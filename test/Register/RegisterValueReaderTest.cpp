#include <stdint.h>
#include <fstream>
#include <string>
#include <iostream>

#include "gtest/gtest.h"
#include "Register/RegisterValueReader.h"
#include "Register/LogFileNameAndPath.h"
#include "RegisterTestSupportables.h"

void printHeaderToFile( std::ofstream& file, const std::string& registerName );
void printValueToFile( std::ofstream& file, const int& value );

void createFileWithHeaderAndDefaultValue( std::ofstream& file, const std::string& registerName, int defaultValue = 0 )
{
	std::string logFilePathAndName = pathToLogFile + registerName + logFileEnding;
	file = std::ofstream( logFilePathAndName );

	printHeaderToFile( file, registerName );
	printValueToFile( file, defaultValue );
}

void printHeaderToFile( std::ofstream& file, const std::string& registerName )
{
	file << "-- Logfile of Register " << registerName << std::endl;
}

void printValueToFile( std::ofstream& file, const int& value )
{
	file << value << std::endl;
}

void printValuesToCreatedFile( std::ofstream& file, const int valuesToPrint[], const int& numberOfValues )
{
	for( int i = 0 ; i < numberOfValues ; ++i )
		file << valuesToPrint[i] << std::endl;
}

class RegisterValueReaderTest: public ::testing::Test
{
protected:
	std::ofstream file;
};

TEST_F( RegisterValueReaderTest, readerReadsRightValueTest1 )
{
	const uint32_t defaultValue = 0;
	const std::string registerName = getNumberedRegisterName();
	createFileWithHeaderAndDefaultValue( file, registerName );
	RegisterValueReader<uint32_t> valueReader( registerName );

	ASSERT_EQ( defaultValue, valueReader.getActualValue() );
}


TEST_F( RegisterValueReaderTest, readerReadsRightValueTest2 )
{
	const uint32_t defaultValue = 245;
	const std::string registerName = getNumberedRegisterName();
	createFileWithHeaderAndDefaultValue( file, registerName, defaultValue );
	RegisterValueReader<uint32_t> valueReader( registerName );

	ASSERT_EQ( defaultValue, valueReader.getActualValue() );
}


TEST_F( RegisterValueReaderTest, readerReadsRightValueTest3 )
{
	const std::string registerName = getNumberedRegisterName();
	createFileWithHeaderAndDefaultValue( file, registerName );
	RegisterValueReader<uint32_t> valueReader( registerName );

	const int valuesToPrint[] = { 22, 44, 746, 1235, 546 };
	const int numberOfValues = sizeof(valuesToPrint)/sizeof(valuesToPrint[0]);
	printValuesToCreatedFile( file, valuesToPrint, numberOfValues );

	const int indexOfLastValue = numberOfValues - 1;
	uint32_t expectedValue = valuesToPrint[ indexOfLastValue ];
	uint32_t actualValue = valueReader.getActualValue();
	ASSERT_EQ( expectedValue, actualValue );
}


TEST_F( RegisterValueReaderTest, readerReadsRightValueTest4 )
{
	const std::string registerName = getNumberedRegisterName();
	createFileWithHeaderAndDefaultValue( file, registerName );
	RegisterValueReader<uint16_t> valueReader( registerName );

	const int valuesToPrint[] = { 425, 6342, 12345, 6553, 1321 };
	const int numberOfValues = sizeof(valuesToPrint)/sizeof(valuesToPrint[0]);
	printValuesToCreatedFile( file, valuesToPrint, numberOfValues );

	const int indexOfLastValue = numberOfValues - 1;
	uint16_t expectedValue = valuesToPrint[ indexOfLastValue ];
	uint16_t actualValue = valueReader.getActualValue();
	ASSERT_EQ( expectedValue, actualValue );
}


TEST_F( RegisterValueReaderTest, readerReadsRightValueTest5 )
{
	const std::string registerName = getNumberedRegisterName();
	createFileWithHeaderAndDefaultValue( file, registerName );
	RegisterValueReader<uint16_t> valueReader( registerName );

	const int valuesToPrint[] = { 3423, 526, 12, 234, 6537, 864, 875, 234, 125, 6534 };
	const int numberOfValues = sizeof(valuesToPrint)/sizeof(valuesToPrint[0]);
	printValuesToCreatedFile( file, valuesToPrint, numberOfValues );

	const int indexOfLastValue = numberOfValues - 1;
	uint16_t expectedValue = valuesToPrint[ indexOfLastValue ];
	uint16_t actualValue = valueReader.getActualValue();
	ASSERT_EQ( expectedValue, actualValue );
}
