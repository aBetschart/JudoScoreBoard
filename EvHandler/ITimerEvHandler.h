/*
 * ITimerEvHandler.h
 *
 *  Created on: 25.10.2017
 *      Author: aaron
 */

#ifndef ITIMEREVHANDLER_H_
#define ITIMEREVHANDLER_H_

#include "../Hal/Timer/Timer.h"

class ITimerEvHandler
{
public:
    virtual void onTimerEv( const Hal::Timer::Timer& timer,
                               const Hal::Timer::TimerEv ev ) = 0;

};

#endif /* ITIMEREVHANDLER_H_ */
