///////////////////////////////////////////////////////////
//  IMainTimeEvHandler.h
//  Implementation of the Class IMainTimeEvHandler
//  Created on:      27-Nov-2017 15:11:39
//  Original author: aaron
///////////////////////////////////////////////////////////

#if !defined(EA_901D02D3_1DEF_419a_BD24_042CD6BAD553__INCLUDED_)
#define EA_901D02D3_1DEF_419a_BD24_042CD6BAD553__INCLUDED_

#include "../Obj/MainTime/MainTime.h"

class IMainTimeEvHandler
{

public:
	virtual void onMainTimeEv( const Obj::MainTime::MainTimeEv& ev ) = 0;

};
#endif // !defined(EA_901D02D3_1DEF_419a_BD24_042CD6BAD553__INCLUDED_)
