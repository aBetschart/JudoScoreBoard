/*
 * CoutnerTest.cpp
 *
 *  Created on: 22.07.2018
 *      Author: aaron
 */

#include "gtest/gtest.h"
#include "Util/Counter/Counter.h"

//--------------------------------------------------------------
void checkCountValue( const Counter& checkedCounter, const int& expectedValue )
{
	ASSERT_EQ( checkedCounter.getCountVal(), expectedValue );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void incrementNrOfSteps( Counter& counter, const int& steps )
{
	for( int i = 0 ; i < steps ; ++i )
		counter.increment();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void decrementNrOfSteps( Counter& counter, const int& steps )
{
	for( int i = 0 ; i < steps ; ++i )
		counter.decrement();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
class CounterTest: public ::testing::Test
{

};
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( CounterTest, ConstructorTest1 )
{
	int testedValue = 22;
	Counter counter( testedValue );

	checkCountValue( counter, testedValue );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( CounterTest, ConstrutorTest2 )
{
	int defaultValue = 0;
	Counter counter;

	checkCountValue( counter, defaultValue );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( CounterTest, incrementTest1 )
{
	int initValue = 35;
	Counter counter( initValue );

	int nrOfIncrements = 32;
	incrementNrOfSteps( counter, nrOfIncrements );

	checkCountValue( counter, initValue + nrOfIncrements );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( CounterTest, incrementTest2 )
{
	int initValue = -432;
	Counter counter( initValue );

	int nrOfIncrements = 852;
	incrementNrOfSteps( counter, nrOfIncrements );

	checkCountValue( counter, initValue + nrOfIncrements );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( CounterTest, decrementTest1 )
{
	int initValue = -4;
	Counter counter( initValue );

	int nrOfDecrements = 42;
	decrementNrOfSteps( counter, nrOfDecrements );

	checkCountValue( counter, initValue - nrOfDecrements );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( CounterTest, decrementTest2 )
{
	int initValue = -432;
	Counter counter( initValue );

	int nrOfDecrements = 852;
	decrementNrOfSteps( counter, nrOfDecrements );

	checkCountValue( counter, initValue - nrOfDecrements );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( CounterTest, resetTest1 )
{
	int initValue = -432;
	Counter counter( initValue );

	int resetValue = 324;
	counter.reset( resetValue );

	checkCountValue( counter, resetValue );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
TEST_F( CounterTest, resetTest2 )
{
	int initValue = 32;
	Counter counter( initValue );

	counter.reset();

	int resetValue = 0;
	checkCountValue( counter, resetValue );
}
//--------------------------------------------------------------
