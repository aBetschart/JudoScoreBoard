/*
 * Nvic.cpp
 *
 *  Created on: 31.08.2017
 *      Author: aaron
 */

#include "Nvic.h"

#include<stdint.h>
#include<new>
#include "../HwRegister/HwRegister.h"

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

    Hal::HwRegister<uint32_t>* reg = new (reinterpret_cast<void*>(nvicEnRegAddr[regNr])) Hal::HwRegister<uint32_t>;
    reg->setBits(bit);
}

void Hal::Nvic::disableIr(const irInstance& nr)
{
    int regNr = nr >> 5;
    int bitNr = nr % 32;
    uint32_t bit = 0x000000001 << bitNr;

    Hal::HwRegister<uint32_t>* reg = new (reinterpret_cast<void*>(nvicDisRegAddr[regNr])) Hal::HwRegister<uint32_t>;
    reg->setBits(bit);
}
