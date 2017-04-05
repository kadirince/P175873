/**
 * @file cpuinfo.cpp
 * @author Kadir Ince
 * @date 04.042017
 *
 */
#include "cpuinfo.h"

CpuInfo::CpuInfo(const QString &type, const QString &val)
    : m_type(type), m_val(val)
{
}

QString CpuInfo::type() const
{
    return m_type;
}

QString CpuInfo::val() const
{
    return m_val;
}

