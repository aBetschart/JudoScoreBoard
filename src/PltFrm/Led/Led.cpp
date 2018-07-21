///////////////////////////////////////////////////////////
//  Led.cpp
//  Implementation of the Class Led
//  Created on:      11-Nov-2017 15:48:09
//  Original author: Aaron
///////////////////////////////////////////////////////////

#include "Led.h"

#include <cassert>

namespace PltFrm
{

Led::Led* Led::instance[Led::nrOfLeds] = {0};

static const Hal::Gpio::GpioInit gpioInit[Led::nrOfLeds] =
{
/* gldnScrLed   */  {Hal::Gpio::dirOutput, Hal::Gpio::portN, Hal::Gpio::pin0, Hal::Gpio::noResistor, false},
/* winnerLed    */  {Hal::Gpio::dirOutput, Hal::Gpio::portN, Hal::Gpio::pin1, Hal::Gpio::noResistor, false},
/* fightOverLed */  {Hal::Gpio::dirOutput, Hal::Gpio::portE, Hal::Gpio::pin4, Hal::Gpio::noResistor, false},
/* TimeLed      */  {Hal::Gpio::dirOutput, Hal::Gpio::portC, Hal::Gpio::pin4, Hal::Gpio::noResistor, false}
};

Led::Led( const LedInstance& inst ): mInst(inst), mGpio( gpioInit[inst] )
{
    assert( instance[mInst] == 0 );
    instance[mInst] = this;
}


Led::~Led()
{
    instance[mInst] = 0;
}


void Led::turnOff()
{
    mGpio.set( false );
}


void Led::turnOn()
{
    mGpio.set( true );
}

void Led::toggle()
{
    if( this->isTurnedOn() )
        this->turnOff();
    else
        this->turnOn();
}

bool Led::isTurnedOn() const
{
    return ( mGpio.isSet() );
}

} /* namespace PltFrm */
