/**
 * @file cpuinfodata.h
 * @author Kadir Ince
 * @date 04.042017
 *
 */
#ifndef CPUINFODATA_H
#define CPUINFODATA_H

#include <QObject>
#include "cpuinfo.h"

/**
 * @brief The CpuInfoData class read/parse cpuinfo and send to the CpuInfoModel
 */
class CpuInfoData : public QObject
{
    Q_OBJECT
public:
    explicit CpuInfoData(QObject *parent = 0);

signals:
    /**
     * @brief This signal is emitted just before cpuinfo added to the model
     * @param cpuinfo cpu information
     */
    void addCpuInfo(const CpuInfo &cpuinfo);

public slots:

private slots:
    /**
     * @brief This function is called to parse end to send the cpu information to the model
     */
    void sendCpuInfo();
};

#endif // CPUINFODATA_H
