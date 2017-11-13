/*
 * Rcgc.cpp
 *
 *  Created on: 17.10.2017
 *      Author: aaron
 */

#include "Rcgc.h"

#include <new>
#include <stdint.h>

#include "../HwRegister/HwRegister.h"

namespace Hal
{

} /* namespace Hal */

void Hal::Rcgc::enaGpioPort(const Gpio::GpioPort& p)
{
    HwRegister<uint16_t>* rcgcReg = new (reinterpret_cast<void*>(0x400FE608)) Hal::HwRegister<uint16_t>;
    rcgcReg->setBits( 0x01 << p );
}

void Hal::Rcgc::enaSsiModule(const Spi::SpiInstance& inst)
{
    HwRegister<uint16_t>* rcgcReg = new (reinterpret_cast<void*>(0x400FE61C)) Hal::HwRegister<uint16_t>;
    rcgcReg->setBits( 0x1 << inst );
}

void Hal::Rcgc::enaTimerModule(const Hal::Timer::TimerInstance& inst)
{
    HwRegister<uint16_t>* rcgcReg = new (reinterpret_cast<void*>(0x400FE604)) Hal::HwRegister<uint16_t>;
    rcgcReg->setBits(0x1 << inst);
}
