/*
 * RegisterValueReader.h
 *
 *  Created on: 26.07.2018
 *      Author: aaron
 */

#ifndef REGISTER_REGISTERVALUEREADER_H_
#define REGISTER_REGISTERVALUEREADER_H_

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include "LogFileNameAndPath.h"

template<typename Type>
class RegisterValueReader
{
public:
	RegisterValueReader( const std::string& name ): registerName( name )
	{
		std::string logFilePathAndName = pathToLogFile + registerName + logFileEnding;
		logFile = std::ifstream( logFilePathAndName );
	}

	Type getActualValue()
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
		return (Type)getIntegerFromString( result );
	}

private:
	std::string registerName;
	std::ifstream logFile;

	int getIntegerFromString( const std::string& stringToConvert )
	{
		return std::stoi( stringToConvert, nullptr, 0 );
	}
};



#endif /* REGISTER_REGISTERVALUEREADER_H_ */
