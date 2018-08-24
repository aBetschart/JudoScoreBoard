/*
 * RegisterActivityLogger.h
 *
 *  Created on: 25.07.2018
 *      Author: aaron
 */

#ifndef REGISTERACTIVITYLOGGER_H_
#define REGISTERACTIVITYLOGGER_H_

#include <iostream>
#include <fstream>
#include <string>

#include "LogFileNameAndPath.h"

template<typename Type>
class RegisterActivityLogger
{
public:
	RegisterActivityLogger( const std::string& name, Type defaultValue = 0 ): registerName(name)
	{
		std::string logFilePathAndName = pathToLogFile + registerName + logFileEnding;
		logFile = std::ofstream( logFilePathAndName );
		printHeaderInLogFile();
		logRegisterModification( defaultValue );
	}

	void logRegisterModification( Type newValue )
	{
		logFile << (int)newValue << std::endl;
	}

	virtual ~RegisterActivityLogger()
	{
		logFile.close();
	}

private:
	std::string registerName;
	std::ofstream logFile;

	void printHeaderInLogFile()
	{
		logFile << "-- Logfile of Register " << registerName << std::endl;
	}
};

#endif /* REGISTERACTIVITYLOGGER_H_ */
