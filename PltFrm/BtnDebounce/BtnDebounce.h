///////////////////////////////////////////////////////////
//  BtnDebounce.h
//  Implementation of the Class BtnDebounce
//  Created on:      13-Nov-2017 11:04:32
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_62AD15AB_C4F7_4fbd_9544_B2B78636E7B2__INCLUDED_)
#define EA_62AD15AB_C4F7_4fbd_9544_B2B78636E7B2__INCLUDED_

#include "../Btn/Btn.h"
#include "../TimeTick/TimeTick.h"
#include "../../EvHandler/ITimeTickEvHandler.h"
#include "../../EvHandler/IBtnEvHandler.h"

namespace PltFrm
{

template<int nrOfBtns = 1>
class BtnDebounce : public IBtnEvHandler, public ITimeTickEvHandler
{

public:
    BtnDebounce( const PltFrm::TimeTick::TimeTickInstance& inst );
	virtual ~BtnDebounce();

	void registerBtn( PltFrm::Btn* btn );
	virtual void onButtonEv( const PltFrm::Btn::BtnInstance& btn );
	virtual void onTimeTickEv( const PltFrm::TimeTick::TimeTickInstance& inst );

private:
	PltFrm::Btn* mBtn[nrOfBtns];
	PltFrm::TimeTick mTimeTick;
};

} /* namespace PltFrm*/
#endif // !defined(EA_62AD15AB_C4F7_4fbd_9544_B2B78636E7B2__INCLUDED_)
