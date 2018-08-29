/*
 * Nvic.cpp
 *
 *  Created on: 31.08.2017
 *      Author: aaron
 */

#include "Nvic.h"

#include<stdint.h>
#include "../../Register/Register.h"
#include "../../Register/RegisterAllocator.h"
#include "../RegisterAddress/NvicRegisterAddress.h"

namespace Hal
{

namespace Nvic
{

void enableIr(const InterruptInstance& nr)
{
    int regNr = nr >> 5;
    int bitNr = nr % 32;
    uint32_t bit = 0x000000001 << bitNr;

    Register::RegisterInterface<uint32_t>* reg = Register::RegisterAllocator<uint32_t>::allocateRegister( nvicEnableRegisterAddress[regNr] );
    reg->setBits(bit);
}

void disableIr(const InterruptInstance& nr)
{
    int regNr = nr >> 5;
    int bitNr = nr % 32;
    uint32_t bit = 0x000000001 << bitNr;

    Register::RegisterInterface<uint32_t>* reg = Register::RegisterAllocator<uint32_t>::allocateRegister( nvicDisableRegisterAddress[regNr] );
    reg->setBits(bit);
}

} //Namespace Nvic

} /* namespace Hal */
