///////////////////////////////////////////////////////////
//  OsaekTimeCtrl.h
//  Implementation of the Class OsaekTimeCtrl
//  Created on:      29-Nov-2017 14:35:09
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_66C9942B_FF0D_4316_8A7E_24DF28EB5DAF__INCLUDED_)
#define EA_66C9942B_FF0D_4316_8A7E_24DF28EB5DAF__INCLUDED_

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "../OsaekTime/OsaekTime.h"

#include "../../PltFrm/BtnDebounce/BtnDebounce.h"
#include "../../PltFrm/Btn/Btn.h"

#include "../../EvHandler/IBtnEvHandler.h"
#include "../../EvHandler/IOsaekTimeEvHandler.h"
//--------------------------------------------------------------

class IOsaekCtrlEvHandler;

namespace Obj
{

class JudoDisplay;
class FightCtrl;

class OsaekTimeCtrl : public IOsaekTimeEvHandler, public IBtnEvHandler
{

public:

    enum OsaekCtrlEv
    {
        // Controlling events
        evStartBl,
        evStartWh,
        evStopBl,
        evStopWh,
        evIpponTime,
        evWazariTime,

        // Events, which trigger the event handlers
        evOsaekOver,
        evIpponTimeBl,
        evWazariTimeBl,
        evIpponTimeWh,
        evWazariTimeWh
    };

    enum { nrOfEvHandlers = 1 };

	OsaekTimeCtrl( JudoDisplay* displ, FightCtrl* fightCtrl );
	virtual ~OsaekTimeCtrl();

	void process( const OsaekCtrlEv& ev );

	bool osaekomiRunning();

	void registerOnEv( IOsaekCtrlEvHandler* handler );
	virtual void onOsaekTimeEv( const Obj::OsaekTime::OsaekTimeEv& ev );
	virtual void onButtonEv( const PltFrm::Btn::BtnInstance& btn );

protected:
	void notify( const OsaekCtrlEv& ev );

private:

	enum OsaekTimeCtrlState
	{
	    stateOsaekBl,
	    stateOsaekWh,
	    stateStop
	};

	OsaekTimeCtrlState mState;

	OsaekTime mOsaekTime;
	PltFrm::BtnDebounce mBtnDeb;
	FightCtrl* mFightCtrl;

	PltFrm::Btn osaekBlBtn;
	PltFrm::Btn osaekWhBtn;

	IOsaekCtrlEvHandler* evHandler[nrOfEvHandlers];

};

} // namespace Obj

#endif // !defined(EA_66C9942B_FF0D_4316_8A7E_24DF28EB5DAF__INCLUDED_)
