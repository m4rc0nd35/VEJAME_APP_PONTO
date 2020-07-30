#include "abstractlistmodel.h"

AbstractListModel::AbstractListModel(QList<QString> list_coluns, QObject* parent):QAbstractListModel(parent)
{
    for(int i = 0; i < list_coluns.count(); i++)
    {
        userRole = (Qt::UserRole + (i + 1));
        m_list_role.append(userRole);
        m_dic_role.insert(userRole, list_coluns[i].toUtf8());
    }
}
int AbstractListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(&parent)
    return m_count;
}
QHash<int, QByteArray> AbstractListModel::roleNames() const
{
    return m_dic_role;
}
QVariant AbstractListModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    int row = index.row();
    if(m_flagFilter)
    { // case filter
        if (index.isValid())
            for(int i = 0; i < m_list_role.count(); i++)
                if (role == m_list_role[i]) // mount coluns
                    return m_list_itens.at(m_filter.at(row)).toObject()[m_dic_role[m_list_role[i]]].toVariant(); // mount row
    }
    else
        if (index.isValid())
            for(int i = 0; i < m_list_role.count(); i++)
                if (role == m_list_role[i]) // mount coluns
                    return m_list_itens.at(row).toObject()[m_dic_role[m_list_role[i]]].toVariant(); // mount row
    return value;
}
void AbstractListModel::addItem(QJsonObject json)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_flagFilter = false;
    m_list_itens.append(json);
    m_count = m_list_itens.count();
    endInsertRows();
}
void AbstractListModel::insertItem(int row, QJsonObject json)
{
    beginInsertRows(QModelIndex(), row, row);
    m_flagFilter = false;
    m_list_itens.insert(row, json);
    m_count = m_list_itens.count();
    endInsertRows();
}
QJsonObject AbstractListModel::get(int row)
{
    return m_list_itens.at(row).toObject();
}
bool AbstractListModel::editItem(const QModelIndex &index, const QJsonObject json, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        beginResetModel();
        m_list_itens.replace(index.row(), json);
        m_flagFilter = false;
        emit dataChanged(index, index, {Qt::EditRole, Qt::DisplayRole});
        m_count = m_list_itens.count();
        endResetModel();
        return true;
    }
    return false;
}
void AbstractListModel::deleteItem(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_flagFilter = false;
    m_list_itens.removeAt(row);
    m_count = m_list_itens.count();
    endRemoveRows();
}
void AbstractListModel::clearModel()
{
    beginResetModel();
    m_flagFilter = false;
    m_list_itens = QJsonArray();
    m_count = m_list_itens.count();
    endResetModel();
}
void AbstractListModel::applyFilter(QString object, QString filter)
{
    beginResetModel();
    m_count = 0;
    endResetModel();
    m_filter.clear();
    m_flagFilter = true;
    QRegExp rx(QString("*%1*").arg(filter));
    rx.setPatternSyntax(QRegExp::Wildcard);
    rx.setCaseSensitivity(Qt::CaseInsensitive);

    for(int i = 0; i < m_list_itens.count(); i++)
        if (rx.exactMatch(m_list_itens.at(i).toObject()[object].toString()))
        {
            beginInsertRows(QModelIndex(), rowCount(), rowCount());
            m_filter.append(i);
            m_count += 1;
            endInsertRows();
        }
}
int AbstractListModel::count()
{
    return m_list_itens.count();
}
void AbstractListModel::load(QJsonArray json)
{
    for(int i = 0; json.count() > i; i++)
        addItem(json.at(i).toObject());
}
void AbstractListModel::reload(QJsonArray json)
{
    clearModel();
    for(int i = 0; json.count() > i; i++)
        addItem(json.at(i).toObject());
}
