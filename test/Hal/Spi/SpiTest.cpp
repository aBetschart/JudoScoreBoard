/**
 * name: aaron
 * date: 30.08.18
 */

#include "gtest/gtest.h"

#include "../SupportFunctions/SupportFunctions.h"
#include "Hal/Spi/Spi.h"
#include "Hal/Gpio/Gpio.h"
#include "Hal/RegisterAddress/SpiRegisterAddress.h"
#include "Hal/RegisterAddress/GpioRegisterAddress.h"

struct SpiPinAssignment
{
	Hal::Gpio::GpioPort 	port;
	Hal::Gpio::GpioPinNr	pinNumber;
	Hal::Gpio::GpioFunc		function;
};

static const SpiPinAssignment clockPin[Hal::Spi::nrOfSpi] = {
		{ Hal::Gpio::portA, Hal::Gpio::pin2, Hal::Gpio::dig15 },
		{ Hal::Gpio::portA, Hal::Gpio::pin3, Hal::Gpio::dig15 },
		{ Hal::Gpio::portA, Hal::Gpio::pin2, Hal::Gpio::dig15 },
		{ Hal::Gpio::portA, Hal::Gpio::pin2, Hal::Gpio::dig15 }
};

class SpiTest: public ::testing::Test
{

};

TEST_F( SpiTest, clockPinInitializedTest ) {
	Hal::Spi::SpiInstance firstInstanceTested = Hal::Spi::spi0;

	for( int spi = firstInstanceTested ; spi < (int)Hal::Spi::nrOfSpi ; ++spi )
	{
		Hal::Spi::SpiInit init = {
				.inst 		= (Hal::Spi::SpiInstance)spi,
				.type 		= Hal::Spi::master,
				.direction 	= Hal::Spi::transmit,
				.cpsvdr 	= 2, // clock prescaler 1
				.scr 		= 3,// clock prescaler 2
				.enaFss 	= false, // low during transmission
				.spo 		= false, // clock polarity
				.sph 		= false, // clock phase
				.dataSize 	= 16, // dataSize = [4, 5, ..., 16]
				.enaIr 		= false // enable interrupt or not
		};
		Hal::Spi testedSpi( init );
		int clockPinNumber = (int)clockPin[init.inst].pinNumber;
		Hal::Gpio::GpioPort portOfClockPin = clockPin[init.inst].port;

		int registerAddress = Hal::gpioBaseAddr[portOfClockPin] + Hal::portCtrlRegisterOffset;
		int portCtrlRegisterValue = getRegisterValueFromAddress( registerAddress );

		int specialFunctionValue = (portCtrlRegisterValue >> 4*clockPinNumber) & 0xFF;

		ASSERT_EQ( specialFunctionValue, (int)clockPin[init.inst].function );
	}
}
