#ifndef ABSTRACTLISTMODEL_H
#define ABSTRACTLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QRegExp>
#include <QDebug>

class AbstractListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AbstractListModel(QList<QString> list_setup, QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE void addItem(QJsonObject txt);
    Q_INVOKABLE QJsonObject get(int);
    Q_INVOKABLE void insertItem(int row, QJsonObject json);
    Q_INVOKABLE bool editItem(const QModelIndex &index, const QJsonObject json, int role = Qt::EditRole);
    Q_INVOKABLE void deleteItem(int row);
    Q_INVOKABLE void clearModel();
    Q_INVOKABLE void applyFilter(QString, QString);
    Q_INVOKABLE int count();

public slots:
    void load(QJsonArray json);
    void reload(QJsonArray json);

private:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QJsonArray m_list_itens;
    int m_count = 0;
    QHash<int, QByteArray> m_dic_role;
    QList<int> m_list_role;
    QList<int> m_filter;
    int userRole;
    int currentIndex = 0;
    const QModelIndex index;
    bool m_flagFilter;
};

#endif // ABSTRACTLISTMODEL_H
