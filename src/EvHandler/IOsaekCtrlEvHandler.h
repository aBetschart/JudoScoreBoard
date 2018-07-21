///////////////////////////////////////////////////////////
//  IOsaekCtrlEvHandler.h
//  Implementation of the Class IOsaekCtrlEvHandler
//  Created on:      29-Nov-2017 14:34:05
//  Original author: aaron
///////////////////////////////////////////////////////////

#if !defined(EA_37392F4A_2414_4028_8ACE_49E0CD58A5C3__INCLUDED_)
#define EA_37392F4A_2414_4028_8ACE_49E0CD58A5C3__INCLUDED_

#include "../Obj/OsaekTimeCtrl/OsaekTimeCtrl.h"

class IOsaekCtrlEvHandler
{

public:

	virtual void onOsaekTimeCtrlEv( Obj::OsaekTimeCtrl::OsaekCtrlEv ev ) = 0;

};
#endif // !defined(EA_37392F4A_2414_4028_8ACE_49E0CD58A5C3__INCLUDED_)
