#pragma once

#include <QDialog>

class UpdateDriverDialog : public QDialog {
    Q_OBJECT
public:
    explicit UpdateDriverDialog(const QString &deviceName,
                                const QString &moduleName,
                                QWidget *parent = nullptr);
};