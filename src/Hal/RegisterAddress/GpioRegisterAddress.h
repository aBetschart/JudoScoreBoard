/**
 *
 * Date: 31.07.18
 * Name: Aaron
 */

#ifndef GPIOREGISTERADDRESS_H_
#define GPIOREGISTERADDRESS_H_

#include<stdint.h>

#include "../Gpio/Gpio.h"

namespace Hal
{

const uint32_t gpioBaseAddr[Hal::Gpio::nrOfGpioPorts] =
{
    0x40058000, 0x40059000, 0x4005A000, 0x4005B000, 0x4005C000,
    0x4005D000, 0x4005E000, 0x4005F000, 0x40060000, 0x40061000,
    0x40062000, 0x40063000, 0x40064000, 0x40065000, 0x40066000
};

enum GpioRegisterOffset
{
	dataRegisterOffset 					= 0x0000,
	directionRegisterOffset 			= 0x0400,
	interruptSenseRegisterOffset 		= 0x0404,
	interuptBothEdgesRegisterOffset 	= 0x0408,
	interruptEventRegisterOffset 		= 0x040C,
	interruptMaskRegisterOffset 		= 0x0410,
	rawInterruptStatusRegisterOffset 	= 0x0414,
	maskedInterruptStatusRegisterOffset	= 0x0418,
	interruptClearRegisterOffset 		= 0x041C,
	alternateFunctionSelRegisterOffset 	= 0x0420,
	ma2DriveSelRegisterOffset 			= 0x0500,
	ma4DriveSelegisterOffset 			= 0x0504,
	ma8DriveSelRegisterOffset 			= 0x0508,
	openDrainSelRegisterOffset 			= 0x050C,
	pullUpSelRegisterOffset 			= 0x0510,
	pullDownSelRegisterOffset 			= 0x0514,
	slewRateCtrlSelRegisterOffset 		= 0x0518,
	digitalEnableRegisterOffset 		= 0x051C,
	lockRegisterOffset 					= 0x0520,
	commitRegisterOffset 				= 0x0524,
	analogModeSelRegisterOffset 		= 0x0528,
	portCtrlRegisterOffset 				= 0x052C,
	adcCtrlRegisterOffset 				= 0x0530,
	dmaCtrlRegisterOffset 				= 0x0534,
	selInterruptRegisterOffset	 		= 0x0538,
	ma12DriveSelRegisterOffset			= 0x053C,
	wakePinEnableRegisterOffset 		= 0x0540,
	wakeLevelRegisterOffset 			= 0x0544,
	wakeStatusRegisterOffset	 		= 0x0548,
	peripherialPropertyRegisterOffset 	= 0x05C0,
	peripherialConfigRegisterOffset 	= 0x05C4
};

} // Hal

#endif //GPIOREGISTERADDRESS_H_
