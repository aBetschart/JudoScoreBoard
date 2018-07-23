/*
 * TimeMethodsTest.cpp
 *
 *  Created on: 22.07.2018
 *      Author: aaron
 */

#include "gtest/gtest.h"
#include "Util/Time/Time.h"

#include "TimeTestSupportables.h"

//--------------------------------------------------------------
class TimeMethodsTest: public ::testing::Test
{
protected:
	Time time;
};
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, incSecondTest1 )
{
	ComparationTime initValue = {.hour = 0, .min=1, .sec=32};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	int stepNr = 1;
	operateInstructionStepNrTimes( time, increment, second, stepNr );

	ComparationTime comparationTime = {.hour = 0, .min=1, .sec=33};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, incSecondTest2 )
{
	ComparationTime initValue = {.hour = 1, .min=1, .sec=59};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	int stepNr = 27;
	operateInstructionStepNrTimes( time, increment, second, stepNr );

	ComparationTime comparationTime = {.hour = 1, .min=2, .sec=26};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, decSecondTest1 )
{
	ComparationTime initValue = {.hour = 0, .min=0, .sec=3};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	int stepNr = 27;
	operateInstructionStepNrTimes( time, decrement, second, stepNr );

	ComparationTime comparationTime = {.hour = 0, .min=0, .sec=0};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, decSecondTest2 )
{
	ComparationTime initValue = {.hour = 4, .min=0, .sec=3};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	int stepNr = 10;
	operateInstructionStepNrTimes( time, decrement, second, stepNr );

	ComparationTime comparationTime = {.hour = 3, .min=59, .sec=53};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, incMinuteTest1 )
{
	ComparationTime initValue = {.hour = 2, .min=1, .sec=59};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	int stepNr = 42;
	operateInstructionStepNrTimes( time, increment, minute, stepNr );

	ComparationTime comparationTime = {.hour = 2, .min=43, .sec=59};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, incMinuteTest2 )
{
	ComparationTime initValue = {.hour = 2, .min=39, .sec=59};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	int stepNr = 30;
	operateInstructionStepNrTimes( time, increment, minute, stepNr );

	ComparationTime comparationTime = {.hour = 3, .min=9, .sec=59};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, decMinuteTest1 )
{
	ComparationTime initValue = {.hour = 4, .min=0, .sec=3};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	int stepNr = 10;
	operateInstructionStepNrTimes( time, decrement, minute, stepNr );

	ComparationTime comparationTime = {.hour = 3, .min=50, .sec=3};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, decMinuteTest2 )
{
	ComparationTime initValue = {.hour = 27, .min=3, .sec=29};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	int stepNr = 120;
	operateInstructionStepNrTimes( time, decrement, minute, stepNr );

	ComparationTime comparationTime = {.hour =25, .min=3, .sec=29};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, incHourTest1 )
{
	ComparationTime initValue = {.hour = 2, .min=39, .sec=59};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	int stepNr = 201;
	operateInstructionStepNrTimes( time, increment, hour, stepNr );

	ComparationTime comparationTime = {.hour = 203, .min=39, .sec=59};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------

//--------------------------------------------------------------
TEST_F( TimeMethodsTest, decHourTest1 )
{
	ComparationTime initValue = {.hour = 27, .min=3, .sec=29};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	int stepNr = 89;
	operateInstructionStepNrTimes( time, decrement, hour, stepNr );

	ComparationTime comparationTime = {.hour =0, .min=3, .sec=29};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, decHourTest2 )
{
	ComparationTime initValue = {.hour = 442, .min=20, .sec=41};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	int stepNr = 89;
	operateInstructionStepNrTimes( time, decrement, hour, stepNr );

	ComparationTime comparationTime = {.hour =353, .min=20, .sec=41};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, getOnesAndTensOfSecond1 )
{
	ComparationTime initValue = {.hour = 442, .min=20, .sec=41};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	ASSERT_EQ( time.getOnesOfSec(), (initValue.sec%10) );
	ASSERT_EQ( time.getTensOfSec(), (initValue.sec/10) );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, getOnesAndTensOfSecond2 )
{
	ComparationTime initValue = {.hour = 442, .min=20, .sec=0};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	ASSERT_EQ( time.getOnesOfSec(), (initValue.sec%10) );
	ASSERT_EQ( time.getTensOfSec(), (initValue.sec/10) );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, getOnesAndTensOfMinute1 )
{
	ComparationTime initValue = {.hour = 442, .min=0, .sec=0};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	ASSERT_EQ( time.getOnesOfMin(), (initValue.min%10) );
	ASSERT_EQ( time.getTensOfMin(), (initValue.min/10) );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, getOnesAndTensOfMinute2 )
{
	ComparationTime initValue = {.hour = 442, .min=20, .sec=0};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	ASSERT_EQ( time.getOnesOfMin(), (initValue.min%10) );
	ASSERT_EQ( time.getTensOfMin(), (initValue.min/10) );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, isZeroTest1 )
{
	ComparationTime initValue = {.hour = 32, .min=19, .sec=41};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	int stepNr = initValue.hour;
	operateInstructionStepNrTimes( time, decrement, hour, stepNr );
	stepNr = initValue.min;
	operateInstructionStepNrTimes( time, decrement, minute, stepNr );
	stepNr = initValue.sec;
	operateInstructionStepNrTimes( time, decrement, second, stepNr );

	ASSERT_TRUE( time.isZero() );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeMethodsTest, isZeroTest2 )
{
	ComparationTime initValue = {.hour = 0, .min=0, .sec=0};
	time.reset( initValue.hour, initValue.min, initValue.sec );

	int stepNr = 20;
	operateInstructionStepNrTimes( time, increment, hour, stepNr );
	stepNr = 43;
	operateInstructionStepNrTimes( time, increment, minute, stepNr );
	stepNr = 32;
	operateInstructionStepNrTimes( time, increment, second, stepNr );

	ASSERT_FALSE( time.isZero() );
}
//--------------------------------------------------------------

