///////////////////////////////////////////////////////////
//  Switch.cpp
//  Implementation of the Class Switch
//  Created on:      27-Nov-2017 22:02:12
//  Original author: aaron
///////////////////////////////////////////////////////////

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "Switch.h"

#include <cassert>
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------
PltFrm::Switch::Switch* PltFrm::Switch::instance[PltFrm::Switch::nrOfSwitches] = {0};

static const Hal::Gpio::GpioInit gpioInit[PltFrm::Switch::nrOfSwitches] =
{
/* scoreSwitch */  {Hal::Gpio::dirInput, Hal::Gpio::portA, Hal::Gpio::pin0, Hal::Gpio::noResistor, false}
};
//--------------------------------------------------------------

namespace PltFrm
{

//--------------------------------------------------------------
Switch::Switch( const SwitchInstance& inst ):
        mGpio( gpioInit[inst] ), mInst( inst )
{
    assert( instance[mInst] == 0 );
    instance[mInst] = this;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
Switch::~Switch()
{
    instance[mInst] = 0;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool Switch::isSet() const
{
    return( mGpio.isSet() );
}
//--------------------------------------------------------------
} /* namespace PltFrm */
