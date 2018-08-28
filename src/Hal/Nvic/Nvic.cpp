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

namespace Hal
{

static const uint32_t nvicEnRegAddr[] =
{
 0xE000E100, 0xE000E104, 0xE000E108, 0xE000E10C
};

static const uint32_t nvicDisRegAddr[] =
{
 0xE000E180, 0xE000E184, 0xE000E188, 0xE000E18C
};

} /* namespace Hal */

void Hal::Nvic::enableIr(const irInstance& nr)
{
    int regNr = nr >> 5;
    int bitNr = nr % 32;
    uint32_t bit = 0x000000001 << bitNr;

    Register::RegisterInterface<uint32_t>* reg = Register::RegisterAllocator<uint32_t>::allocateRegister( nvicEnRegAddr[regNr] );
    reg->setBits(bit);
}

void Hal::Nvic::disableIr(const irInstance& nr)
{
    int regNr = nr >> 5;
    int bitNr = nr % 32;
    uint32_t bit = 0x000000001 << bitNr;

    Register::RegisterInterface<uint32_t>* reg = Register::RegisterAllocator<uint32_t>::allocateRegister( nvicDisRegAddr[regNr] );
    reg->setBits(bit);
}
