/**
 * Date:	31.07.18
 * Author: 	Aaron
 */

#include <stdint.h>
#include <string>

#include "gtest/gtest.h"
#include "Register/SoftwareRegister.h"
#include "Register/AddressAndNameParsing/AddressAndNameParsing.h"

class SoftwareRegisterTest: public ::testing::Test
{

};

TEST_F( SoftwareRegisterTest, namingTet )
{
	uint16_t defaultValue = 0x001A;
	std::string registerName = Register::AddressAndNameParsing::getNameFromAddress( 0x00000000 );
	Register::SoftwareRegister<uint16_t> *testedRegister = new Register::SoftwareRegister<uint16_t>( registerName, defaultValue );

	std::string fileName = "logfiles/Reg0x00000000Log.txt";
	std::ifstream file( fileName );

	EXPECT_TRUE( file.is_open() );
}

TEST_F( SoftwareRegisterTest, defaultValueTest1 )
{
	uint16_t defaultValue = 0x001A;
	Register::SoftwareRegister<uint16_t> testedRegister( "TestRegister", defaultValue );

	uint16_t expectedValue = defaultValue;
	uint16_t actualValue   = testedRegister.getVal();
	ASSERT_EQ( expectedValue, actualValue );
}


TEST_F( SoftwareRegisterTest, defaultValueTest2 )
{
	uint16_t defaultValue = 0;
	Register::SoftwareRegister<uint16_t> testedRegister( "TestRegister" );

	uint16_t expectedValue = defaultValue;
	uint16_t actualValue   = testedRegister.getVal();
	ASSERT_EQ( expectedValue, actualValue );
}


TEST_F( SoftwareRegisterTest, clearBitsTest1 )
{
	uint16_t defaultValue = 0xA321;
	Register::SoftwareRegister<uint16_t> testedRegister( "TestRegister", defaultValue );

	uint16_t clearedBits = 0x0000;
	testedRegister.clearBits( clearedBits );

	uint16_t expectedValue = ( defaultValue & (~clearedBits) );
	uint16_t actualValue   = testedRegister.getVal();
	ASSERT_EQ( expectedValue, actualValue );
}


TEST_F( SoftwareRegisterTest, clearBitsTest2 )
{
	uint16_t defaultValue = 0x242B;
	Register::SoftwareRegister<uint16_t> testedRegister( "TestRegister", defaultValue );

	uint16_t clearedBits = 0xFFFF;
	testedRegister.clearBits( clearedBits );

	uint16_t expectedValue = ( defaultValue & (~clearedBits) );
	uint16_t actualValue   = testedRegister.getVal();
	ASSERT_EQ( expectedValue, actualValue );
}


TEST_F( SoftwareRegisterTest, clearBitsTest3 )
{
	uint16_t defaultValue = 0x242B;
	Register::SoftwareRegister<uint16_t> testedRegister( "TestRegister", defaultValue );

	uint16_t clearedBits = 0xF0A0;
	testedRegister.clearBits( clearedBits );

	uint16_t expectedValue = ( defaultValue & (~clearedBits) );
	uint16_t actualValue   = testedRegister.getVal();
	ASSERT_EQ( expectedValue, actualValue );
}


TEST_F( SoftwareRegisterTest, setBitsTest1 )
{
	uint16_t defaultValue = 0x242B;
	Register::SoftwareRegister<uint16_t> testedRegister( "TestRegister", defaultValue );

	uint16_t setBits = 0x0000;
	testedRegister.setBits( setBits );

	uint16_t expectedValue = ( defaultValue | setBits );
	uint16_t actualValue   = testedRegister.getVal();
	ASSERT_EQ( expectedValue, actualValue );
}


TEST_F( SoftwareRegisterTest, setBitsTest2 )
{
	uint16_t defaultValue = 0xAC13;
	Register::SoftwareRegister<uint16_t> testedRegister( "TestRegister", defaultValue );

	uint16_t setBits = 0xFFFF;
	testedRegister.setBits( setBits );

	uint16_t expectedValue = ( defaultValue | setBits );
	uint16_t actualValue   = testedRegister.getVal();
	ASSERT_EQ( expectedValue, actualValue );
}


TEST_F( SoftwareRegisterTest, setBitsTest3 )
{
	uint16_t defaultValue = 0x56ED;
	Register::SoftwareRegister<uint16_t> testedRegister( "TestRegister", defaultValue );

	uint16_t setBits = 0xF023;
	testedRegister.setBits( setBits );

	uint16_t expectedValue = ( defaultValue | setBits );
	uint16_t actualValue   = testedRegister.getVal();
	ASSERT_EQ( expectedValue, actualValue );
}


TEST_F( SoftwareRegisterTest, insertTest1 )
{
	uint32_t defaultValue = 0x5060E0D0;
	Register::SoftwareRegister<uint32_t> testedRegister( "TestRegister", defaultValue );

	uint32_t insertedValue = 0x00000000;
	testedRegister.insert( insertedValue );

	uint32_t expectedValue = insertedValue;
	uint32_t actualValue   = testedRegister.getVal();
	ASSERT_EQ( expectedValue, actualValue );
}


TEST_F( SoftwareRegisterTest, insertTest2 )
{
	uint32_t defaultValue = 0x5060E0D0;
	Register::SoftwareRegister<uint32_t> testedRegister( "TestRegister", defaultValue );

	uint32_t insertedValue = 0xFFFFFFFF;
	testedRegister.insert( insertedValue );

	uint32_t expectedValue = insertedValue;
	uint32_t actualValue   = testedRegister.getVal();
	ASSERT_EQ( expectedValue, actualValue );
}


TEST_F( SoftwareRegisterTest, insertTest3 )
{
	uint32_t defaultValue = 0x5060E0D0;
	Register::SoftwareRegister<uint32_t> testedRegister( "TestRegister", defaultValue );

	uint32_t insertedValue = 0x23ACFF09;
	testedRegister.insert( insertedValue );

	uint32_t expectedValue = insertedValue;
	uint32_t actualValue   = testedRegister.getVal();
	ASSERT_EQ( expectedValue, actualValue );
}


TEST_F( SoftwareRegisterTest, checkBitsTest1 )
{
	uint32_t defaultValue = 0x5060E0D0;
	Register::SoftwareRegister<uint32_t> testedRegister( "TestRegister", defaultValue );

	uint32_t checkedBits = 0x00000000;

	ASSERT_TRUE( testedRegister.checkBits( checkedBits ) );
}


TEST_F( SoftwareRegisterTest, checkBitsTest2 )
{
	uint32_t defaultValue = 0x5060E0D0;
	Register::SoftwareRegister<uint32_t> testedRegister( "TestRegister", defaultValue );

	uint32_t checkedBits = ~defaultValue;

	ASSERT_FALSE( testedRegister.checkBits( checkedBits ) );
}


TEST_F( SoftwareRegisterTest, checkBitsTest3 )
{
	uint32_t defaultValue = 0x5060E0D0;
	Register::SoftwareRegister<uint32_t> testedRegister( "TestRegister", defaultValue );

	uint32_t checkedBits = defaultValue;

	ASSERT_TRUE( testedRegister.checkBits( checkedBits ) );
}


TEST_F( SoftwareRegisterTest, checkBitsTest4 )
{
	uint32_t defaultValue = 0x5060E0D0;
	Register::SoftwareRegister<uint32_t> testedRegister( "TestRegister", defaultValue );

	uint32_t checkedBits = 0x00000001;

	ASSERT_FALSE( testedRegister.checkBits( checkedBits ) );
}


TEST_F( SoftwareRegisterTest, checkBitsTest5 )
{
	uint32_t defaultValue = 0x5060E0D3;
	Register::SoftwareRegister<uint32_t> testedRegister( "TestRegister", defaultValue );

	uint32_t checkedBits = 0x00000001;

	ASSERT_TRUE( testedRegister.checkBits( checkedBits ) );
}
