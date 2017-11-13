///////////////////////////////////////////////////////////
//  TimeTick.cpp
//  Implementation of the Class TimeTick
//  Created on:      12-Nov-2017 20:06:50
//  Original author: Aaron
///////////////////////////////////////////////////////////

#include "TimeTick.h"

#include<cassert>
#include<stdint.h>

#include "../../Hal/Clk/Clk.h"
#include "../../EvHandler/ITimeTickEvHandler.h"

static const Hal::Timer::TimerInit timerInit[PltFrm::TimeTick::nrOfTimeTicks] =
{
/*mainTimeTick*/  {Hal::Timer::timer0, Hal::Timer::subTimerA, true,  Hal::Timer::periodic, Hal::Timer::up},
/*osaekTimeTick*/ {Hal::Timer::timer1, Hal::Timer::subTimerA, true,  Hal::Timer::periodic, Hal::Timer::up},
/*scoreBtnTick*/  {Hal::Timer::timer2, Hal::Timer::subTimerA, false, Hal::Timer::periodic, Hal::Timer::up},
/*timeBtnTick*/   {Hal::Timer::timer2, Hal::Timer::subTimerB, false, Hal::Timer::periodic, Hal::Timer::up}
};

static const uint16_t msInterval[PltFrm::TimeTick::nrOfTimeTicks] =
{
 1000, 1000, 300, 300
};

namespace PltFrm
{

TimeTick::TimeTick* TimeTick::instance[TimeTick::nrOfTimeTicks] = {0};

TimeTick::TimeTick( const TimeTickInstance& t ):
mInst( t ), mTimer( timerInit[t] )
{
    assert( instance[mInst] == 0 );
    instance[mInst] = this;

    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
        evHandler[i] = 0;

    mTimer.registerOnEv( this );
    mTimer.enableIr( Hal::Timer::evTimeOut );

    // set interval border
    uint32_t interval = Hal::Clk::getClkFreq()/1000;
    interval *= msInterval[mInst];
    interval--; // because it begins to count at zero
    mTimer.setIntervalBorder( interval );

    mTimer.setModuleIr( true );
}

TimeTick::~TimeTick()
{
    instance[mInst] = 0;
}


void TimeTick::enable()
{
    mTimer.start();
}

void TimeTick::disable()
{
    mTimer.stop();
}


void TimeTick::registerOnEv( ITimeTickEvHandler* handler )
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] == 0 )
            evHandler[i] = handler;
    }
}

void TimeTick::onTimerEv(const Hal::Timer::Timer& timer,
                         const Hal::Timer::TimerEv ev)
{
    if( (ev == Hal::Timer::evTimeOut) && (mTimer == timer) )
        notify();
}

PltFrm::TimeTick::TimeTickInstance TimeTick::getInstance()
{
    return mInst;
}

void TimeTick::notify()
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] != 0 )
            evHandler[i]->onTimeTickEv( mInst );
    }
}

} /* namespace PltFrm*/
