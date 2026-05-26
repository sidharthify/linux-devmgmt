#include "DeviceScanner.h"
#include "SysfsScanner.h"
#include "DeviceData.h"
#include <QHostInfo>

DeviceScanner::DeviceScanner(QObject *parent)
    : QThread(parent) {}

void DeviceScanner::run() {
    QString host = QHostInfo::localHostName().toUpper();
    if (host.isEmpty())
        host = QStringLiteral("LOCALHOST");
    QVector<DeviceCategory> cats = scanDevices();
    emit scanComplete(host, cats);
}