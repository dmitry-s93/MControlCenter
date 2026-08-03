/* Copyright (C) 2026 MControlCenter contributors
 *
 * Typed fan-curve capability, profile, and transaction result boundary.
 */
#ifndef FAN_CURVE_H
#define FAN_CURVE_H

#include <QVariantMap>
#include <QVector>
#include <QString>

struct FanCurveCapability {
    bool supported = false;
    int thresholdCount = 0;
    int levelCount = 0;
    int thresholdMin = 0;
    int thresholdMax = 0;
    int levelMin = 0;
    int levelMax = 0;
    QString reason;

    [[nodiscard]] bool complete() const noexcept;
};

struct FanCurveProfile {
    QVector<int> cpuThresholds;
    QVector<int> cpuLevels;
    QVector<int> gpuThresholds;
    QVector<int> gpuLevels;

    [[nodiscard]] bool complete() const noexcept;
    friend bool operator==(const FanCurveProfile &left, const FanCurveProfile &right) noexcept {
        return left.cpuThresholds == right.cpuThresholds && left.cpuLevels == right.cpuLevels &&
               left.gpuThresholds == right.gpuThresholds && left.gpuLevels == right.gpuLevels;
    }
};

struct FanCurveState {
    QString mode;
    FanCurveProfile profile;
    bool readable = false;
};

struct FanCurveResult {
    bool success = false;
    QString effectiveMode;
    QString error;
    QString rollbackStatus;

    [[nodiscard]] bool rolledBack() const noexcept { return rollbackStatus == QStringLiteral("succeeded"); }
};

// Validation is deliberately independent of Qt widgets and sysfs so that it can
// be exercised with a fake backend without touching hardware.
[[nodiscard]] QString fanCurveProfileWithinRanges(const FanCurveCapability &capability,
                                                  const FanCurveProfile &profile);
[[nodiscard]] QString validateFanCurve(const FanCurveCapability &capability,
                                       const FanCurveProfile &profile);
[[nodiscard]] bool fanCurveFirmwareMatches(const QString &savedVersion,
                                           const QString &savedDate,
                                           const QString &currentVersion,
                                           const QString &currentDate);

[[nodiscard]] QVariantMap fanCurveCapabilityToMap(const FanCurveCapability &capability);
[[nodiscard]] FanCurveCapability fanCurveCapabilityFromMap(const QVariantMap &map);
[[nodiscard]] QVariantMap fanCurveProfileToMap(const FanCurveProfile &profile);
[[nodiscard]] bool fanCurveProfileFromMap(const QVariantMap &map, FanCurveProfile *profile);
[[nodiscard]] QVariantMap fanCurveResultToMap(const FanCurveResult &result);
[[nodiscard]] FanCurveResult fanCurveResultFromMap(const QVariantMap &map);

#endif // FAN_CURVE_H
