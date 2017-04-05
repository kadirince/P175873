/**
 * @file cpuinfo.h
 * @author Kadir Ince
 * @date 04.042017
 *
 */
#ifndef CPUINFO_H
#define CPUINFO_H

#include <QString>

/**
 * @brief The CpuInfo class
 */
class CpuInfo
{
public:
    /**
     * @brief Constructor
     * @param type kind of information
     * @param val value
     */
    CpuInfo(const QString &type, const QString &val);

    QString type() const;
    QString val() const;

private:
    QString m_type;
    QString m_val;
};

#endif // CPUINFO_H
