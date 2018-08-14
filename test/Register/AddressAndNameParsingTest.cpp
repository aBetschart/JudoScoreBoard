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

TEST_F( RegisterAddressAndNameParsingTest, getNameFromAddressTest )
{
	ASSERT_EQ( "0x00000000", Register::AddressAndNameParsing::getNameFromAddress( 0x00000000 ) );
	ASSERT_EQ( "0x00000001", Register::AddressAndNameParsing::getNameFromAddress( 0x00000001 ) );
	ASSERT_EQ( "0x00000002", Register::AddressAndNameParsing::getNameFromAddress( 0x00000002 ) );
	ASSERT_EQ( "0x000010f9", Register::AddressAndNameParsing::getNameFromAddress( 0x000010F9 ) );
	ASSERT_EQ( "0x00000156", Register::AddressAndNameParsing::getNameFromAddress( 0x00000156 ) );
	ASSERT_EQ( "0x0004eb32", Register::AddressAndNameParsing::getNameFromAddress( 0x0004EB32 ) );
	ASSERT_EQ( "0x0001e0fe", Register::AddressAndNameParsing::getNameFromAddress( 0x0001E0FE ) );
	ASSERT_EQ( "0x00000080", Register::AddressAndNameParsing::getNameFromAddress( -128 ) );
	ASSERT_EQ( "0x00000001", Register::AddressAndNameParsing::getNameFromAddress( -1 ) );
	ASSERT_EQ( "0x016f13d3", Register::AddressAndNameParsing::getNameFromAddress( -24056787 ) );
	ASSERT_EQ( "0x0006822a", Register::AddressAndNameParsing::getNameFromAddress( -426538 ) );
}
