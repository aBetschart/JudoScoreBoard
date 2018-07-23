/*
 * TimeInitializeTest.cpp
 *
 *  Created on: 22.07.2018
 *      Author: aaron
 */

#include "gtest/gtest.h"
#include "Util/Time/Time.h"
#include "TimeTestSupportables.h"

//--------------------------------------------------------------
class TimeInitializeTest: public ::testing::Test
{

};
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeInitializeTest, constructorTest1 )
{
	ComparationTime initValue = {.hour = 0, .min=1, .sec=65};
	Time time( initValue.hour, initValue.min, initValue.sec );

	ComparationTime comparationTime = {.hour = 0, .min=2, .sec=5};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeInitializeTest, constructorTest2 )
{
	ComparationTime initValue = {.hour = 54, .min=4, .sec=120};
	Time time( initValue.hour, initValue.min, initValue.sec );

	ComparationTime comparationTime = {.hour = 54, .min=6, .sec=0};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeInitializeTest, constructorTest3 )
{
	ComparationTime initValue = {.hour = 534, .min=9, .sec=119};
	Time time( initValue.hour, initValue.min, initValue.sec );

	ComparationTime comparationTime = {.hour = 534, .min=10, .sec=59};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeInitializeTest, constructorTest4 )
{
	ComparationTime initValue = {.hour = -32, .min=-30, .sec=-12};
	Time time( initValue.hour, initValue.min, initValue.sec );

	ComparationTime comparationTime = {.hour = 32, .min=30, .sec=12};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeInitializeTest, constructorTest5 )
{
	ComparationTime initValue = {.hour = 9, .min=-1, .sec=-61};
	Time time( initValue.hour, initValue.min, initValue.sec );

	ComparationTime comparationTime = {.hour = 9, .min=2, .sec=1};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeInitializeTest, constructorTest6 )
{
	ComparationTime initValue = {.hour = 9, .min=-1, .sec=-61};
	Time time( initValue.hour, initValue.min, initValue.sec );

	ComparationTime comparationTime = {.hour = 9, .min=2, .sec=1};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeInitializeTest, constructorTest7)
{
	ComparationTime initValue = {.hour = 0, .min=59, .sec=60};
	Time time( initValue.hour, initValue.min, initValue.sec );

	ComparationTime comparationTime = {.hour=1, .min=0, .sec=0};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeInitializeTest, constructorTest8)
{
	ComparationTime initValue = {.hour = -1, .min=59, .sec=60};
	Time time( initValue.hour, initValue.min, initValue.sec );

	ComparationTime comparationTime = {.hour=2, .min=0, .sec=0};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( TimeInitializeTest, constructorTest9)
{
	ComparationTime initValue = {.hour = 59, .min=59, .sec=124};
	Time time( initValue.hour, initValue.min, initValue.sec );

	ComparationTime comparationTime = {.hour=60, .min=1, .sec=4};
	compareTimeToExpectedValue( time, comparationTime );
}
//--------------------------------------------------------------
