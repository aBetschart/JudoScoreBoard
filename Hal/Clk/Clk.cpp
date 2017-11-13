/*
 * Clk.cpp
 *
 *  Created on: 10.11.2017
 *      Author: aaron
 */

#include "Clk.h"

#include<new>

#include "../HwRegister/HwRegister.h"
#include "../Pll/Pll.h"

namespace Hal
{

static const uint32_t clkFreq[Hal::Clk::nrOfClkSources] =
{
 16000000, 33000, 25000000, 32768
};

//--------------------------------------------------------------
void Hal::Clk::setClkSource(const ClkSource& clk)
{
    HwRegister<uint32_t>* rsClkCfgReg = new (reinterpret_cast<void*>( 0x400FE0B0 )) Hal::HwRegister<uint32_t>;

    rsClkCfgReg->clearBits(0x00F00000);

    switch( clk )
    {
    case lfiosc:
        rsClkCfgReg->setBits(0x00200000);
        break;
    case mosc:
    {
        HwRegister<uint8_t>* moscCtlReg = new (reinterpret_cast<void*>( 0x400FE07C )) Hal::HwRegister<uint8_t>;
        moscCtlReg->setBits(0x08); // power down mosc
        rsClkCfgReg->setBits(0x00300000); // set mosc to clk source
        moscCtlReg->clearBits(0x08); // power up mosc
        break;
    }
    case rtcosc:
        rsClkCfgReg->setBits(0x00400000);
        break;
    default: // nothing to do at PIOSC
        break;
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
Clk::ClkSource Clk::getOscClkSource()
{
    HwRegister<uint32_t>* rsClkCfgReg = new (reinterpret_cast<void*>( 0x400FE0B0 )) Hal::HwRegister<uint32_t>;
    uint32_t clk = rsClkCfgReg->getVal();
    ClkSource clkSrc = piosc;

    clk &= 0xFF0FFFFF;

    clk = clk >> 20;

    switch(clk)
    {
    case 0x00000000:
        clkSrc = piosc;
        break;
    case 0x00000002:
        clkSrc = lfiosc;
        break;
    case 0x00000003:
        clkSrc = mosc;
        break;
    case 0x00000004:
        clkSrc = rtcosc;
        break;
    }

    return clkSrc;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Hal::Clk::setPllClkSource(const ClkSource& clk)
{
    HwRegister<uint32_t>* rsClkCfgReg = new (reinterpret_cast<void*>( 0x400FE0B0 )) Hal::HwRegister<uint32_t>;

    if( clk == piosc )
    {
        rsClkCfgReg->clearBits(0x0F000000);
    }
    else if( clk == mosc )
    {
        rsClkCfgReg->clearBits(0x0F000000);
        rsClkCfgReg->setBits(0x03000000);
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Hal::Clk::setOscClkDivisor(const uint16_t& div)
{
    HwRegister<uint32_t>* rsClkCfgReg = new (reinterpret_cast<void*>( 0x400FE0B0 )) Hal::HwRegister<uint32_t>;
    uint16_t shortDiv = (div & 0x03FF); // just size of 10 bits

    rsClkCfgReg->clearBits( (0x000003FF << 10) );
    rsClkCfgReg->setBits( (shortDiv << 10) );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
uint16_t Clk::getOscClkDivisor()
{
    HwRegister<uint32_t>* rsClkCfgReg = new (reinterpret_cast<void*>( 0x400FE0B0 )) Hal::HwRegister<uint32_t>;
    uint32_t longVal = rsClkCfgReg->getVal();

    longVal =  longVal >> 10;
    longVal &= 0x000003FF;

    return( uint16_t( longVal ) );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Hal::Clk::setPllClkDivisor(const uint16_t& div)
{
    HwRegister<uint32_t>* rsClkCfgReg = new (reinterpret_cast<void*>( 0x400FE0B0 )) Hal::HwRegister<uint32_t>;
    uint16_t shortDiv = (div & 0x03FF); // just size of 10 bits

    rsClkCfgReg->clearBits( 0x000003FF );
    rsClkCfgReg->setBits( shortDiv );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
uint16_t Clk::getPllClkDivisor()
{
    HwRegister<uint32_t>* rsClkCfgReg = new (reinterpret_cast<void*>( 0x400FE0B0 )) Hal::HwRegister<uint32_t>;
    uint32_t longVal = rsClkCfgReg->getVal();

    longVal &= 0x000003FF;

    return( uint16_t( longVal ) );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
Clk::ClkSource Clk::getPllClkSource()
{
    HwRegister<uint32_t>* rsClkCfgReg = new (reinterpret_cast<void*>( 0x400FE0B0 )) Hal::HwRegister<uint32_t>;
    uint32_t clk = rsClkCfgReg->getVal();
    ClkSource clkSrc = piosc;

    rsClkCfgReg->clearBits(0xF0FFFFFF);

    clk = clk >> 24;

    switch(clk)
    {
    case 0x00000000:
        clkSrc = piosc;
    case 0x00000003:
        clkSrc = mosc;
    }

    return clkSrc;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
uint32_t Clk::getClkFreq()
{
    if( Hal::Clk::pllEnabled() )
    {
        uint16_t div = getPllClkDivisor();
        return ( Hal::Pll::getPllFreq()/(div+1) );
    }
    else
    {
        ClkSource clkSrc = getOscClkSource();
        uint16_t div = getOscClkDivisor();

        return (clkFreq[clkSrc]/(div+1));
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
uint32_t Clk::getRawClkFreq(const ClkSource& clk)
{
    return( clkFreq[clk] );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool Clk::pllEnabled()
{
    HwRegister<uint32_t>* rsClkCfgReg = new (reinterpret_cast<void*>( 0x400FE0B0 )) Hal::HwRegister<uint32_t>;

    return( rsClkCfgReg->checkBits(0x10000000) );
}
//--------------------------------------------------------------
} /* namespace Hal */
