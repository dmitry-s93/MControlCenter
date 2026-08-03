#include "fan-curve.h"

#include <QFile>

namespace {
const QString fanCurveSupported = QStringLiteral("fan_curve_supported");
const QString thresholdCount = QStringLiteral("fan_curve_threshold_count");
const QString levelCount = QStringLiteral("fan_curve_level_count");
const QString thresholdMin = QStringLiteral("fan_curve_threshold_min");
const QString thresholdMax = QStringLiteral("fan_curve_threshold_max");
const QString levelMin = QStringLiteral("fan_curve_level_min");
const QString levelMax = QStringLiteral("fan_curve_level_max");

bool parseInt(const QString &text, int *value) {
    bool ok = false;
    const int parsed = text.trimmed().toInt(&ok);
    if (ok && value)
        *value = parsed;
    return ok;
}
}

SysfsFanCurveBackend::SysfsFanCurveBackend(QString root) : root(std::move(root)) {}

bool writeFanModeVerified(FanCurveBackend &backend, const QString &mode, QString *error) {
    if (mode != QStringLiteral("auto") && mode != QStringLiteral("silent") &&
        mode != QStringLiteral("basic") && mode != QStringLiteral("advanced")) {
        if (error)
            *error = QStringLiteral("invalid fan mode");
        return false;
    }
    if (!backend.writeMode(mode, error))
        return false;
    if (backend.readMode() != mode) {
        if (error)
            *error = QStringLiteral("fan mode readback did not match requested mode");
        return false;
    }
    return true;
}

QString SysfsFanCurveBackend::pathFor(const QString &fan, const QString &kind, int index) const {
    return root + QLatin1Char('/') + fan + QStringLiteral("/fan_curve_") + kind +
           QLatin1Char('_') + QString::number(index);
}

QString SysfsFanCurveBackend::read(const QString &path, QString *error) const {
    QFile file(path);
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        if (error)
            *error = QStringLiteral("cannot read %1").arg(path);
        return {};
    }
    return QString::fromUtf8(file.readAll()).trimmed();
}

bool SysfsFanCurveBackend::write(const QString &path, const QString &value, QString *error) {
    QFile file(path);
    if (!file.exists() || !file.open(QIODevice::WriteOnly) ||
        file.write(value.toUtf8()) != value.toUtf8().size()) {
        if (error)
            *error = QStringLiteral("cannot write %1").arg(path);
        return false;
    }
    return true;
}

FanCurveCapability SysfsFanCurveBackend::capability() const {
    FanCurveCapability capability;
    QString text;
    text = read(root + QLatin1Char('/') + fanCurveSupported);
    int supported = 0;
    if (!parseInt(text, &supported) || supported != 1) {
        capability.reason = QStringLiteral("driver does not advertise fan curve support");
        return capability;
    }
    const auto readCapability = [&](const QString &name, int *field) -> bool {
        QString error;
        const QString value = read(root + QLatin1Char('/') + name, &error);
        return parseInt(value, field);
    };
    if (!readCapability(thresholdCount, &capability.thresholdCount) ||
        !readCapability(levelCount, &capability.levelCount) ||
        !readCapability(thresholdMin, &capability.thresholdMin) ||
        !readCapability(thresholdMax, &capability.thresholdMax) ||
        !readCapability(levelMin, &capability.levelMin) ||
        !readCapability(levelMax, &capability.levelMax)) {
        capability.reason = QStringLiteral("driver fan curve capability is incomplete");
        return capability;
    }
    capability.supported = true;
    if (!capability.complete()) {
        capability.reason = QStringLiteral("driver fan curve capability has unexpected counts or ranges");
        return capability;
    }
    // Metadata alone is not a usable ABI. Confirm every point and the mode
    // control exist before exposing the capability to the application.
    if (!QFile::exists(root + QStringLiteral("/fan_mode"))) {
        capability.supported = false;
        capability.reason = QStringLiteral("fan mode control is missing");
        return capability;
    }
    for (const QString &fan : {QStringLiteral("cpu"), QStringLiteral("gpu")}) {
        for (const QString &kind : {QStringLiteral("threshold"), QStringLiteral("level")}) {
            const int count = kind == QStringLiteral("threshold") ? capability.thresholdCount : capability.levelCount;
            for (int index = 1; index <= count; ++index) {
                if (!QFile::exists(pathFor(fan, kind, index))) {
                    capability.supported = false;
                    capability.reason = QStringLiteral("fan curve ABI is missing %1/%2_%3")
                                             .arg(fan, kind).arg(index);
                    return capability;
                }
            }
        }
    }
    FanCurveProfile probe;
    QString probeError;
    if (readMode().isEmpty() || !readProfile(&probe, &probeError)) {
        capability.supported = false;
        capability.reason = probeError.isEmpty() ? QStringLiteral("fan curve ABI cannot be read") : probeError;
    }
    return capability;
}

bool SysfsFanCurveBackend::readProfile(FanCurveProfile *profile, QString *error) const {
    if (!profile)
        return false;
    FanCurveProfile result;
    const auto readValues = [&](const QString &fan, const QString &kind, int count,
                                QVector<int> *values) -> bool {
        for (int index = 1; index <= count; ++index) {
            QString readError;
            const QString text = read(pathFor(fan, kind, index), &readError);
            int value = 0;
            if (!parseInt(text, &value)) {
                if (error)
                    *error = readError.isEmpty() ? QStringLiteral("invalid fan curve value") : readError;
                return false;
            }
            values->append(value);
        }
        return true;
    };
    if (!readValues(QStringLiteral("cpu"), QStringLiteral("threshold"), 6, &result.cpuThresholds) ||
        !readValues(QStringLiteral("cpu"), QStringLiteral("level"), 7, &result.cpuLevels) ||
        !readValues(QStringLiteral("gpu"), QStringLiteral("threshold"), 6, &result.gpuThresholds) ||
        !readValues(QStringLiteral("gpu"), QStringLiteral("level"), 7, &result.gpuLevels))
        return false;
    *profile = result;
    return true;
}

QString SysfsFanCurveBackend::readMode() const {
    return read(root + QStringLiteral("/fan_mode"));
}

bool SysfsFanCurveBackend::writeMode(const QString &mode, QString *error) {
    if (mode != QStringLiteral("auto") && mode != QStringLiteral("silent") &&
        mode != QStringLiteral("basic") && mode != QStringLiteral("advanced")) {
        if (error)
            *error = QStringLiteral("invalid fan mode");
        return false;
    }
    return write(root + QStringLiteral("/fan_mode"), mode, error);
}

bool SysfsFanCurveBackend::writePoint(const QString &fan, const QString &kind, int index,
                                      int value, QString *error) {
    return write(pathFor(fan, kind, index), QString::number(value), error);
}

bool FanCurveTransaction::writeProfile(const FanCurveProfile &profile, QString *error) {
    const auto writeValues = [&](const QString &fan, const QString &kind,
                                 const QVector<int> &values) -> bool {
        for (int i = 0; i < values.size(); ++i) {
            if (!backend.writePoint(fan, kind, i + 1, values[i], error))
                return false;
        }
        return true;
    };
    return writeValues(QStringLiteral("cpu"), QStringLiteral("threshold"), profile.cpuThresholds) &&
           writeValues(QStringLiteral("cpu"), QStringLiteral("level"), profile.cpuLevels) &&
           writeValues(QStringLiteral("gpu"), QStringLiteral("threshold"), profile.gpuThresholds) &&
           writeValues(QStringLiteral("gpu"), QStringLiteral("level"), profile.gpuLevels);
}

bool FanCurveTransaction::profileMatches(const FanCurveProfile &profile, QString *error) const {
    FanCurveProfile readback;
    if (!backend.readProfile(&readback, error))
        return false;
    if (readback.cpuThresholds != profile.cpuThresholds ||
        readback.cpuLevels != profile.cpuLevels ||
        readback.gpuThresholds != profile.gpuThresholds ||
        readback.gpuLevels != profile.gpuLevels) {
        if (error)
            *error = QStringLiteral("fan curve readback did not match requested values");
        return false;
    }
    return true;
}

bool FanCurveTransaction::restore(const FanCurveProfile &profile, const QString &mode, QString *error) {
    // Never rewrite points while Advanced (or another mode) may consume them.
    // Force a known safe mode before restoring the snapshot values.
    if (!writeFanModeVerified(backend, QStringLiteral("auto"), error))
        return false;
    if (!writeProfile(profile, error) || !profileMatches(profile, error))
        return false;
    if (!writeFanModeVerified(backend, mode, error)) {
        if (error && error->isEmpty())
            *error = QStringLiteral("fan mode rollback readback failed");
        return false;
    }
    return true;
}

FanCurveResult FanCurveTransaction::apply(const FanCurveProfile &profile) {
    FanCurveResult result;
    result.rollbackStatus = QStringLiteral("not-needed");
    const FanCurveCapability capability = backend.capability();
    if (const QString validationError = validateFanCurve(capability, profile); !validationError.isEmpty()) {
        result.error = validationError;
        result.effectiveMode = backend.readMode();
        return result;
    }

    FanCurveProfile snapshot;
    QString error;
    const QString snapshotMode = backend.readMode();
    if (snapshotMode.isEmpty() || !backend.readProfile(&snapshot, &error)) {
        result.error = error.isEmpty() ? QStringLiteral("could not snapshot current fan curve") : error;
        result.effectiveMode = snapshotMode;
        return result;
    }

    // A readable but malformed snapshot must never be reactivated as
    // Advanced. It can still be restored as data, but only while Auto is active.
    const bool snapshotCurveValid = validateFanCurve(capability, snapshot).isEmpty();
    const QString rollbackMode = (snapshotMode == QStringLiteral("advanced") && !snapshotCurveValid)
                                     ? QStringLiteral("auto") : snapshotMode;

    auto failAndRollback = [&](const QString &failure) {
        result.success = false;
        result.error = failure;
        QString rollbackError;
        if (restore(snapshot, rollbackMode, &rollbackError)) {
            result.rollbackStatus = QStringLiteral("succeeded");
            result.effectiveMode = rollbackMode;
        } else {
            // A partially written EC curve is unsafe.  Auto is the only safe
            // mode that does not consume the potentially inconsistent curve.
            QString autoError;
            const bool autoVerified = writeFanModeVerified(backend, QStringLiteral("auto"), &autoError);
            result.rollbackStatus = QStringLiteral("failed_auto");
            result.effectiveMode = autoVerified ? QStringLiteral("auto") : backend.readMode();
            if (!autoVerified && !autoError.isEmpty())
                result.error += QStringLiteral("; auto fallback failed: ") + autoError;
        }
    };

    if (snapshotMode != QStringLiteral("auto")) {
        if (!writeFanModeVerified(backend, QStringLiteral("auto"), &error)) {
            failAndRollback(error.isEmpty() ? QStringLiteral("could not enter auto mode") : error);
            return result;
        }
    }
    if (!writeProfile(profile, &error) || !profileMatches(profile, &error)) {
        failAndRollback(error.isEmpty() ? QStringLiteral("fan curve write failed") : error);
        return result;
    }
    if (!writeFanModeVerified(backend, QStringLiteral("advanced"), &error)) {
        failAndRollback(error.isEmpty() ? QStringLiteral("could not activate advanced mode") : error);
        return result;
    }
    result.success = true;
    result.effectiveMode = QStringLiteral("advanced");
    result.error.clear();
    return result;
}
