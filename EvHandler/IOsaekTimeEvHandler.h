///////////////////////////////////////////////////////////
//  IOsaekTimeEvHandler.h
//  Implementation of the Class IOsaekTimeEvHandler
//  Created on:      27-Nov-2017 14:37:33
//  Original author: aaron
///////////////////////////////////////////////////////////

#if !defined(EA_C07F282D_3D7C_40ab_ACEC_F8F587E678A4__INCLUDED_)
#define EA_C07F282D_3D7C_40ab_ACEC_F8F587E678A4__INCLUDED_

#include "../Obj/OsaekTime/OsaekTime.h"

class IOsaekTimeEvHandler
{

public:
	virtual void onOsaekTimeEv( const Obj::OsaekTime::OsaekTimeEv& ev ) = 0;

};
#endif // !defined(EA_C07F282D_3D7C_40ab_ACEC_F8F587E678A4__INCLUDED_)
