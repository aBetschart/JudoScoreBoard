/*
 * Pll.cpp
 *
 *  Created on: 03.11.2017
 *      Author: aaron
 */

#include "Pll.h"

#include <new>

#include "../HwRegister/HwRegister.h"
#include "../Clk/Clk.h"

namespace Hal
{
//--------------------------------------------------------------
void Hal::Pll::enablePll()
{
    HwRegister<uint32_t>* pllF0Reg    = new (reinterpret_cast<void*>( 0x400FE160 )) Hal::HwRegister<uint32_t>;
    HwRegister<uint32_t>* rsclkcfgReg = new (reinterpret_cast<void*>( 0x400FE0B0 )) Hal::HwRegister<uint32_t>;

    pllF0Reg->setBits( 0x00800000 ); // power the PLL
    rsclkcfgReg->setBits( 0x50000000 ); // activate PLL-registers
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Hal::Pll::disablePll()
{
    HwRegister<uint32_t>* pllF0Reg    = new (reinterpret_cast<void*>( 0x400FE160 )) Hal::HwRegister<uint32_t>;
    HwRegister<uint32_t>* rsclkcfgReg = new (reinterpret_cast<void*>( 0x400FE0B0 )) Hal::HwRegister<uint32_t>;

    pllF0Reg->clearBits( 0x00800000 ); // power the PLL
    rsclkcfgReg->clearBits( 0x10000000 ); // activate PLL-registers
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Hal::Pll::setM(const uint8_t& val)
{
    HwRegister<uint32_t>* pllF1Reg    = new (reinterpret_cast<void*>( 0x400FE164 )) Hal::HwRegister<uint32_t>;

    uint8_t shortVal = val & 0x1F; // M has just the size of five bits

    pllF1Reg->clearBits(0x1F);
    pllF1Reg->setBits( shortVal );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
uint8_t Pll::getM()
{
    HwRegister<uint32_t>* pllF1Reg    = new (reinterpret_cast<void*>( 0x400FE164 )) Hal::HwRegister<uint32_t>;
    uint32_t val = pllF1Reg->getVal();

    val &= 0x0000001F;

    return( uint8_t(val) );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Hal::Pll::setQ(const uint8_t& val)
{
    HwRegister<uint32_t>* pllF1Reg    = new (reinterpret_cast<void*>( 0x400FE164 )) Hal::HwRegister<uint32_t>;

    uint8_t shortVal = val & 0x3F; // Q has just the size of six bits

    pllF1Reg->clearBits( 0x3F << 8 );
    pllF1Reg->setBits( shortVal << 8 );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
uint8_t Pll::getQ()
{
    HwRegister<uint32_t>* pllF1Reg    = new (reinterpret_cast<void*>( 0x400FE164 )) Hal::HwRegister<uint32_t>;
    uint32_t val = pllF1Reg->getVal();

    val = val >> 8;
    val &= 0x0000003F;

    return( uint8_t(val) );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Hal::Pll::setMint(const uint16_t& val)
{
    HwRegister<uint32_t>* pllF0Reg    = new (reinterpret_cast<void*>( 0x400FE160 )) Hal::HwRegister<uint32_t>;

    uint8_t shortVal = val & 0x03FF; // MINT has the size of 10 Bit

    pllF0Reg->clearBits( 0x03FF );
    pllF0Reg->setBits( shortVal );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
uint16_t Pll::getMint()
{
    HwRegister<uint32_t>* pllF0Reg    = new (reinterpret_cast<void*>( 0x400FE160 )) Hal::HwRegister<uint32_t>;
    uint32_t val = pllF0Reg->getVal();

    val &= 0x000003FF;

    return( uint16_t(val) );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Hal::Pll::setMfrac(const uint16_t& val)
{
    HwRegister<uint32_t>* pllF0Reg    = new (reinterpret_cast<void*>( 0x400FE160 )) Hal::HwRegister<uint32_t>;
    HwRegister<uint32_t>* pllF1Reg    = new (reinterpret_cast<void*>( 0x400FE164 )) Hal::HwRegister<uint32_t>;

    uint8_t shortVal = val & 0x03FF; // MINT has the size of 10 Bit

    pllF0Reg->clearBits(0x03FF << 10);
    pllF0Reg->setBits(shortVal << 10);
}
//--------------------------------------------------------------


//--------------------------------------------------------------
uint16_t Pll::getMfrac()
{
    HwRegister<uint32_t>* pllF0Reg    = new (reinterpret_cast<void*>( 0x400FE160 )) Hal::HwRegister<uint32_t>;
    uint32_t val = pllF0Reg->getVal();

    val = val >> 10;
    val &= 0x000003FF;

    return( uint16_t(val) );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
uint32_t Pll::getPllFreq()
{
    uint8_t m = Pll::getM();
    uint8_t q = Pll::getQ();
    uint16_t mInt  = Pll::getMint();
    uint16_t mFrac = Pll::getMfrac();

    Hal::Clk::ClkSource clkSrc = Hal::Clk::getPllClkSource();
    uint32_t clkOutFreq = Hal::Clk::getRawClkFreq(clkSrc);

    clkOutFreq /= (m + 1)*(q + 1);
    clkOutFreq *= mInt + (mFrac/1024);

    return clkOutFreq;
}
//--------------------------------------------------------------

} /* namespace Hal */
