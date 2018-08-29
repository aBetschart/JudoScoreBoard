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
#include "../RegisterAddress/RcgcRegisterAddress.h"

namespace Hal
{

void Rcgc::enaGpioPort(const Gpio::GpioPort& p)
{
	int registerAddress = GPIO_RCGC_REGISTER_ADDRESS;
	Register::RegisterInterface<uint16_t>* rcgcReg = Register::RegisterAllocator<uint16_t>::allocateRegister( registerAddress );
    rcgcReg->setBits( 0x01 << p );
}

void Rcgc::enaSsiModule(const Spi::SpiInstance& inst)
{
	int registerAddress = SSI_RCGC_REGISTER_ADDRESS;
	Register::RegisterInterface<uint16_t>* rcgcReg = Register::RegisterAllocator<uint16_t>::allocateRegister( registerAddress );
    rcgcReg->setBits( 0x1 << inst );
}

void Rcgc::enaTimerModule(const Hal::Timer::TimerInstance& inst)
{
	int registerAddress = TIMER_RCGC_REGISTER_ADDRESS;
	Register::RegisterInterface<uint16_t>* rcgcReg = Register::RegisterAllocator<uint16_t>::allocateRegister( registerAddress );
    rcgcReg->setBits(0x1 << inst);
}

} /* namespace Hal */
