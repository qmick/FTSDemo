#include "resulttablemodel.h"

ResultTableModel::ResultTableModel()
{
    mHeader = QStringList({ "name", "rank", "snippet", "path"});
}


int ResultTableModel::rowCount(const QModelIndex &) const
{
    return mData.size();
}

int ResultTableModel::columnCount(const QModelIndex &) const
{
    return mHeader.size();
}

QVariant ResultTableModel::data(const QModelIndex &index, int) const
{
    return mData[index.row()][index.column()];
}

QVariant ResultTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return mHeader.at(section);
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}
