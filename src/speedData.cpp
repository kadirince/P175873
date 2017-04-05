/**
 * @file speedData.cpp
 * @see http://community.qnx.com/sf/discussion/do/listPosts/projects.qt/discussion.general.topc21389?_pagenum=1
 *
 */


#include "speedData.h"
#include <fcntl.h>
#include <math.h>


inline int imax(int a, int b)
{
    return (a > b) ? a : b;
}

// forward
int spd2angle( float x );
int rpm2angle( float x );

// create a global instance pointer to speedData
// so it can be accessed from thread
speedData *speedD;

/**********************************************************************/

#define TICKS_PER_SEC   100
#define MS_SLEEP        (1000 / TICKS_PER_SEC)

#define TOT_SECS_UP       8
#define TOT_SECS_STDY     3
#define TOT_SECS_DOWN     4
#define TOT_SECS_STOPPED  2
#define TOT_SECS        (TOT_SECS_UP + TOT_SECS_STDY + TOT_SECS_DOWN + TOT_SECS_STOPPED)

#define S_ANGL_BASE     205
#define S_ANGL_RANGE    260
#define S_RANGE         120

#define T_ANGL_BASE     243
#define T_ANGL_RANGE    260
#define T_RANGE         8000

#define MAX_MPH         115
#define MIN_RPM         800
#define RANGE_RPM       4000
#define MAX_RPM         (MIN_RPM + RANGE_RPM)

/**********************************************************************/

speedData::speedData(QObject *parent)
    : QObject(parent)
{
    speedD = this;
    valThread = new watchThread;
    totalFrames = 0;
    simulationFrozen = false;
    valThread->start();  // calls valThread->run() implemented below
}

speedData::~speedData()
{
}

void speedData::freeze()
{
    // supports a "button" to freeze/unfreeze the simulation
    // the script can call this "slot" directly to change the state - but not currently used!
    simulationFrozen = ~simulationFrozen;

}

/*
 *   GOTCHA!
 *
 *   valuesChanged() is declared as a signal within the speedData class
 *   BUT - IF we preface with 'speedData::' the program will not link!
 *
 *   valsChanged() is a proxy for valuesChanged()
 *     - valChanged() is callable from the thread!
 */
void valuesChanged( QString Mtr0, QString Mtr1, QString totFrames )
{
    // this stub function links to a "signal" in speedo.qml
    // causing it to updates its screen using the call parameters
}

void speedData::valsChanged( QString Mtr0, QString Mtr1, QString totFrames )
{
    if ( !speedD->simulationFrozen )
    {
        valuesChanged( Mtr0, Mtr1, totFrames );
    }
}

/**********************************************************************/
/* non-member functions                                               */
/**********************************************************************/

int setSpd( speedData *speedD )
{
    int time = speedD->totalFrames % (TOT_SECS * TICKS_PER_SEC);

    if ( time < TOT_SECS_UP * TICKS_PER_SEC )
    {
        // "up" range
        return MAX_MPH * time / (TOT_SECS_UP * TICKS_PER_SEC);
    }
    else if ( time < (TOT_SECS_UP + TOT_SECS_STDY) * TICKS_PER_SEC )
    {
        // "steady range
        return MAX_MPH;
    }

    if ( time < (TOT_SECS_UP + TOT_SECS_STDY + TOT_SECS_DOWN) * TICKS_PER_SEC )
    {
        // "down" range
        int time2 = time - (TOT_SECS_UP + TOT_SECS_STDY) * TICKS_PER_SEC;

        return MAX_MPH - (MAX_MPH * time2 / (TOT_SECS_DOWN * TICKS_PER_SEC));
    }
    else
    {
        // "stop" range
        return 0;
    }
}

/**********************************************************************/

int setRpm( speedData *speedD )
{
    int time = speedD->totalFrames % (TOT_SECS * TICKS_PER_SEC);

    if ( time < TOT_SECS_UP * TICKS_PER_SEC )
    {
        // "up" range
        int time2 = time % (TOT_SECS_UP * TICKS_PER_SEC / 4);
        return MIN_RPM + (RANGE_RPM * time2 / (TOT_SECS_UP * TICKS_PER_SEC / 4));
    }
    else if ( time < (TOT_SECS_UP + TOT_SECS_STDY) * TICKS_PER_SEC )
    {
        // "steady range
        return MIN_RPM + RANGE_RPM;
    }
    else if ( time < (TOT_SECS_UP + TOT_SECS_STDY + TOT_SECS_DOWN) * TICKS_PER_SEC )
    {
        int time2 = time - (TOT_SECS_UP + TOT_SECS_STDY) * TICKS_PER_SEC;

        // "down" range
        return imax( MAX_RPM - (RANGE_RPM * time2 * 2 / (TOT_SECS_DOWN * TICKS_PER_SEC)), MIN_RPM );
    }
    else
    {
        // "stop" range
        return MIN_RPM;
    }
}

/**********************************************************************/

int spd2angle( float x )
{
    return ( (int)round( (float)x / S_RANGE * S_ANGL_RANGE ) / 2 + S_ANGL_BASE ) % 360;
}

/**********************************************************************/

int rpm2angle( float x )
{
    return ( (int)round( (float)x / T_RANGE * T_ANGL_RANGE ) + T_ANGL_BASE ) % 360;
}

/**********************************************************************/

void setAngles( speedData *speedD )
{
    // compute speed
    speedD->xmtr0 = setSpd( speedD );

    // set speedometer angle
    speedD->xmtr0 = spd2angle( (float)speedD->xmtr0 );

    // compute rpm
    speedD->xmtr1 = setRpm( speedD );

    // set tachometer angle
    speedD->xmtr1 = rpm2angle( (float)speedD->xmtr1 );
}

/**********************************************************************/
/*
 * Thread routine to drive the simulation
 */

void watchThread::run()
{
//char buf[16];

    msleep(250);  // allow for script engine to start before first "valsChanged()"

    // set initial constant values
    speedD->xmtr0 = spd2angle( (float)0 );
    speedD->xmtr1 = rpm2angle( (float)MIN_RPM );
    /*
    speedD->valsChanged( itoa(speedD->xmtr0, buf, 10),
                         itoa(speedD->xmtr1, buf, 10),
                         itoa( speedD->totalFrames, buf, 10 ) ); */
    speedD->valsChanged( QString::number(speedD->xmtr0),
                         QString::number(speedD->xmtr1),
                         QString::number( speedD->totalFrames) );


    msleep(1500);  // simulate engine start and power-on time

    // start normal operation
    while ( true )
    {
        msleep( MS_SLEEP );

        if ( !speedD->simulationFrozen )
        {
            speedD->totalFrames += 1;

            // set the speedometer and tachometer values to be passed into script
            setAngles( speedD );  // sets xmtr0 and xmtr1

            // inform script of changes
            speedD->valsChanged( QString::number(speedD->xmtr0),
                                 QString::number(speedD->xmtr1),
                                 QString::number( speedD->totalFrames) );
        }
        else
        {
            break;
        }
    }
}
