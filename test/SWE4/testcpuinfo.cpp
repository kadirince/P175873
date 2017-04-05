#include <QtTest/QtTest>
#include "cpuinfo.h"

class TestCpuInfo: public QObject
{
    Q_OBJECT
private slots:
    void test1();
};

void TestCpuInfo::test1()
{
    CpuInfo cpuinf("vendor_id", "TEST ID");
    QVERIFY(cpuinf.type() == "vendor_id");
    QVERIFY(cpuinf.val() == "TEST ID");
}

QTEST_MAIN(TestCpuInfo)
#include "testcpuinfo.moc"
