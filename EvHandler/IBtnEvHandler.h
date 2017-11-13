///////////////////////////////////////////////////////////
//  IBtnEvHandler.h
//  Implementation of the Class IBtnEvHandler
//  Created on:      11-Nov-2017 14:48:26
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_A96AE272_F6B6_4fcf_A246_09E8CACB4EAA__INCLUDED_)
#define EA_A96AE272_F6B6_4fcf_A246_09E8CACB4EAA__INCLUDED_

#include "../PltFrm/Btn/Btn.h"

class IBtnEvHandler
{

public:
	virtual void onButtonEv( const PltFrm::Btn::BtnInstance& btn ) = 0;
};
#endif // !defined(EA_A96AE272_F6B6_4fcf_A246_09E8CACB4EAA__INCLUDED_)
