/*
 * Rcgc.cpp
 *
 *  Created on: 17.10.2017
 *      Author: aaron
 */

#include "Rcgc.h"

#include <new>
#include <stdint.h>

#include "../../Register/HwRegister.h"

namespace Hal
{

void Rcgc::enaGpioPort(const Gpio::GpioPort& p)
{
	Register::HwRegister<uint16_t>* rcgcReg = new (reinterpret_cast<void*>(0x400FE608)) Register::HwRegister<uint16_t>;
    rcgcReg->setBits( 0x01 << p );
}

void Rcgc::enaSsiModule(const Spi::SpiInstance& inst)
{
	Register::HwRegister<uint16_t>* rcgcReg = new (reinterpret_cast<void*>(0x400FE61C)) Register::HwRegister<uint16_t>;
    rcgcReg->setBits( 0x1 << inst );
}

void Rcgc::enaTimerModule(const Hal::Timer::TimerInstance& inst)
{
	Register::HwRegister<uint16_t>* rcgcReg = new (reinterpret_cast<void*>(0x400FE604)) Register::HwRegister<uint16_t>;
    rcgcReg->setBits(0x1 << inst);
}

} /* namespace Hal */
