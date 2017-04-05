/**
 * @file cpuinfomodel.cpp
 * @author Kadir Ince
 * @date 04.042017
 *
 */
#include "cpuinfomodel.h"



int CpuInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_cpuinfos.count();
}

QVariant CpuInfoModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_cpuinfos.count())
    {
        return QVariant();
    }

    const CpuInfo &cpuinfo = m_cpuinfos[index.row()];

    if (role == TypeRole)
    {
        return cpuinfo.type();
    }
    else if (role == ValRole)
    {
        return cpuinfo.val();
    }

    return QVariant();
}


QHash<int, QByteArray> CpuInfoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[ValRole] = "val";
    return roles;
}


void CpuInfoModel::addCpuInfo(const CpuInfo &cpuinfo)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_cpuinfos << cpuinfo;
    endInsertRows();
}


