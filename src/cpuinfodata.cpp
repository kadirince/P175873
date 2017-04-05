/**
 * @file cpuinfodata.cpp
 * @author Kadir Ince
 * @date 04.042017
 *
 */
#include "cpuinfodata.h"
#include <QTimer>
#include <QProcess>




CpuInfoData::CpuInfoData(QObject *parent) : QObject(parent)
{
    QTimer::singleShot(1000, this, SLOT(sendCpuInfo()));
}

void CpuInfoData::sendCpuInfo()
{
    // read cpuinfo
    QString cpuVid      = "-";
    QString cpuModName  = "-";
    QString cpuMHz      = "-";
    QString cpuCores    = "-";

    try
    {

        QProcess process;
        process.start("cat /proc/cpuinfo");
        process.waitForFinished(1000); // will wait 1000ms until finished

        QString stdout = process.readAllStandardOutput();
        QString stderr = process.readAllStandardError();

        if (stderr.isEmpty())
        {
            // parse cpuinfo
            QStringList listinfo = stdout.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

            foreach (QString v, listinfo)
            {
                if (v.contains("vendor_id"))
                {
                    cpuVid = v.split(":").at(1);
                }
                else if (v.contains("model name"))
                {
                    cpuModName = v.split(":").at(1);
                }
                else if (v.contains("cpu MHz"))
                {
                    cpuMHz = v.split(":").at(1);
                }
                else if (v.contains("cpu cores"))
                {
                    cpuCores = v.split(":").at(1);
                }
            }
        }
        else
        {
            cpuVid = stderr;
        }

    }
    catch (...)
    {
        cpuVid      = "unexpected error occured";
    }

    emit addCpuInfo(CpuInfo("vendor_id", cpuVid));
    emit addCpuInfo(CpuInfo("model name", cpuModName));
    emit addCpuInfo(CpuInfo("cpu MHz  ", cpuMHz));
    emit addCpuInfo(CpuInfo("cpu cores", cpuCores));
}

