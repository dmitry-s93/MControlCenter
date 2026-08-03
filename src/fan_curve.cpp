#include "fan_curve.h"

#include <QDBusArgument>
#include <QDBusVariant>
#include <QVariantList>

namespace {
QVector<int> vectorFromVariant(const QVariant &value, bool *ok) {
    QVector<int> result;
    *ok = false;
    if (!value.isValid())
        return {};

    QVariantList list;
    if (value.metaType() == QMetaType::fromType<QDBusArgument>()) {
        const QDBusArgument argument = qvariant_cast<QDBusArgument>(value);
        if (argument.currentSignature() != QStringLiteral("av"))
            return {};
        argument.beginArray();
        while (!argument.atEnd()) {
            QDBusVariant wrapped;
            argument >> wrapped;
            list.append(wrapped.variant());
        }
        argument.endArray();
    } else if (value.canConvert<QVariantList>()) {
        list = value.toList();
    } else {
        return {};
    }

    result.reserve(list.size());
    for (const QVariant &entry : list) {
        bool converted = false;
        const int number = entry.toInt(&converted);
        if (!converted)
            return {};
        result.append(number);
    }
    *ok = true;
    return result;
}

QVariantList variantFromVector(const QVector<int> &values) {
    QVariantList result;
    result.reserve(values.size());
    for (const int value : values)
        result.append(value);
    return result;
}
}

bool FanCurveCapability::complete() const noexcept {
    return supported && thresholdCount == 6 && levelCount == 7 &&
           thresholdMin == 0 && thresholdMax == 100 &&
           levelMin == 0 && levelMax == 150;
}

bool FanCurveProfile::complete() const noexcept {
    return cpuThresholds.size() == 6 && cpuLevels.size() == 7 &&
           gpuThresholds.size() == 6 && gpuLevels.size() == 7;
}

QString fanCurveProfileWithinRanges(const FanCurveCapability &capability,
                                    const FanCurveProfile &profile) {
    if (!capability.complete())
        return QStringLiteral("unsupported or incomplete fan curve ABI");
    if (!profile.complete())
        return QStringLiteral("fan curve must contain exactly 6 thresholds and 7 levels per fan");
    for (const QVector<int> *thresholds : {&profile.cpuThresholds, &profile.gpuThresholds}) {
        for (const int value : *thresholds) {
            if (value < capability.thresholdMin || value > capability.thresholdMax)
                return QStringLiteral("threshold outside driver range");
        }
    }
    for (const QVector<int> *levels : {&profile.cpuLevels, &profile.gpuLevels}) {
        for (const int value : *levels) {
            if (value < capability.levelMin || value > capability.levelMax)
                return QStringLiteral("fan level outside driver range");
        }
    }
    return {};
}

QString validateFanCurve(const FanCurveCapability &capability,
                         const FanCurveProfile &profile) {
    if (const QString error = fanCurveProfileWithinRanges(capability, profile); !error.isEmpty())
        return error;
    const auto validateThresholds = [](const QVector<int> &values) -> QString {
        for (int i = 1; i < values.size(); ++i) {
            if (values[i] <= values[i - 1])
                return QStringLiteral("thresholds must be strictly ascending");
        }
        return {};
    };
    const auto validateLevels = [](const QVector<int> &values) -> QString {
        for (int i = 1; i < values.size(); ++i) {
            if (values[i] < values[i - 1])
                return QStringLiteral("fan levels must be nondecreasing");
        }
        return {};
    };
    for (const QVector<int> *thresholds : {&profile.cpuThresholds, &profile.gpuThresholds}) {
        if (const QString error = validateThresholds(*thresholds); !error.isEmpty())
            return error;
    }
    for (const QVector<int> *levels : {&profile.cpuLevels, &profile.gpuLevels}) {
        if (const QString error = validateLevels(*levels); !error.isEmpty())
            return error;
    }
    return {};
}

bool fanCurveFirmwareMatches(const QString &savedVersion,
                              const QString &savedDate,
                              const QString &currentVersion,
                              const QString &currentDate) {
    return !savedVersion.isEmpty() && !savedDate.isEmpty() &&
           savedVersion == currentVersion && savedDate == currentDate;
}

QVariantMap fanCurveCapabilityToMap(const FanCurveCapability &capability) {
    return {{QStringLiteral("supported"), capability.supported},
            {QStringLiteral("threshold_count"), capability.thresholdCount},
            {QStringLiteral("level_count"), capability.levelCount},
            {QStringLiteral("threshold_min"), capability.thresholdMin},
            {QStringLiteral("threshold_max"), capability.thresholdMax},
            {QStringLiteral("level_min"), capability.levelMin},
            {QStringLiteral("level_max"), capability.levelMax},
            {QStringLiteral("reason"), capability.reason}};
}

FanCurveCapability fanCurveCapabilityFromMap(const QVariantMap &map) {
    FanCurveCapability capability;
    capability.supported = map.value(QStringLiteral("supported")).toBool();
    capability.thresholdCount = map.value(QStringLiteral("threshold_count")).toInt();
    capability.levelCount = map.value(QStringLiteral("level_count")).toInt();
    capability.thresholdMin = map.value(QStringLiteral("threshold_min")).toInt();
    capability.thresholdMax = map.value(QStringLiteral("threshold_max")).toInt();
    capability.levelMin = map.value(QStringLiteral("level_min")).toInt();
    capability.levelMax = map.value(QStringLiteral("level_max")).toInt();
    capability.reason = map.value(QStringLiteral("reason")).toString();
    return capability;
}

QVariantMap fanCurveProfileToMap(const FanCurveProfile &profile) {
    return {{QStringLiteral("cpu_thresholds"), variantFromVector(profile.cpuThresholds)},
            {QStringLiteral("cpu_levels"), variantFromVector(profile.cpuLevels)},
            {QStringLiteral("gpu_thresholds"), variantFromVector(profile.gpuThresholds)},
            {QStringLiteral("gpu_levels"), variantFromVector(profile.gpuLevels)}};
}

bool fanCurveProfileFromMap(const QVariantMap &map, FanCurveProfile *profile) {
    if (!profile)
        return false;
    bool okCpuThresholds = false;
    bool okCpuLevels = false;
    bool okGpuThresholds = false;
    bool okGpuLevels = false;
    FanCurveProfile candidate;
    candidate.cpuThresholds = vectorFromVariant(map.value(QStringLiteral("cpu_thresholds")), &okCpuThresholds);
    candidate.cpuLevels = vectorFromVariant(map.value(QStringLiteral("cpu_levels")), &okCpuLevels);
    candidate.gpuThresholds = vectorFromVariant(map.value(QStringLiteral("gpu_thresholds")), &okGpuThresholds);
    candidate.gpuLevels = vectorFromVariant(map.value(QStringLiteral("gpu_levels")), &okGpuLevels);
    if (!okCpuThresholds || !okCpuLevels || !okGpuThresholds || !okGpuLevels)
        return false;
    *profile = candidate;
    return true;
}

QVariantMap fanCurveResultToMap(const FanCurveResult &result) {
    return {{QStringLiteral("success"), result.success},
            {QStringLiteral("effective_mode"), result.effectiveMode},
            {QStringLiteral("error"), result.error},
            {QStringLiteral("rollback_status"), result.rollbackStatus}};
}

FanCurveResult fanCurveResultFromMap(const QVariantMap &map) {
    FanCurveResult result;
    result.success = map.value(QStringLiteral("success")).toBool();
    result.effectiveMode = map.value(QStringLiteral("effective_mode")).toString();
    result.error = map.value(QStringLiteral("error")).toString();
    result.rollbackStatus = map.value(QStringLiteral("rollback_status")).toString();
    return result;
}
