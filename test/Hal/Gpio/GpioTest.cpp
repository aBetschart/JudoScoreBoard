/**
 * author: aaron
 * date: 28.08.18
 */

#include <stdint.h>
#include <string>
#include "gtest/gtest.h"
#include "hippomocks.h"

#include "Hal/Gpio/Gpio.h"
#include "Hal/Nvic/Nvic.h"
#include "Hal/RegisterAddress/GpioRegisterAddress.h"
#include "Hal/RegisterAddress/RcgcRegisterAddress.h"
#include "Register/SoftwareRegister.h"
#include "Register/RegisterValueReader.h"
#include "Register/AddressAndNameParsing/AddressAndNameParsing.h"
#include "EvHandler/IGpioEvHandler.h"

int getRegisterValueFromAddress( const int& registerAddress );
void checkSetBitsInValue( const int& value, const int& bits );
void checkNotSetBitsInValue( const int& value, const int& bits );
void setInterruptStatusOfGpio( const Hal::Gpio::GpioPort& portOfGpio, const Hal::Gpio::GpioPinNr& pinNrOfGpio );
void clearInterruptStatusOfGpio( const Hal::Gpio::GpioPort& portOfGpio, const Hal::Gpio::GpioPinNr& pinNrOfGpio );

class GpioTest: public ::testing::Test
{

};

class GpioEvHandlerTest: public IGpioEvHandler
{
public:
	virtual ~GpioEvHandlerTest(){}
	virtual void onGpioEv( const Hal::Gpio& gpio ){}
};


TEST_F(GpioTest, rcgcPortsEnabledTest) {
	int firstPortTested = (int)Hal::Gpio::portA;
	int lastPortTested  = (int)Hal::Gpio::portQ;

	for( int portIndex = firstPortTested ; portIndex <= lastPortTested ; ++portIndex ){
		Hal::Gpio::GpioInit init =
		{
				.dir 		= Hal::Gpio::dirOutput,
				.port 		= (Hal::Gpio::GpioPort)portIndex,
				.nr 		= Hal::Gpio::pin1,
				.outCfg 	= Hal::Gpio::pullUpRes,
				.openDrain 	= false
		};

		Hal::Gpio testedGpio( init );

		int registerAddress = Hal::GPIO_RCGC_REGISTER_ADDRESS;
		int bitsToBeSet = 0x01 << init.port;
		int actualValue = getRegisterValueFromAddress( registerAddress );

		checkSetBitsInValue( actualValue, bitsToBeSet );
	}
}


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


TEST_F(GpioTest, alternateFunctionsCtrlRegisterValueTest) {
	Hal::Gpio::GpioPort port = Hal::Gpio::portA;
	Hal::Gpio::GpioPinNr pin = Hal::Gpio::pin2;
	Hal::Gpio::GpioFunc firstFunctionTested = Hal::Gpio::analogFunc;
	Hal::Gpio::GpioFunc lastFunctionTested = Hal::Gpio::dig15;

	for( int f = (int)firstFunctionTested ; f <= (int)lastFunctionTested ; ++f ) {
		Hal::Gpio testedGpio( port, pin, (Hal::Gpio::GpioFunc)f );
		int expectedValue = f;
		int registerAddress = Hal::gpioBaseAddr[port] + Hal::portCtrlRegisterOffset;
		int registerValue = getRegisterValueFromAddress( registerAddress );
		int actualValue = registerValue >> 4*pin;
		actualValue &= 0x000F;

		EXPECT_EQ( expectedValue, actualValue );
	}
}


TEST_F(GpioTest, analogFunctionEnabledDigitalDisabledTest) {
	Hal::Gpio::GpioPort port = Hal::Gpio::portA;
	Hal::Gpio::GpioPinNr pin = Hal::Gpio::pin2;
	Hal::Gpio::GpioFunc function = Hal::Gpio::analogFunc;
	Hal::Gpio testedGpio( port, pin, function );

	int registerAddress = Hal::gpioBaseAddr[port] + Hal::analogModeSelRegisterOffset;
	int bitsToBeSet = 0x01 << pin;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), bitsToBeSet );

	registerAddress = Hal::gpioBaseAddr[port] + Hal::digitalEnableRegisterOffset;
	int bitsNotToBeSet = 0x01 << pin;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), bitsNotToBeSet );
}


TEST_F(GpioTest, analogFunctionDisabledDigitalEnabledTest1) {
	Hal::Gpio::GpioPort port = Hal::Gpio::portA;
	Hal::Gpio::GpioPinNr pin = Hal::Gpio::pin2;
	Hal::Gpio::GpioFunc function = Hal::Gpio::noSpecFunc;
	Hal::Gpio testedGpio( port, pin, function );

	int registerAddress = Hal::gpioBaseAddr[port] + Hal::analogModeSelRegisterOffset;
	int bitsNotToBeSet = 0x01 << pin;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), bitsNotToBeSet );

	registerAddress = Hal::gpioBaseAddr[port] + Hal::digitalEnableRegisterOffset;
	int bitsToBeSet = 0x01 << pin;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), bitsToBeSet );
}


TEST_F(GpioTest, analogFunctionDisabledDigitalEnabledTest2) {
	Hal::Gpio::GpioPort port = Hal::Gpio::portA;
	Hal::Gpio::GpioPinNr pin = Hal::Gpio::pin2;
	Hal::Gpio::GpioFunc function = Hal::Gpio::dig6;
	Hal::Gpio testedGpio( port, pin, function );

	int registerAddress = Hal::gpioBaseAddr[port] + Hal::analogModeSelRegisterOffset;
	int bitsNotToBeSet = 0x01 << pin;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), bitsNotToBeSet );

	registerAddress = Hal::gpioBaseAddr[port] + Hal::digitalEnableRegisterOffset;
	int bitsToBeSet = 0x01 << pin;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), bitsToBeSet );
}


TEST_F(GpioTest, driveStrength2maTest) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirOutput,
			.port = Hal::Gpio::portJ,
			.nr = Hal::Gpio::pin6,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );
	testedGpio.setDriveStrength( Hal::Gpio::GpioDrStr::ma2 );

	int checkedBits = 0x01 << init.nr;

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::ma2DriveSelRegisterOffset;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, driveStrength4maTest) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirOutput,
			.port = Hal::Gpio::portJ,
			.nr = Hal::Gpio::pin6,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );
	testedGpio.setDriveStrength( Hal::Gpio::GpioDrStr::ma4 );

	int checkedBits = 0x01 << init.nr;

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::ma4DriveSelRegisterOffset;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, driveStrength8maTest) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirOutput,
			.port = Hal::Gpio::portJ,
			.nr = Hal::Gpio::pin6,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );
	testedGpio.setDriveStrength( Hal::Gpio::GpioDrStr::ma8 );

	int checkedBits = 0x01 << init.nr;

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::ma8DriveSelRegisterOffset;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, interruptEnabledTest) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portC,
			.nr = Hal::Gpio::pin2,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );
	testedGpio.setInterrupt( true );

	int checkedBits = 0x01 << init.nr;

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::interruptMaskRegisterOffset;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, interruptDisabledTest) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portB,
			.nr = Hal::Gpio::pin5,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );
	testedGpio.setInterrupt( true );
	testedGpio.setInterrupt( false );

	int checkedBits = 0x01 << init.nr;

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::interruptMaskRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, nvicInterruptEnabledPortBTest) {

	MockRepository mocks;

	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portB,
			.nr = Hal::Gpio::pin5,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );
	mocks.ExpectCallFunc( Hal::Nvic::enableIr ).With( Hal::Nvic::gpioPortB );
	testedGpio.setInterrupt( true );
}


TEST_F(GpioTest, nvicInterruptEnabledPortJTest) {

	MockRepository mocks;

	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portJ,
			.nr = Hal::Gpio::pin5,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );
	mocks.ExpectCallFunc( Hal::Nvic::enableIr ).With( Hal::Nvic::gpioPortJ );
	testedGpio.setInterrupt( true );
}



TEST_F(GpioTest, interruptRisingEdgeEnabledTest) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portB,
			.nr = Hal::Gpio::pin5,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );
	testedGpio.setInterrupt( true );
	testedGpio.configIr( Hal::Gpio::GpioIrEv::evRisingEdge );

	int checkedBits = 0x01 << init.nr;

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::interruptSenseRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
	registerAddress = Hal::gpioBaseAddr[init.port] + Hal::interruptBothEdgesRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
	registerAddress = Hal::gpioBaseAddr[init.port] + Hal::interruptEventRegisterOffset;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, interruptFallingEdgeEnabledTest) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portB,
			.nr = Hal::Gpio::pin5,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );
	testedGpio.setInterrupt( true );
	testedGpio.configIr( Hal::Gpio::GpioIrEv::evFallingEdge );

	int checkedBits = 0x01 << init.nr;

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::interruptSenseRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
	registerAddress = Hal::gpioBaseAddr[init.port] + Hal::interruptBothEdgesRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
	registerAddress = Hal::gpioBaseAddr[init.port] + Hal::interruptEventRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, interruptBothEdgesEnabledTest) {
	Hal::Gpio::GpioInit init =
	{
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portB,
			.nr = Hal::Gpio::pin5,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};

	Hal::Gpio testedGpio( init );
	testedGpio.setInterrupt( true );
	testedGpio.configIr( Hal::Gpio::GpioIrEv::evBothEdge );

	int checkedBits = 0x01 << init.nr;

	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::interruptSenseRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
	registerAddress = Hal::gpioBaseAddr[init.port] + Hal::interruptBothEdgesRegisterOffset;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, isEqualOperatorTest) {
	Hal::Gpio testedGpio1( Hal::Gpio::portB, Hal::Gpio::pin5, Hal::Gpio::noSpecFunc );
	Hal::Gpio testedGpio2( Hal::Gpio::portC, Hal::Gpio::pin5, Hal::Gpio::noSpecFunc );
	Hal::Gpio testedGpio3( Hal::Gpio::portB, Hal::Gpio::pin4, Hal::Gpio::noSpecFunc );
	Hal::Gpio* pointerOnTestedGpio1 = &testedGpio1;

	ASSERT_TRUE( testedGpio1 == *pointerOnTestedGpio1 );
	ASSERT_FALSE( testedGpio1 == testedGpio2 );
	ASSERT_FALSE( testedGpio1 == testedGpio3 );
	ASSERT_FALSE( testedGpio2 == testedGpio3 );
	ASSERT_FALSE( testedGpio2 == *pointerOnTestedGpio1 );
	ASSERT_FALSE( testedGpio3 == *pointerOnTestedGpio1 );
}


TEST_F(GpioTest, setGpioTest) {
	Hal::Gpio::GpioInit init = {
			.dir = Hal::Gpio::dirOutput,
			.port = Hal::Gpio::portB,
			.nr = Hal::Gpio::pin5,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};
	Hal::Gpio testedGpio( init );

	testedGpio.set( true );
	int checkedBits = 0x01 << init.nr;
	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::dataRegisterOffset;
	checkSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, unsetGpioTest) {
	Hal::Gpio::GpioInit init = {
			.dir = Hal::Gpio::dirOutput,
			.port = Hal::Gpio::portB,
			.nr = Hal::Gpio::pin5,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};
	Hal::Gpio testedGpio( init );

	testedGpio.set( true );
	testedGpio.set( false );
	int checkedBits = 0x01 << init.nr;
	int registerAddress = Hal::gpioBaseAddr[init.port] + Hal::dataRegisterOffset;
	checkNotSetBitsInValue( getRegisterValueFromAddress( registerAddress ), checkedBits );
}


TEST_F(GpioTest, isGpioSetTrueTest) {
	Hal::Gpio::GpioInit init = {
			.dir = Hal::Gpio::dirOutput,
			.port = Hal::Gpio::portA,
			.nr = Hal::Gpio::pin1,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};
	std::string registerName = Register::AddressAndNameParsing::getNameFromAddress(Hal::gpioBaseAddr[init.port] + Hal::dataRegisterOffset);
	Register::SoftwareRegister<uint8_t> dataRegisterOfGpio( registerName );
	Hal::Gpio testedGpio( init );

	int checkedBits = 0x01 << init.nr;

	dataRegisterOfGpio.setBits( checkedBits );

	EXPECT_TRUE( testedGpio.isSet() );
}


TEST_F(GpioTest, isGpioSetFalseTest) {
	Hal::Gpio::GpioInit init = {
			.dir = Hal::Gpio::dirOutput,
			.port = Hal::Gpio::portC,
			.nr = Hal::Gpio::pin4,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};
	std::string registerName = Register::AddressAndNameParsing::getNameFromAddress(Hal::gpioBaseAddr[init.port] + Hal::dataRegisterOffset);
	Register::SoftwareRegister<uint8_t> dataRegisterOfGpio( registerName );
	Hal::Gpio testedGpio( init );

	int checkedBits = 0x01 << init.nr;

	dataRegisterOfGpio.clearBits( checkedBits );

	EXPECT_FALSE( testedGpio.isSet() );
}

TEST_F(GpioTest, evHandlerRegisteredAndCalled1) {
	MockRepository mocks;
	GpioEvHandlerTest* evHandlerMock = mocks.Mock<GpioEvHandlerTest>();

	Hal::Gpio::GpioInit init = {
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portC,
			.nr = Hal::Gpio::pin4,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};
	Hal::Gpio testedGpio( init );
	testedGpio.setInterrupt( true );
	setInterruptStatusOfGpio( init.port, init.nr );

	testedGpio.registerOnEv( evHandlerMock );
	mocks.ExpectCall( evHandlerMock, GpioEvHandlerTest::onGpioEv );
	Hal::Gpio::gpioCallBackPortC();
}


TEST_F(GpioTest, evHandlerRegisteredAndCalled2) {
	MockRepository mocks;
	GpioEvHandlerTest* evHandlerMock = mocks.Mock<GpioEvHandlerTest>();

	Hal::Gpio::GpioInit init = {
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portJ,
			.nr = Hal::Gpio::pin7,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};
	Hal::Gpio testedGpio( init );
	testedGpio.setInterrupt( true );
	setInterruptStatusOfGpio( init.port, init.nr );

	testedGpio.registerOnEv( evHandlerMock );
	mocks.ExpectCall( evHandlerMock, GpioEvHandlerTest::onGpioEv );
	Hal::Gpio::gpioCallBackPortJ();
}


TEST_F(GpioTest, noInterruptIfOtherPortIsChecked) {
	MockRepository mocks;
	GpioEvHandlerTest* evHandlerMock = mocks.Mock<GpioEvHandlerTest>();

	Hal::Gpio::GpioInit init = {
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portE,
			.nr = Hal::Gpio::pin6,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};
	Hal::Gpio testedGpio( init );
	testedGpio.setInterrupt( true );
	setInterruptStatusOfGpio( init.port, init.nr );

	testedGpio.registerOnEv( evHandlerMock );
	mocks.NeverCall( evHandlerMock, GpioEvHandlerTest::onGpioEv );
	Hal::Gpio::gpioCallBackPortJ();
}


TEST_F(GpioTest, noInterruptIfFlagIsClearedTest) {
	MockRepository mocks;
	GpioEvHandlerTest* evHandlerMock = mocks.Mock<GpioEvHandlerTest>();

	Hal::Gpio::GpioInit init = {
			.dir = Hal::Gpio::dirInput,
			.port = Hal::Gpio::portE,
			.nr = Hal::Gpio::pin6,
			.outCfg = Hal::Gpio::noResistor,
			.openDrain = false
	};
	Hal::Gpio testedGpio( init );
	testedGpio.setInterrupt( true );
	clearInterruptStatusOfGpio( init.port, init.nr );

	testedGpio.registerOnEv( evHandlerMock );
	mocks.NeverCall( evHandlerMock, GpioEvHandlerTest::onGpioEv );
	Hal::Gpio::gpioCallBackPortE();
}


void setInterruptStatusOfGpio( const Hal::Gpio::GpioPort& portOfGpio, const Hal::Gpio::GpioPinNr& pinNrOfGpio ) {
	std::string registerName = Register::AddressAndNameParsing::getNameFromAddress(Hal::gpioBaseAddr[portOfGpio] + Hal::maskedInterruptStatusRegisterOffset);
	Register::SoftwareRegister<uint8_t> interruptRegisterOfGpio( registerName );
	interruptRegisterOfGpio.setBits( 0x01 << pinNrOfGpio );
}


void clearInterruptStatusOfGpio( const Hal::Gpio::GpioPort& portOfGpio, const Hal::Gpio::GpioPinNr& pinNrOfGpio ) {
	std::string registerName = Register::AddressAndNameParsing::getNameFromAddress(Hal::gpioBaseAddr[portOfGpio] + Hal::maskedInterruptStatusRegisterOffset);
	Register::SoftwareRegister<uint8_t> interruptRegisterOfGpio( registerName );
	interruptRegisterOfGpio.clearBits( 0x01 << pinNrOfGpio );
}


int getRegisterValueFromAddress( const int& registerAddress ) {
	std::string registerName =	Register::AddressAndNameParsing::getNameFromAddress(registerAddress);
	RegisterValueReader<uint32_t> reader(registerName);

	return reader.getActualValue();
}


void checkSetBitsInValue( const int& value, const int& bits ) {
	ASSERT_TRUE( (value & bits) == bits );
}


void checkNotSetBitsInValue( const int& value, const int& bits ) {
	ASSERT_TRUE( (~value & bits) == bits );
}
