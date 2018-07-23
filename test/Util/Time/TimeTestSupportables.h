/*
 * TimeTestSupportables.cpp
 *
 *  Created on: 23.07.2018
 *      Author: aaron
 */

#ifndef TIMETESTSUPPORTABLES_H
#define TIMETESTSUPPORTABLES_H

#include "gtest/gtest.h"
#include "Util/Time/Time.h"

struct ComparationTime
{
	int hour;
	int min;
	int sec;
};

enum OperationType
{
	increment,
	decrement
};

enum OperationAttribute
{
	second,
	minute,
	hour
};

void compareTimeToExpectedValue( const Time& actualTime, const ComparationTime& expectedTime );
void operateInstructionStepNrTimes(  Time& time, const OperationType& operationType,
								const OperationAttribute& operationAttribute, const int& stepNr );

#endif //TIMETESTSUPPORTABLES_H
