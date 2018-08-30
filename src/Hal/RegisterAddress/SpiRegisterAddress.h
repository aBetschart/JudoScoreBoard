/**
 * author: Aaron
 * date: 30.08.18
 */

#ifndef SPIREGISTERADDRESS_H_
#define SPIREGISTERADDRESS_H_

#include "../Spi/Spi.h"

namespace Hal
{

static const uint32_t spiBaseAddr[Spi::nrOfSpi] = {
		0x40008000, //spi0
		0x40009000, //spi1
		0x4000A000, //spi2
		0x4000B000  //spi3
};

enum SpiRegisterOffset {
	control0RegisterOffset 				= 0x000,
	control1RegisterOffset 				= 0x004,
	dataRegisterOffset 					= 0x008,
	statusRegisterOffset				= 0x00C,
	clockPrescaleRegisterOffset 		= 0x010,
	interruptMaskRegisterOffset 		= 0x014,
	rawInterruptStatusRegisterOffset 	= 0x018,
	maskedInterruptStatusRegisterOffset	= 0x01C,
	interruptClearRegisterOffset		= 0x020,
	dmaControlRegisterOffset 			= 0x024,
	peripherialPropertiesRegisterOffset = 0xFC0,
	clockConfigurationRegisterOffset 	= 0xFC8
};

} //namespace Hal

#endif //SPIREGISTERADDRESS_H_
