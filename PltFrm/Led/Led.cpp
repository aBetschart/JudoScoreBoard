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
/*led0*/  {Hal::Gpio::dirOutput, Hal::Gpio::portN, Hal::Gpio::pin0, Hal::Gpio::noResistor, false},
/*led1*/  {Hal::Gpio::dirOutput, Hal::Gpio::portN, Hal::Gpio::pin1, Hal::Gpio::noResistor, false}
};

Led::Led( const LedInstance& inst ): mInst(inst), mGpio( gpioInit[inst] )
{
    assert( instance[mInst] == 0 );
    instance[mInst] = this;

    switch( mInst )
    {
    case led0:
        mGpio.setDriveStrength( Hal::Gpio::ma8 );
        break;

    case led1:
        mGpio.setDriveStrength( Hal::Gpio::ma8 );
        break;

    default:
        break;
    }
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
