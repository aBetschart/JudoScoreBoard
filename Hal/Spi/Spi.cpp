
//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "Spi.h"

#include <cassert>
#include <new>

#include "../../EvHandler/ISpiEvHandler.h"
#include "../Nvic/Nvic.h"
#include "../HwRegister/HwRegister.h"
#include "../Gpio/Gpio.h"
#include "../Rcgc/Rcgc.h"
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- wrapper functions for interrupts
//--------------------------------------------------------------
extern "C"
{
//--------------------------------------------------------------
void ssi0CallBackWr(void)
{
    Hal::Spi::ssi0CallBack();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void ssi1CallBackWr(void)
{
    Hal::Spi::ssi1CallBack();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void ssi2CallBackWr(void)
{
    Hal::Spi::ssi2CallBack();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void ssi3CallBackWr(void)
{
    Hal::Spi::ssi3CallBack();
}
//--------------------------------------------------------------
}
//--------------------------------------------------------------


namespace Hal
{
Spi::Spi* Spi::instance[nrOfSpi] = {0};

//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------
static const uint32_t spiBaseAddr[Spi::nrOfSpi] =
{ 0x40008000,
  0x40009000,
  0x4000A000,
  0x4000B000
};

static const Hal::Nvic::irInstance irInst[Hal::Spi::nrOfSpi] =
{ Nvic::ssi0, Nvic::ssi1, Nvic::ssi2, Nvic::ssi3 };

static const uint16_t irBitMask[Hal::Spi::nrOfSpiEvs] =
{ 0x01, 0x02, 0x04, 0x08, 0x40 };

static const uint16_t irClearBitMask[Hal::Spi::nrOfSpiEvs] =
{ 0x01, 0x02, 0x00, 0x00, 0x40 };
//--------------------------------------------------------------

//--------------------------------------------------------------
Spi::Spi( const SpiInit& init ): mInst( init.inst ), mDir( init.direction )
{
    assert( instance[mInst] == 0 );
    instance[mInst] = this;

    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
        evHandler[i] = 0;

    // enable QSSI-module at RCGC-module
    Rcgc::enaSsiModule( mInst );

    dataReg = new (reinterpret_cast<void*>(spiBaseAddr[mInst] + 0x0008)) Hal::HwRegister<uint16_t>;
    HwRegister<uint16_t>* ctrlReg0    = new (reinterpret_cast<void*>(spiBaseAddr[mInst] + 0x0000)) Hal::HwRegister<uint16_t>;
    ctrlReg1    = new (reinterpret_cast<void*>(spiBaseAddr[mInst] + 0x0004)) Hal::HwRegister<uint16_t>;
    HwRegister<uint8_t>*  clkPrescReg = new (reinterpret_cast<void*>(spiBaseAddr[mInst] + 0x0010)) Hal::HwRegister<uint8_t>;

    // initialize pins
    switch( mInst )
    {
    case spi0:
    {
        Gpio clkPin( Gpio::portA, Gpio::pin2, Gpio::dig15 );
        if( init.spo )
            clkPin.setPinCfg( Gpio::pullUpRes, false );
        if( init.enaFss )
        {
            // just initialized if slave select is needed
            Gpio FssPin( Gpio::portA, Gpio::pin3, Gpio::dig15 );
            FssPin.setPinCfg( Gpio::pullUpRes, false );
        }
        if( init.direction == transmit )
        {
            // init Rx-Pin
            Gpio recPin( Gpio::portA, Gpio::pin4, Gpio::dig15 );
        }
        else
        {
            // init Tx-Pin
            Gpio traPin( Gpio::portA, Gpio::pin5, Gpio::dig15 );
        }
        break;
    }
    case spi1:
    {
        Gpio clkPin( Gpio::portB, Gpio::pin5, Gpio::dig15 );
        if( init.spo )
            clkPin.setPinCfg( Gpio::pullUpRes, false );
        if( init.enaFss )
        {
            // just initialized if slave select is needed
            Gpio FssPin( Gpio::portB, Gpio::pin4, Gpio::dig15 );
            FssPin.setPinCfg( Gpio::pullUpRes, false );
        }
        if( init.direction == transmit )
        {
            // init Rx-Pin
            Gpio recPin( Gpio::portE, Gpio::pin4, Gpio::dig15 );
        }
        else
        {
            // init Tx-Pin
            Gpio traPin( Gpio::portE, Gpio::pin5, Gpio::dig15 );
        }
        break;
    }
    case spi2:
    {
        Gpio clkPin( Gpio::portD, Gpio::pin3, Gpio::dig15 );
        if( init.spo )
            clkPin.setPinCfg( Gpio::pullUpRes, false );
        if( init.enaFss )
        {
            // just initialized if slave select is needed
            Gpio FssPin( Gpio::portD, Gpio::pin2, Gpio::dig15 );
            FssPin.setPinCfg( Gpio::pullUpRes, false );
        }
        if( init.direction == transmit )
        {
            // init Rx-Pin
            Gpio recPin( Gpio::portD, Gpio::pin1, Gpio::dig15 );
        }
        else
        {
            // init Tx-Pin
            Gpio traPin( Gpio::portD, Gpio::pin0, Gpio::dig15 );
        }
        break;
    }
    case spi3:
    {
        Gpio clkPin( Gpio::portF, Gpio::pin3, Gpio::dig14 );
        if( init.spo )
            clkPin.setPinCfg( Gpio::pullUpRes, false );
        if( init.enaFss )
        {
            // just initialized if slave select is needed
            Gpio FssPin( Gpio::portF, Gpio::pin2, Gpio::dig14 );
            FssPin.setPinCfg( Gpio::pullUpRes, false );
        }
        if( init.direction == transmit )
        {
            // init Rx-Pin
            Gpio recPin( Gpio::portF, Gpio::pin1, Gpio::dig14 );
        }
        else
        {
            // init Tx-Pin
            Gpio traPin( Gpio::portF, Gpio::pin0, Gpio::dig14 );
        }
        break;
    }
    default:
        break;
    }

    ctrlReg1->clearBits(0x0002); // disable ssi module

    if( init.type == slave )
        ctrlReg1->setBits(0x4);
    else
        ctrlReg1->clearBits(0x4);

    // setting the prescaler-value
    clkPrescReg->clearBits(0xFF);
    clkPrescReg->setBits(init.cpsvdr);

    // setting sumScale
    ctrlReg0->setBits( init.scr << 8 );

    // setting clock phase
    if( init.sph )
        ctrlReg0->setBits(0x80);
    else
        ctrlReg0->clearBits(0x80);

    ctrlReg1->setBits(0x200); // hold Fss-signal for the whole frame

    // setting clock polarity
    if( init.spo )
        ctrlReg0->setBits(0x40);
    else
        ctrlReg0->clearBits(0x40);

    // enable freescale SPI-mode
    ctrlReg0->clearBits(0x30);

    // adjust datasize
    ctrlReg0->clearBits(0xF);

    if( init.dataSize < 0x3 )
    {
        ctrlReg0->setBits(0x3);
    }
    else if( init.dataSize > 0xF )
    {
        ctrlReg0->setBits(0xF);
    }
    else
    {
        ctrlReg0->setBits(init.dataSize);
    }

    if( mDir == receive )
        ctrlReg1->setBits(0x2); // enable ssi module

    setModuleIr( init.enaIr );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
Spi::~Spi()
{
    instance[mInst] = 0;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Spi::insertMsg(const uint16_t& msg)
{
    dataReg->insert( msg );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
uint16_t Spi::getMsg()
{
    return( dataReg->getVal() );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Spi::setModule(const bool& on)
{
    if(on)
    {
        ctrlReg1->setBits(0x2); // enable module
    }
    else
    {
        ctrlReg1->clearBits(0x2); // disable module
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Spi::setModuleIr(const bool& on)
{
    if( on )
    {
        Hal::Nvic::enableIr( irInst[mInst] );
    }
    else
    {
        Hal::Nvic::disableIr( irInst[mInst] );
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Spi::enableIr(const SpiEv& ev)
{
    HwRegister<uint8_t>* irMaskReg = new (reinterpret_cast<void*>(spiBaseAddr[mInst] + 0x0014)) Hal::HwRegister<uint8_t>;
    irMaskReg->setBits( irBitMask[ev] );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Spi::disableIr(const SpiEv& ev)
{
    HwRegister<uint8_t>* irMaskReg = new (reinterpret_cast<void*>(spiBaseAddr[mInst] + 0x0014)) Hal::HwRegister<uint8_t>;
    irMaskReg->clearBits( irBitMask[ev] );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Spi::registerOnEv( ISpiEvHandler* handler )
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
void Spi::ssi0CallBack()
{
    checkIrStatus( spi0 );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Spi::ssi1CallBack()
{
    checkIrStatus( spi1 );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Spi::ssi2CallBack()
{
    checkIrStatus( spi2 );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Spi::ssi3CallBack()
{
    checkIrStatus( spi3 );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Spi::notify(const SpiEv& ev)
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] != 0 )
        {
            evHandler[i]->onSpiEv( mInst, ev );
        }
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Spi::checkIrStatus(const SpiInstance& inst)
{
    HwRegister<uint8_t>* irStatReg  = new (reinterpret_cast<void*>(spiBaseAddr[inst] + 0x001C)) Hal::HwRegister<uint8_t>;
    HwRegister<uint8_t>* irClearReg = new (reinterpret_cast<void*>(spiBaseAddr[inst] + 0x0020)) Hal::HwRegister<uint8_t>;

    if( instance[inst] != 0 )
    {
        for( int i = 0 ; i < nrOfSpiEvs ; ++i )
        {
            if( irStatReg->checkBits( irBitMask[i] ) )
            {
                instance[inst]->notify( static_cast<SpiEv>(i) );
                irClearReg->setBits(irClearBitMask[i]);
            }
        }
    }
}
//--------------------------------------------------------------

} /* namespace Hal */
