#pragma once

#include <QThread>
#include "DeviceData.h"

class DeviceScanner : public QThread {
    Q_OBJECT
public:
    explicit DeviceScanner(QObject *parent = nullptr);
    void run() override;

signals:
    void scanComplete(const QString &hostName,
                      const QVector<DeviceCategory> &categories);
};