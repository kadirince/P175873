/**
 * @file speedData.h
 * @see http://community.qnx.com/sf/discussion/do/listPosts/projects.qt/discussion.general.topc21389?_pagenum=1
 *
 */
#ifndef SPEEDDATA_H
#define SPEEDDATA_H

#include <QObject>
#include <QString>
#include <QList>
#include <QStack>
#include <QTime>
#include <QTimer>
#include <QThread>
//#include <QDeclarativeListProperty>

class watchThread : public QThread
{
public:
    void run();  // re-implement - from QThread
};

class speedData : public QObject
{
    Q_OBJECT

public:
    speedData(QObject *parent = 0);
    ~speedData();
    watchThread *valThread;
    void valsChanged( QString Mtr0, QString Mtr1, QString totFrames );
    int totalFrames;
    int xmtr0;   // "mph" angle
    int xmtr1;   // "rpm" angle
    bool simulationFrozen;

public slots:
    void freeze();

signals:
    void valuesChanged( QString Mtr0, QString Mtr1, QString totFrames );
private:
};

extern speedData *speedD;

#endif // SPEEDDATA_H
