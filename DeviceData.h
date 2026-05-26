#pragma once

#include <QString>
#include <QVector>
#include <QHostInfo>

struct Device {
    QString name;
    QString status;
    QString manufacturer;
    QString driver;
    QString driverVersion;
    QString driverDate;
    QString location;
    QString iconName;
    bool disabled = false;
    bool isDkms = false;
    QString rawLocation;
    QString sysfsPciPath;
};

struct DeviceCategory {
    QString name;
    QString iconName;
    QVector<Device> devices;
};

inline QString rootHostName() {
    QString h = QHostInfo::localHostName().toUpper();
    return h.isEmpty() ? QStringLiteral("LOCALHOST") : h;
}

inline QVector<DeviceCategory> GenericCategories() {
    return {
        {
            "Disk drives", "drive-harddisk",
            {
                {"Generic NVMe Drive", "Working properly",
                 "Generic Vendor", "nvme"},
                {"Generic SATA Hard Disk Drive", "Working properly",
                 "Generic Vendor", "sd"}
            }
        },
        {
            "Display adapters", "video-display",
            {
                {"Linux Basic Display Adapter", "Working properly",
                 "Linux", "basicdisplay"}
            }
        },
        {
            "Network adapters", "network-wired",
            {
                {"Generic Ethernet Controller", "Working properly",
                 "Generic Vendor", "eth"},
                {"Generic Wireless Adapter", "Working properly",
                 "Generic Vendor", "wifi"}
            }
        },
        {
            "Processors", "cpu",
            {
                {"GenuineIntel Processor", "Working properly",
                 "GenuineIntel", "intel"}
            }
        },
        {
            "Sound, video and game controllers", "audio-card",
            {
                {"High Defition Audio Device", "Working properly",
                 "Linux", "hda"}
            }
        },
        {
            "Universal Serial Bus controllers", "drive-removable-media-usb",
            {
                {"Generic xHCI USB Controller", "Working properly",
                 "Generic Vendor", "xhci_hcd"}
            }
        }
    };
}
