/*
 * Gpio.cpp
 *
 *  Created on: 29.07.2017
 *      Author: Aaron
 */

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "Gpio.h"

#include <new>
#include <cassert>

#include "../RegisterAddress/GpioRegisterAddress.h"
#include "../../Register/RegisterAllocator.h"
#include "../Nvic/Nvic.h"
#include "../Rcgc/Rcgc.h"
#include "../../EvHandler/IGpioEvHandler.h"
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- wrapper functions for interrupts
//--------------------------------------------------------------
extern "C"
{
void gpioCallBackPortAWr(void)
{
    Hal::Gpio::gpioCallBackPortA();
}

void gpioCallBackPortBWr(void)
{
    Hal::Gpio::gpioCallBackPortB();
}

void gpioCallBackPortCWr(void)
{
    Hal::Gpio::gpioCallBackPortC();
}

void gpioCallBackPortDWr(void)
{
    Hal::Gpio::gpioCallBackPortD();
}

void gpioCallBackPortEWr(void)
{
    Hal::Gpio::gpioCallBackPortE();
}

void gpioCallBackPortFWr(void)
{
    Hal::Gpio::gpioCallBackPortF();
}

void gpioCallBackPortGWr(void)
{
    Hal::Gpio::gpioCallBackPortG();
}

void gpioCallBackPortHWr(void)
{
    Hal::Gpio::gpioCallBackPortH();
}

void gpioCallBackPortJWr(void)
{
    Hal::Gpio::gpioCallBackPortJ();
}

void gpioCallBackPortKWr(void)
{
    Hal::Gpio::gpioCallBackPortK();
}

void gpioCallBackPortLWr(void)
{
    Hal::Gpio::gpioCallBackPortL();
}

void gpioCallBackPortMWr(void)
{
    Hal::Gpio::gpioCallBackPortM();
}

void gpioCallBackPortNWr(void)
{
    Hal::Gpio::gpioCallBackPortN();
}

void gpioCallBackPortPWr(void)
{
    Hal::Gpio::gpioCallBackPortP();
}

void gpioCallBackPortQWr(void)
{
    Hal::Gpio::gpioCallBackPortQ();
}
}
//--------------------------------------------------------------

namespace Hal
{

//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------
static const Hal::Nvic::InterruptInstance interruptInstance[Hal::Gpio::nrOfGpioPorts] =
{
 Nvic::gpioPortA, Nvic::gpioPortB, Nvic::gpioPortC,
 Nvic::gpioPortD, Nvic::gpioPortE, Nvic::gpioPortF,
 Nvic::gpioPortG, Nvic::gpioPortH, Nvic::gpioPortJ,
 Nvic::gpioPortK, Nvic::gpioPortL, Nvic::gpioPortM,
 Nvic::gpioPortN, Nvic::gpioPortP, Nvic::gpioPortQ,
};

Gpio* Hal::Gpio::instance[Gpio::nrOfGpioPorts][Gpio::nrOfPins] = {0};
//--------------------------------------------------------------


//--------------------------------------------------------------
Gpio::Gpio( const GpioInit& init ): mBit( 0x01 << init.nr ), mPort( init.port )
{
    assert( instance[init.port][init.nr] == 0 );

    instance[init.port][init.nr] = this;

    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
        evHandler[i] = 0;

    Rcgc::enaGpioPort( mPort );

    // mapping of the registers
    dataReg 	= Register::RegisterAllocator<uint8_t>::allocateRegister( gpioBaseAddr[mPort] + dataRegisterOffset );
    irMaskReg 	= Register::RegisterAllocator<uint8_t>::allocateRegister( gpioBaseAddr[mPort] + interruptMaskRegisterOffset );
    int directionRegisterAddress = gpioBaseAddr[mPort] + directionRegisterOffset;
    Register::RegisterInterface<uint8_t>* dirReg = Register::RegisterAllocator<uint8_t>::allocateRegister( directionRegisterAddress );

    // direction setting
    if( init.dir == dirInput )
    {
        inp = true;
        dirReg->clearBits(mBit);
    }
    else // init.dir == dirOutput
    {
        inp = false;
        dirReg->setBits(mBit);
    }
    setPinCfg(init.outCfg, init.openDrain);
    setSpecialFunc( Gpio::noSpecFunc );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
Gpio::Gpio(const GpioPort& port, const GpioPinNr& pin, const GpioFunc& f):
        mBit( 0x1 << pin ), mPort( port )
{
    Rcgc::enaGpioPort( mPort );
    setSpecialFunc( f );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
Gpio::~Gpio()
{
	int mPin = 0;
	
	while( mBit != 0x01 )
	{
	    mPin++;
	    mBit = mBit >> 1;
	}

    instance[mPort][mPin] = 0;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Gpio::setSpecialFunc(const GpioFunc& f)
{
	int registerAddress = gpioBaseAddr[mPort] + alternateFunctionSelRegisterOffset;
    Register::RegisterInterface<uint8_t>* afSelReg = Register::RegisterAllocator<uint8_t>::allocateRegister( registerAddress );
    registerAddress = gpioBaseAddr[mPort] + digitalEnableRegisterOffset;
    Register::RegisterInterface<uint8_t>* denReg   = Register::RegisterAllocator<uint8_t>::allocateRegister( registerAddress );
    registerAddress = gpioBaseAddr[mPort] + analogModeSelRegisterOffset;
    Register::RegisterInterface<uint8_t>* aenReg   = Register::RegisterAllocator<uint8_t>::allocateRegister( registerAddress );
    registerAddress = gpioBaseAddr[mPort] + portCtrlRegisterOffset;
    Register::RegisterInterface<uint32_t>* ctlReg  = Register::RegisterAllocator<uint32_t>::allocateRegister( registerAddress );

    if( f != noSpecFunc ) // Special function requested
    {
        int bitNr = 0;
        int i = mBit;

        while( i != 0x01 )
        {
            i = i >> 1;
            bitNr++;
        }

        uint8_t shiftVal = bitNr*4;

        afSelReg->setBits( mBit );
        ctlReg->clearBits( 0x0000000F << shiftVal );
        ctlReg->setBits( f << shiftVal );
        if( f == analogFunc )
        {
            denReg->clearBits(mBit);
            aenReg->setBits(mBit);
        }
        else // digital function
        {
            aenReg->clearBits(mBit);
            denReg->setBits(mBit);
        }
    }
    else // normal gpio (no special function)
    {
        afSelReg->clearBits(mBit);
        aenReg->clearBits(mBit);
        denReg->setBits(mBit);
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Gpio::setDriveStrength(const GpioDrStr& str)
{
    Register::RegisterInterface<uint8_t>* driveReg = Register::RegisterAllocator<uint8_t>::allocateRegister( gpioBaseAddr[mPort] + str );
    driveReg->setBits(mBit);
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Gpio::setPinCfg(const GpioPinResistor& res, const bool& openDrain)
{
	int registerAddress = gpioBaseAddr[mPort] + pullUpSelRegisterOffset;
	Register::RegisterInterface<uint8_t>* pullUpReg = Register::RegisterAllocator<uint8_t>::allocateRegister( registerAddress );
	registerAddress = gpioBaseAddr[mPort] + pullDownSelRegisterOffset;
	Register::RegisterInterface<uint8_t>* pullDnReg = Register::RegisterAllocator<uint8_t>::allocateRegister( registerAddress );
	registerAddress = gpioBaseAddr[mPort] + openDrainSelRegisterOffset;
	Register::RegisterInterface<uint8_t>* odSelReg  = Register::RegisterAllocator<uint8_t>::allocateRegister( registerAddress );

    switch( res )
    {
    case pullUpRes:
        pullUpReg->setBits(mBit);
        break;

    case pullDownRes:
        pullDnReg->setBits(mBit);
        break;

    case noResistor:
    	pullUpReg->clearBits(mBit);
    	pullDnReg->clearBits(mBit);
    	break;

    default:
        break;
    }

    if( openDrain )
        odSelReg->setBits(mBit);
    else
        odSelReg->clearBits(mBit);

}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Gpio::setInterrupt(const bool& on)
{
	int registerAddress = gpioBaseAddr[mPort] + interruptClearRegisterOffset;
    Register::RegisterInterface<uint8_t>* irClearReg  = Register::RegisterAllocator<uint8_t>::allocateRegister( registerAddress );
    irClearReg->setBits(mBit);
    if(on)
    {
        irMaskReg->setBits(mBit);
        Hal::Nvic::enableIr( interruptInstance[mPort] );
    }
    else
    {
        irMaskReg->clearBits(mBit);
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Gpio::configIr(const GpioIrEv& ev)
{
	int registerAddress = gpioBaseAddr[mPort] + interruptBothEdgesRegisterOffset;
    Register::RegisterInterface<uint8_t>* bothEdgeReg = Register::RegisterAllocator<uint8_t>::allocateRegister( registerAddress );
    registerAddress = gpioBaseAddr[mPort] + interruptEventRegisterOffset;
    Register::RegisterInterface<uint8_t>* irEvReg     = Register::RegisterAllocator<uint8_t>::allocateRegister( registerAddress );
    registerAddress = gpioBaseAddr[mPort] + interruptClearRegisterOffset;
    Register::RegisterInterface<uint8_t>* irClearReg  = Register::RegisterAllocator<uint8_t>::allocateRegister( registerAddress );
    registerAddress = gpioBaseAddr[mPort] + interruptSenseRegisterOffset;
    Register::RegisterInterface<uint8_t>* irSenseReg  = Register::RegisterAllocator<uint8_t>::allocateRegister( registerAddress );

    irSenseReg->clearBits(mBit);
    irClearReg->setBits(mBit);
    irMaskReg->setBits(mBit);
    if( ev == evBothEdge )
    {
        bothEdgeReg->setBits(mBit);
    }
    else
    {
        bothEdgeReg->clearBits(mBit);
        if( ev == evRisingEdge )
            irEvReg->setBits(mBit);
        else
            irEvReg->clearBits(mBit);
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Gpio::registerOnEv( IGpioEvHandler* const handler )
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
bool Gpio::isSet() const
{
    return( dataReg->checkBits(mBit) );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Gpio::set( const bool& on )
{
    if( !inp )
    {
        if( on )
        {
            dataReg->setBits(mBit);
        }
        else
        {
            dataReg->clearBits(mBit);
        }
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool Gpio::operator ==(const Gpio& gpio)
{
    return( gpio.mPort == this->mPort &&
            gpio.mBit  == this->mBit );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Gpio::notify()
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] != 0 )
            evHandler[i]->onGpioEv( *this );
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Gpio::checkIrStatus(const GpioPort& p)
{
	int registerAddress = Hal::gpioBaseAddr[p] + maskedInterruptStatusRegisterOffset;
	Register::RegisterInterface<uint8_t>* irStatReg = Register::RegisterAllocator<uint8_t>::allocateRegister( registerAddress );
	registerAddress = Hal::gpioBaseAddr[p] + interruptClearRegisterOffset;
	Register::RegisterInterface<uint8_t>* irClearReg = Register::RegisterAllocator<uint8_t>::allocateRegister( registerAddress );

    uint8_t checkBit = 0x01;
    for( int i = 0 ; i < nrOfPins ; ++i )
    {
        if( irStatReg->checkBits(checkBit) )
        {
            irClearReg->setBits(checkBit);
            if( instance[p][i] != 0 )
                instance[p][i]->notify();
        }
        checkBit = checkBit << 1;
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- Interrupt callback functions
//--------------------------------------------------------------
void Gpio::gpioCallBackPortA()
{
    checkIrStatus( portA );
}

void Gpio::gpioCallBackPortB()
{
    checkIrStatus( portB );
}

void Gpio::gpioCallBackPortC()
{
    checkIrStatus( portC );
}

void Gpio::gpioCallBackPortD()
{
    checkIrStatus( portD );
}

void Gpio::gpioCallBackPortE()
{
    checkIrStatus( portE );
}

void Gpio::gpioCallBackPortF()
{
    checkIrStatus( portF );
}

void Gpio::gpioCallBackPortG()
{
    checkIrStatus( portG );
}

void Gpio::gpioCallBackPortH()
{
    checkIrStatus( portH );
}

void Gpio::gpioCallBackPortJ()
{
    checkIrStatus( portJ );
}

void Gpio::gpioCallBackPortK()
{
    checkIrStatus( portK );
}

void Gpio::gpioCallBackPortL()
{
    checkIrStatus( portL );
}

void Gpio::gpioCallBackPortM()
{
    checkIrStatus( portM );
}

void Gpio::gpioCallBackPortN()
{
    checkIrStatus( portN );
}

void Gpio::gpioCallBackPortP()
{
    checkIrStatus( portP );
}

void Gpio::gpioCallBackPortQ()
{
    checkIrStatus( portQ );
}
//--------------------------------------------------------------

} /* namespace Hal */
