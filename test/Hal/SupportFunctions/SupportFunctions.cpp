/**
 * author: Aaron
 * date: 30.08.18
 */

#include <string>
#include "gtest/gtest.h"

#include "SupportFunctions.h"
#include "Register/RegisterValueReader.h"
#include "Register/AddressAndNameParsing/AddressAndNameParsing.h"

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
