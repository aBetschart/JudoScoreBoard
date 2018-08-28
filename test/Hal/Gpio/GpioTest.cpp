/**
 * author: aaron
 * date: 28.08.18
 */

#include <stdint.h>
#include <string>
#include "gtest/gtest.h"

#include "Hal/Gpio/Gpio.h"
#include "Hal/RegisterAddress/GpioRegisterAddress.h"
#include "Register/RegisterValueReader.h"
#include "Register/AddressAndNameParsing/AddressAndNameParsing.h"

int getRegisterValueFromAddress( const int& registerAddress );
void checkSetBitsInValue( const int& value, const int& bits );
void checkNotSetBitsInValue( const int& value, const int& bits );

class GpioTest: public ::testing::Test
{

};


TEST_F(GpioTest, directionInitializationTest1) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirOutput,
			.port = Hal::Gpio::portA,
			.nr = Hal::Gpio::pin1,
			.outCfg = Hal::Gpio::pullUpRes,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::directionRegisterOffset;
	int bitsToBeSet = 0x01 << init.nr;
	int actualValue = getRegisterValueFromAddress( registerAddress );

	checkSetBitsInValue( actualValue, bitsToBeSet );
}


TEST_F(GpioTest, directionInitializationTest2) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portB,
			.nr = Hal::Gpio::pin2,
			.outCfg = Hal::Gpio::pullUpRes,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::directionRegisterOffset;
	int bitsNotToBeSet = 0x01 << init.nr;
	int actualValue = getRegisterValueFromAddress( registerAddress );

	checkNotSetBitsInValue( actualValue, bitsNotToBeSet );
}


TEST_F(GpioTest, resistorInitializationNoResistorTest) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portB,
			.nr = Hal::Gpio::pin2,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );

	int bitsNotToBeSet = 0x01 << init.nr;

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::pullUpSelRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), bitsNotToBeSet );
	registerAddress = Hal::gpioBaseAddr[init.port] + Hal::pullDownSelRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), bitsNotToBeSet );
}


TEST_F(GpioTest, resistorInitializationPullDownTest) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portC,
			.nr = Hal::Gpio::pin7,
			.outCfg = Hal::Gpio::pullDownRes,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );

	int checkedBits = 0x01 << init.nr;

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::pullUpSelRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
	registerAddress = Hal::gpioBaseAddr[init.port] + Hal::pullDownSelRegisterOffset;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, resistorInitializationPullUpTest) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirOutput,
			.port = Hal::Gpio::portD,
			.nr = Hal::Gpio::pin7,
			.outCfg = Hal::Gpio::pullUpRes,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );

	int checkedBits = 0x01 << init.nr;

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::pullUpSelRegisterOffset;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
	registerAddress = Hal::gpioBaseAddr[init.port] + Hal::pullDownSelRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, openDrainTrueTest) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirOutput,
			.port = Hal::Gpio::portD,
			.nr = Hal::Gpio::pin7,
			.outCfg = Hal::Gpio::pullUpRes,
			.openDrain = true
	};

	Hal::Gpio testedGpio( init );

	int checkedBits = 0x01 << init.nr;

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::openDrainSelRegisterOffset;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, openDrainFalseTest) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portE,
			.nr = Hal::Gpio::pin6,
			.outCfg = Hal::Gpio::pullUpRes,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );

	int checkedBits = 0x01 << init.nr;

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::openDrainSelRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, alternateFunctionDisabledTest) {
	Hal::Gpio::GpioPort port = Hal::Gpio::portH;
	Hal::Gpio::GpioPinNr pin = Hal::Gpio::pin1;
	Hal::Gpio testedGpio( port, pin, Hal::Gpio::noSpecFunc );

	int checkedBits = 0x01 << pin;

	int registerAddress = Hal::gpioBaseAddr[port] + Hal::alternateFunctionSelRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, alternateFunctionEnabledTest) {
	Hal::Gpio::GpioPort port = Hal::Gpio::portJ;
	Hal::Gpio::GpioPinNr pin = Hal::Gpio::pin2;
	Hal::Gpio testedGpio( port, pin, Hal::Gpio::dig1 );

	int checkedBits = 0x01 << pin;

	int registerAddress = Hal::gpioBaseAddr[port] + Hal::alternateFunctionSelRegisterOffset;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, digitalFunction3EnabledTest) {
	Hal::Gpio::GpioPort port = Hal::Gpio::portA;
	Hal::Gpio::GpioPinNr pin = Hal::Gpio::pin2;
	Hal::Gpio::GpioFunc function = Hal::Gpio::dig3;
	Hal::Gpio testedGpio( port, pin, function );

	int expectedValue = (int)function;
	int registerAddress = Hal::gpioBaseAddr[port] + Hal::portCtrlRegisterOffset;
	int registerValue = getRegisterValueFromAddress( registerAddress );
	int actualValue = registerValue;

	EXPECT_EQ( expectedValue, actualValue );
}


int getRegisterValueFromAddress( const int& registerAddress ) {
	std::string registerName =	Register::AddressAndNameParsing::getNameFromAddress(registerAddress);
	RegisterValueReader<uint8_t> reader(registerName);

	return reader.getActualValue();
}


void checkSetBitsInValue( const int& value, const int& bits ) {
	ASSERT_TRUE( (value & bits) == bits );
}


void checkNotSetBitsInValue( const int& value, const int& bits ) {
	ASSERT_TRUE( (~value & bits) == bits );
}
