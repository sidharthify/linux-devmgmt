#pragma once

#include <QDialog>

class QTabWidget;
class QPushButton;

struct DeviceInfo {
    QString name;
    QString manufacturer;
    QString status;
    QString driver;
    QString driverVersion;
    QString driverDate;
    QString location;
    QString iconName;
    bool disabled = false;
    bool isDkms = false;
    QString rawLocation;
    QString sysfsPciPath;
    QString deviceType;
};

class DevicePropertiesDialog : public QDialog {
    Q_OBJECT
public:
    explicit DevicePropertiesDialog(const DeviceInfo &info,
                                    QWidget *parent = nullptr);

signals:
    void disableToggled(bool nowDisabled);

private:
    DeviceInfo m_info;
    QPushButton *m_disableBtn = nullptr;

    QWidget *buildGeneralTab();
    QWidget *buildDriverTab();
    QWidget *buildDetailsTab();
    QWidget *buildResourcesTab();

    bool isKernelModule() const;
};