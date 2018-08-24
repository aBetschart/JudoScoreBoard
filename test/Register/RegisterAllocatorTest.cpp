/**
 * author: Aaron
 * date: 14.08.18
 */

#include "gtest/gtest.h"
#include <stdint.h>
#include <fstream>

#include "Register/RegisterAllocator.h"
#include "Register/Register.h"
#include "Register/AddressAndNameParsing/AddressAndNameParsing.h"
#include "Register/LogFileNameAndPath.h"

class RegisterAllocatorTest: public ::testing::Test
{

};

TEST_F( RegisterAllocatorTest, allocationTest1 )
{
	Register::RegisterInterface<uint8_t> *testRegister;
	int address = 0x00000FFF;
	testRegister = Register::RegisterAllocator<uint8_t>::allocateRegister( address );

	std::stringstream logfileName;
	logfileName << pathToLogFile
				<< Register::AddressAndNameParsing::getNameFromAddress( address )
				<< logFileEnding;

	std::ifstream logFile( logfileName.str() );

	EXPECT_TRUE( logFile.is_open() );
}


TEST_F( RegisterAllocatorTest, allocationTest2 )
{
	Register::RegisterInterface<uint16_t> *testRegister;
	int address = 0x000001EA;
	testRegister = Register::RegisterAllocator<uint16_t>::allocateRegister( address );

	std::stringstream logfileName;
	logfileName << pathToLogFile
				<< Register::AddressAndNameParsing::getNameFromAddress( address )
				<< logFileEnding;

	std::ifstream logFile( logfileName.str() );

	EXPECT_TRUE( logFile.is_open() );
}
