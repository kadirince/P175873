/**
 * @file cpuinfomodel.h
 * @author Kadir Ince
 * @date 04.042017
 *
 */
#ifndef CPUINFOMODEL_H
#define CPUINFOMODEL_H

#include <QAbstractListModel>
#include <QModelIndex>
#include <QVariant>
#include <QStringList>
#include <QByteArray>
#include <QHash>
#include "cpuinfo.h"



/**
 * @brief The CpuInfoModel class
 *
 * separation of concerns - separate data from views
 *
 */
class CpuInfoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /**
     * @brief The cpuInfoRoles enum
     */
    enum cpuInfoRoles
    {
        TypeRole = Qt::UserRole + 1,
        ValRole
    };

    /**
        * @brief Returns size of the list m_cpuinfos
        * @param parent
        * @return row count
        */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @brief Returns the data stored under the given role for the item referred to by the index.
     * @param index
     * @param role
     * @return Returns the data
     */
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    /**
     * @brief addCpuInfo adds the cpu information to the list m_cpuinfos
     * @param cpuinfo cpu information
     */
    void addCpuInfo(const CpuInfo &cpuinfo);

protected:
    /**
     * @brief roleNames
     * @return
     */
    QHash<int, QByteArray> roleNames() const;

private:
    QList<CpuInfo> m_cpuinfos; /// list of cpuinfo
};

#endif // CPUINFOMODEL_H
