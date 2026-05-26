#pragma once

#include <QDialog>

class DriverDetailsDialog : public QDialog {
    Q_OBJECT
public:
    explicit DriverDetailsDialog(const QString &moduleName,
                                 QWidget *parent = nullptr);
};