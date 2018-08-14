/**
 * author: 	Aaron
 * date:	14.08.18
 */

#include <string>

#include "gtest/gtest.h"
#include "Register/AddressAndNameParsing/AddressAndNameParsing.h"
#include "Register/LogFileNameAndPath.h"
#include "RegisterTestSupportables.h"

class RegisterAddressAndNameParsingTest: public ::testing::Test
{

};

TEST_F( RegisterAddressAndNameParsingTest, getAddressFromNameTest )
{
	int expectedAddress = 0x00000000;
	ASSERT_EQ( expectedAddress, AddressAndNameParsing::getAddressFromName( "TestRegister" ) );
}

TEST_F( RegisterAddressAndNameParsingTest, getNameFromAddressTest )
{
	std::string expectedName = "DefaultRegister";
	ASSERT_EQ( expectedName, AddressAndNameParsing::getNameFromAddress( 0x00000000 ) );
}
