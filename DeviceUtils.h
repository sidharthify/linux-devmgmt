#pragma once

#include <QDate>
#include <QDateTime>
#include <QFile>
#include <QLocale>
#include <QSet>
#include <QString>

inline QString formatDate(const QDate &date) {
    return QLocale::system().toString(date, QLocale::ShortFormat);
}

inline QString formatDate(const QDateTime &dt) {
    return formatDate(dt.date());
}

inline QString readSysFile(const QString &path) {
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return {};
    return QString::fromUtf8(f.readAll()).trimmed();
}

inline bool isSafeToDisable(const QString &driver) {
    static const QSet<QString> blocked{
        "amdgpu", "radeon", "nouveau", "i915", "xe",
        "nvidia", "nvidia_drm", "nvidia_modeset",
        "nvme", "ahci", "sd_mod", "usb_storage",
        "virtio_blk", "mmc_block",
        "i8042", "atkbd", "usbhid", "hid_generic",
        "acpi", "acpi_cpufreq", "battery", "ac",
        "thermal", "processor",
        "dm_mod", "md_mod",
        "virtio_net",
    };
    return !blocked.contains(driver);
}