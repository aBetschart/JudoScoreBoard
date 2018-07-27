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

const static std::string pathToLogFile = std::string("logfiles/");
const static std::string logFileEnding = std::string("Log.txt");

template<typename Type>
class RegisterActivityLogger
{
public:

	static void logRegisterModification( const std::string& registerName, Type newValue )
	{
		std::string logFilePathAndName = pathToLogFile + registerName + logFileEnding;
		std::ofstream logFile = std::ofstream( logFilePathAndName );
		logFile << newValue;
	}

private:
	RegisterActivityLogger();
	virtual ~RegisterActivityLogger();
};

#endif /* REGISTERACTIVITYLOGGER_H_ */
