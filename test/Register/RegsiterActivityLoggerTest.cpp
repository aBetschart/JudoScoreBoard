#include <stdint.h>
#include <fstream>
#include <string>

#include "gtest/gtest.h"
#include "Register/RegisterActivityLogger.h"
#include "Register/LogFileNameAndPath.h"
#include "RegisterTestSupportables.h"

int getLastLineWrittenToFile( std::ifstream& logFile )
{
	std::string result = "0";
	if(logFile.is_open())
	{
		logFile.seekg(0,std::ios_base::end);      //Start at end of file
		char ch = ' ';                        //Init ch not equal to '\n'
		while(ch != '\n'){
			logFile.seekg(-2,std::ios_base::cur); //Two steps back, this means we
			//will NOT check the last character
			if((int)logFile.tellg() <= 0){        //If passed the start of the file,
				logFile.seekg(0);                 //this is the start of the line
				break;
			}
			logFile.get(ch);  //Check the next character
		}
		std::getline(logFile,result);
	}
	return std::stoi( result, nullptr, 10 );
}

class RegisterActivityLoggerTest: public ::testing::Test
{

};

TEST_F( RegisterActivityLoggerTest, fileCreatedTest1 )
{
	std::string registerName = getNumberedRegisterName();
	RegisterActivityLogger<uint32_t> activityLogger( registerName );

	std::ifstream checkedLogFile( pathToLogFile + registerName + logFileEnding );
	ASSERT_TRUE( checkedLogFile.is_open() );
}


TEST_F( RegisterActivityLoggerTest, fileCreatedTest2 )
{
	std::string registerName = getNumberedRegisterName();
	RegisterActivityLogger<uint32_t> activityLogger( registerName );

	std::ifstream checkedLogFile( pathToLogFile + registerName + logFileEnding );
	ASSERT_TRUE( checkedLogFile.is_open() );
}


TEST_F( RegisterActivityLoggerTest, rightValueInFileTest1 )
{
	std::string registerName = getNumberedRegisterName();
	RegisterActivityLogger<uint32_t> activityLogger( registerName );

	std::ifstream checkedLogFile( pathToLogFile + registerName + logFileEnding );

	int defaultValue = 0;
	ASSERT_EQ( defaultValue, getLastLineWrittenToFile( checkedLogFile ) );
}


TEST_F( RegisterActivityLoggerTest, rightValueInFileTest2 )
{
	int defaultValue = 32;
	std::string registerName = getNumberedRegisterName();
	RegisterActivityLogger<uint32_t> activityLogger( registerName, defaultValue );

	std::ifstream checkedLogFile( pathToLogFile + registerName + logFileEnding );

	ASSERT_EQ( defaultValue, getLastLineWrittenToFile( checkedLogFile ) );
}


TEST_F( RegisterActivityLoggerTest, rightValueInFileTest3 )
{
	std::string registerName = getNumberedRegisterName();
	RegisterActivityLogger<uint32_t> activityLogger( registerName );

	int newValue = 0xA;
	activityLogger.logRegisterModification( newValue );
	std::ifstream checkedLogFile( pathToLogFile + registerName + logFileEnding );

	ASSERT_EQ( newValue, getLastLineWrittenToFile( checkedLogFile ) );
}


TEST_F( RegisterActivityLoggerTest, rightValueInFileTest4 )
{
	std::string registerName = getNumberedRegisterName();
	RegisterActivityLogger<uint16_t> activityLogger( registerName );

	int newValue = -425;
	activityLogger.logRegisterModification( newValue );
	std::ifstream checkedLogFile( pathToLogFile + registerName + logFileEnding );

	ASSERT_NE( newValue, getLastLineWrittenToFile( checkedLogFile ) );
}


TEST_F( RegisterActivityLoggerTest, rightValueInFileTest5 )
{
	std::string registerName = getNumberedRegisterName();
	RegisterActivityLogger<uint32_t> activityLogger( registerName );

	int newValue = 0x3245;
	activityLogger.logRegisterModification( newValue );
	std::ifstream checkedLogFile( pathToLogFile + registerName + logFileEnding );

	ASSERT_EQ( newValue, getLastLineWrittenToFile( checkedLogFile ) );
}


TEST_F( RegisterActivityLoggerTest, overwriteTest )
{
	std::string registerName = "OverwriteTest";
	RegisterActivityLogger<uint32_t>* firstActivityLogger;
	RegisterActivityLogger<uint32_t>* secondActivityLogger;

	uint32_t value = 0x324;

	firstActivityLogger = new RegisterActivityLogger<uint32_t>( registerName );
	firstActivityLogger->logRegisterModification( value );
	secondActivityLogger = new RegisterActivityLogger<uint32_t>( registerName );

	std::ifstream checkedLogFile( pathToLogFile + registerName + logFileEnding );
	ASSERT_EQ( (int)value, getLastLineWrittenToFile( checkedLogFile ) );
}
