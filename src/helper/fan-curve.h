#ifndef HELPER_FAN_CURVE_H
#define HELPER_FAN_CURVE_H

#include "../fan_curve.h"

#include <QString>

class FanCurveBackend {
public:
    virtual ~FanCurveBackend() = default;
    [[nodiscard]] virtual FanCurveCapability capability() const = 0;
    [[nodiscard]] virtual bool readProfile(FanCurveProfile *profile, QString *error) const = 0;
    [[nodiscard]] virtual QString readMode() const = 0;
    virtual bool writeMode(const QString &mode, QString *error) = 0;
    virtual bool writePoint(const QString &fan, const QString &kind, int index,
                            int value, QString *error) = 0;
};

// Write a mode and require an exact readback. Invalid modes are rejected
// before any sysfs/EC write.
[[nodiscard]] bool writeFanModeVerified(FanCurveBackend &backend, const QString &mode,
                                         QString *error = nullptr);

class SysfsFanCurveBackend final : public FanCurveBackend {
public:
    explicit SysfsFanCurveBackend(QString root = QStringLiteral("/sys/devices/platform/msi-ec"));

    [[nodiscard]] FanCurveCapability capability() const override;
    [[nodiscard]] bool readProfile(FanCurveProfile *profile, QString *error) const override;
    [[nodiscard]] QString readMode() const override;
    bool writeMode(const QString &mode, QString *error) override;
    bool writePoint(const QString &fan, const QString &kind, int index,
                    int value, QString *error) override;

private:
    QString root;
    [[nodiscard]] QString pathFor(const QString &fan, const QString &kind, int index) const;
    [[nodiscard]] QString read(const QString &path, QString *error = nullptr) const;
    bool write(const QString &path, const QString &value, QString *error);
};

class FanCurveTransaction {
public:
    explicit FanCurveTransaction(FanCurveBackend &backend) : backend(backend) {}

    [[nodiscard]] FanCurveResult apply(const FanCurveProfile &profile);

private:
    FanCurveBackend &backend;
    bool writeProfile(const FanCurveProfile &profile, QString *error);
    bool profileMatches(const FanCurveProfile &profile, QString *error) const;
    bool restore(const FanCurveProfile &profile, const QString &mode, QString *error);
};

#endif // HELPER_FAN_CURVE_H
