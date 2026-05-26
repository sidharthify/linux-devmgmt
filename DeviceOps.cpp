#include "DeviceOps.h"

#include <QMessageBox>
#include <QProcess>

bool setModuleBlacklisted(const QString &driver, bool blacklist, QWidget *parent) {
    QString cmd = blacklist
        ? QString("echo 'blacklist %1' >> %2 && modprobe -r %1")
              .arg(driver, kModprobeConf)
        : QString("sed -i '/^blacklist %1$/d' %2 && modprobe %1")
              .arg(driver, kModprobeConf);

    QProcess proc;
    proc.start("pkexec", {"sh", "-c", cmd});
    proc.waitForFinished(10000);

    if (proc.exitCode() != 0) {
        QString err = QString::fromUtf8(proc.readAllStandardError()).trimmed();
        QMessageBox::warning(parent,
            QString("Could not %1 device").arg(blacklist ? "disable" : "enable"),
            QString("Operation failed:\n\n%1").arg(err));
        return false;
    }
    return true;
}

bool dkmsRemove(const QString &driver, QWidget *parent) {
    QProcess proc;
    proc.start("dkms", {"status"});
    proc.waitForFinished(5000);
    QString dkmsStatus = QString::fromUtf8(proc.readAllStandardOutput());

    QString moduleLine;
    for (const QString &line : dkmsStatus.split('\n')) {
        if (line.contains(driver)) {
            moduleLine = line;
            break;
        }
    }

    QString nameVer;
    if (!moduleLine.isEmpty())
        nameVer = moduleLine.section(',', 0, 0).trimmed();

    if (nameVer.isEmpty()) {
        QMessageBox::warning(parent, "Uninstall failed",
            "Could not find DKMS module information.");
        return false;
    }

    QProcess uninstall;
    uninstall.start("pkexec", {"dkms", "remove", nameVer, "--all"});
    uninstall.waitForFinished(30000);

    if (uninstall.exitCode() != 0) {
        QString err = QString::fromUtf8(uninstall.readAllStandardError()).trimmed();
        QMessageBox::warning(parent, "Uninstall failed",
            "Could not remove the driver:\n\n" + err);
        return false;
    }

    QMessageBox::information(parent, "Uninstalled", "The driver has been removed.");
    return true;
}
