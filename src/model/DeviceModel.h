#pragma once

#include <QAbstractItemModel>
#include <QIcon>
#include <QSet>
#include "DeviceData.h"

class DeviceModel : public QAbstractItemModel {
    Q_OBJECT
public:
    enum NodeType { RootNode, ComputerNode, CategoryNode, DeviceNode,
                    DisabledCategoryNode };

    struct Node {
        NodeType type;
        QString label;
        QString iconName;
        Node *parent = nullptr;
        QVector<Node *> children;
        const Device *device = nullptr;
        ~Node() { qDeleteAll(children); }
    };

    explicit DeviceModel(QObject *parent = nullptr);
    ~DeviceModel() override;

    void setCategories(const QString &hostName,
                       const QVector<DeviceCategory> &categories);
    QVariant deviceField(const QModelIndex &index,
                         const QString &field) const;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = {}) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = {}) const override;
    int columnCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;

private:
    Node *m_root = nullptr;
    QVector<DeviceCategory> m_storage;
    QSet<QString> m_disabledModules;
    Device m_machine;

    Node *nodeFor(const QModelIndex &index) const;
    void loadDisabledModules();
};