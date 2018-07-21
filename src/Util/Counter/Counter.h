///////////////////////////////////////////////////////////
//  Counter.h
//  Implementation of the Class Counter
//  Created on:      15-Nov-2017 11:13:19
//  Original author: aaron
///////////////////////////////////////////////////////////

#if !defined(EA_99B6FA91_98BB_4e59_94FA_15687222AF9F__INCLUDED_)
#define EA_99B6FA91_98BB_4e59_94FA_15687222AF9F__INCLUDED_

class Counter
{

public:
	Counter( const int& initVal = 0 );
	void decrement();
	void increment();
	int getCountVal();
	void reset( const int& resVal = 0 );

private:
	int val;

};
#endif // !defined(EA_99B6FA91_98BB_4e59_94FA_15687222AF9F__INCLUDED_)
