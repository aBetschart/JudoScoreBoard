/**
 * TimeTestSupportables.cpp
 */

#include "TimeTestSupportables.h"

#include "gtest/gtest.h"
#include "Util/Time/Time.h"

void compareTimeToExpectedValue( const Time& actualTime, const ComparationTime& expectedTime )
{
	ASSERT_EQ( actualTime.getHour(), expectedTime.hour );
	ASSERT_EQ( actualTime.getMin(),  expectedTime.min );
	ASSERT_EQ( actualTime.getSec(),  expectedTime.sec );
}

void operateInstructionStepNrTimes(Time& time, const OperationType& operationType,
		const OperationAttribute& operationAttribute, const int& stepNr)
{
	switch( operationAttribute )
	{
	case second:
		if( operationType == increment )
			for( int i = 0 ; i < stepNr ; ++i )
				time.incSec();
		else
			for( int i = 0 ; i < stepNr ; ++i )
				time.decSec();
		break;
	case minute:
		if( operationType == increment )
			for( int i = 0 ; i < stepNr ; ++i )
				time.incMin();
		else
			for( int i = 0 ; i < stepNr ; ++i )
				time.decMin();
		break;
	case hour:
		if( operationType == increment )
			for( int i = 0 ; i < stepNr ; ++i )
				time.incHour();
		else
			for( int i = 0 ; i < stepNr ; ++i )
				time.decHour();
		break;
	default:
		break;
	}
}
