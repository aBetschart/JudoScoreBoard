///////////////////////////////////////////////////////////
//  Btn.cpp
//  Implementation of the Class Btn
//  Created on:      11-Nov-2017 14:37:54
//  Original author: Aaron
///////////////////////////////////////////////////////////

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "Btn.h"

#include <cassert>

#include "../../EvHandler/IBtnEvHandler.h"
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------
PltFrm::Btn* PltFrm::Btn::instance[PltFrm::Btn::nrOfBtns] = {0};

static const Hal::Gpio::GpioInit gpioInit[PltFrm::Btn::nrOfBtns] =
{
/*ipponBlBtn*/  {Hal::Gpio::dirInput, Hal::Gpio::portA, Hal::Gpio::pin7, Hal::Gpio::pullUpRes, false},
/*wazariBlBtn*/ {Hal::Gpio::dirInput, Hal::Gpio::portP, Hal::Gpio::pin3, Hal::Gpio::pullUpRes, false},
/*shidoBlBtn*/  {Hal::Gpio::dirInput, Hal::Gpio::portQ, Hal::Gpio::pin1, Hal::Gpio::pullUpRes, false},

/*ipponWhBtn*/  {Hal::Gpio::dirInput, Hal::Gpio::portM, Hal::Gpio::pin0, Hal::Gpio::pullUpRes, false},
/*wazariWhBtn*/ {Hal::Gpio::dirInput, Hal::Gpio::portH, Hal::Gpio::pin1, Hal::Gpio::pullUpRes, false},
/*shidoWhBtn*/  {Hal::Gpio::dirInput, Hal::Gpio::portK, Hal::Gpio::pin6, Hal::Gpio::pullUpRes, false},

/*startBtn*/    {Hal::Gpio::dirInput, Hal::Gpio::portM, Hal::Gpio::pin7, Hal::Gpio::pullUpRes, false},
/*stopBtn*/     {Hal::Gpio::dirInput, Hal::Gpio::portP, Hal::Gpio::pin5, Hal::Gpio::pullUpRes, false},

/*osaekBlBtn*/  {Hal::Gpio::dirInput, Hal::Gpio::portM, Hal::Gpio::pin6, Hal::Gpio::pullUpRes, false},
/*osaekWhBtn*/  {Hal::Gpio::dirInput, Hal::Gpio::portK, Hal::Gpio::pin7, Hal::Gpio::pullUpRes, false}
};
//--------------------------------------------------------------

namespace PltFrm
{
//--------------------------------------------------------------
Btn::Btn( const BtnInstance& btn ): mInst( btn ), mGpio( gpioInit[btn] )
{
    assert(instance[mInst] == 0);
    instance[mInst] = this;

    mGpio.registerOnEv(this);

    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
        evHandler[i] = 0;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
Btn::~Btn()
{
    instance[mInst] = 0;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Btn::disable()
{
    mGpio.setInterrupt( false );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Btn::enable()
{
    mGpio.setInterrupt( true );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Btn::registerOnEv(IBtnEvHandler* handler)
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] == 0 )
        {
            evHandler[i] = handler;
            break;
        }
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
PltFrm::Btn::BtnInstance Btn::getInstance()
{
    return mInst;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Btn::notify()
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] != 0 )
            evHandler[i]->onButtonEv( mInst );
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Btn::onGpioEv(const Hal::Gpio& gpio)
{
    if ( mGpio == gpio )
        notify();
}
//--------------------------------------------------------------
} /* namespace PltFrm*/
