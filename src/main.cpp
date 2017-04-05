/**
 * @file main.cpp
 * @author Kadir Ince
 * @date 04.042017
 *
 */
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "speedData.h"
#include "cpuinfomodel.h"
#include "cpuinfodata.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // instance of speedData class
    speedData m_speedData;


    CpuInfoModel model;
    CpuInfoData cpuinfodata;
    QObject::connect(&cpuinfodata, SIGNAL(addCpuInfo(const CpuInfo)),
                     &model, SLOT(addCpuInfo(const CpuInfo)));


    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("speedData", &m_speedData);
    ctx->setContextProperty("cpuInfoModel", &model);



    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    //engine.load(QUrl(QStringLiteral("qrc:/speedo.qml")));

    QMetaObject::Connection con = QObject::connect(&app, SIGNAL(aboutToQuit()),
                                  &m_speedData, SLOT(freeze()));

    //QTimer::singleShot(10000, &m_speedData, SLOT(freeze()));

    return app.exec();
}

