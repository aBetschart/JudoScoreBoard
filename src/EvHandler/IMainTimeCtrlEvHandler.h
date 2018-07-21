///////////////////////////////////////////////////////////
//  IMainTimeCtrlEvHandler.h
//  Implementation of the Class IMainTimeCtrlEvHandler
//  Created on:      30-Nov-2017 10:42:26
//  Original author: aaron
///////////////////////////////////////////////////////////

#if !defined(EA_EAEAB497_E0BE_456d_B4FD_63169D5BC399__INCLUDED_)
#define EA_EAEAB497_E0BE_456d_B4FD_63169D5BC399__INCLUDED_

#include "../Obj/MainTimeCtrl/MainTimeCtrl.h"

class IMainTimeCtrlEvHandler
{
public:
    virtual void onMainTimeCtrlEv( const Obj::MainTimeCtrl::MainTimeCtrlEv& ev) = 0;
};
#endif // !defined(EA_EAEAB497_E0BE_456d_B4FD_63169D5BC399__INCLUDED_)
