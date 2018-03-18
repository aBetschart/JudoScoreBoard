///////////////////////////////////////////////////////////
//  IScoreCtrlEvHandler.h
//  Implementation of the Class IScoreCtrlEvHandler
//  Created on:      30-Nov-2017 10:31:08
//  Original author: aaron
///////////////////////////////////////////////////////////

#if !defined(EA_04049052_C483_42a2_832B_BE5D7584F60F__INCLUDED_)
#define EA_04049052_C483_42a2_832B_BE5D7584F60F__INCLUDED_

#include "../Obj/ScoreCtrl/ScoreCtrl.h"

class IScoreCtrlEvHandler
{
public:
    virtual void onScoreCtrlEv( const Obj::ScoreCtrl::ScoreCtrlEv& ev ) = 0;
};
#endif // !defined(EA_04049052_C483_42a2_832B_BE5D7584F60F__INCLUDED_)
