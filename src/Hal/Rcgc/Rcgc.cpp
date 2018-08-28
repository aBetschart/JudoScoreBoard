/*
 * Rcgc.cpp
 *
 *  Created on: 17.10.2017
 *      Author: aaron
 */

#include "Rcgc.h"

#include <new>
#include <stdint.h>

#include "../../Register/Register.h"
#include "../../Register/RegisterAllocator.h"

namespace Hal
{

void Rcgc::enaGpioPort(const Gpio::GpioPort& p)
{
	Register::RegisterInterface<uint16_t>* rcgcReg = Register::RegisterAllocator<uint16_t>::allocateRegister( 0x400FE608 );
    rcgcReg->setBits( 0x01 << p );
}

void Rcgc::enaSsiModule(const Spi::SpiInstance& inst)
{
	Register::RegisterInterface<uint16_t>* rcgcReg = Register::RegisterAllocator<uint16_t>::allocateRegister( 0x400FE61C );
    rcgcReg->setBits( 0x1 << inst );
}

void Rcgc::enaTimerModule(const Hal::Timer::TimerInstance& inst)
{
	Register::RegisterInterface<uint16_t>* rcgcReg = Register::RegisterAllocator<uint16_t>::allocateRegister( 0x400FE604 );
    rcgcReg->setBits(0x1 << inst);
}

} /* namespace Hal */
