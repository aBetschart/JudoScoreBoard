///////////////////////////////////////////////////////////
//  ITimeTickEvHandler.h
//  Implementation of the Class ITimeTickEvHandler
//  Created on:      12-Nov-2017 20:21:27
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_BE5C97E5_8144_4f40_B231_93E476AAD317__INCLUDED_)
#define EA_BE5C97E5_8144_4f40_B231_93E476AAD317__INCLUDED_

#include "../PltFrm/TimeTick/TimeTick.h"

class ITimeTickEvHandler
{
public:
	virtual void onTimeTickEv( const PltFrm::TimeTick::TimeTickInstance& inst ) = 0;
};
#endif // !defined(EA_BE5C97E5_8144_4f40_B231_93E476AAD317__INCLUDED_)
