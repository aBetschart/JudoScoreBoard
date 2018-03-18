///////////////////////////////////////////////////////////
//  IScoreEvHandler.h
//  Implementation of the Class IScoreEvHandler
//  Created on:      27-Nov-2017 17:36:24
//  Original author: aaron
///////////////////////////////////////////////////////////

#if !defined(EA_7A30D6C2_B10D_4ad9_B216_97AA54116D5D__INCLUDED_)
#define EA_7A30D6C2_B10D_4ad9_B216_97AA54116D5D__INCLUDED_

#include "../Obj/Score/Score.h"

class IScoreEvHandler
{

public:
	virtual void onScoreEv( const Obj::Score::ScoreEv& ev ) = 0;

};
#endif // !defined(EA_7A30D6C2_B10D_4ad9_B216_97AA54116D5D__INCLUDED_)
