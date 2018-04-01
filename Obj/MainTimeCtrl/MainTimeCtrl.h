///////////////////////////////////////////////////////////
//  MainTimeCtrl.h
//  Implementation of the Class MainTimeCtrl
//  Created on:      29-Nov-2017 14:33:28
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_6E455FCC_0A5B_4c22_8DE9_474B772394A6__INCLUDED_)
#define EA_6E455FCC_0A5B_4c22_8DE9_474B772394A6__INCLUDED_

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "../MainTime/MainTime.h"

#include "../../PltFrm/BtnDebounce/BtnDebounce.h"
#include "../../PltFrm/Btn/Btn.h"
#include "../../PltFrm/Led/Led.h"

#include "../../EvHandler/IMainTimeEvHandler.h"
#include "../../EvHandler/IBtnEvHandler.h"
//--------------------------------------------------------------

class IMainTimeCtrlEvHandler;

namespace Obj
{

class JudoDisplay;
class FightCtrl;

class MainTimeCtrl : public IMainTimeEvHandler, public IBtnEvHandler
{

public:

    enum MainTimeCtrlEv
    {                   /* Controlling    | Triggers    */
        evStart,        /*           x    |             */
        evStop,         /*           x    |             */
        evGoldenScore,  /*           x    |             */
        evTimeIsOver,   /*           x    |         x   */
    };

    enum { nrOfEvHandlers = 1 };

	MainTimeCtrl( JudoDisplay* displ, FightCtrl* fightCtrl );
	virtual ~MainTimeCtrl();

	void process( const MainTimeCtrlEv& ev );

	bool isRunning();

	void registerOnEv( IMainTimeCtrlEvHandler* handler );
	virtual void onMainTimeEv( const Obj::MainTime::MainTimeEv& ev );
	void onButtonEv( const PltFrm::Btn::BtnInstance& btn );

protected:
	void notify( const MainTimeCtrlEv& ev );

private:

	enum MainTimeCtrlState
	{
	    stateCountDown,
	    stateStopCountDown,
	    stateCountUp,
	    stateStopCountUp
	};

	MainTimeCtrlState mState;

	MainTime mMainTime;
	PltFrm::BtnDebounce mBtnDebounce;
	PltFrm::Btn startBtn;
	PltFrm::Btn stopBtn;
	PltFrm::Led timeRunLed;

	FightCtrl* mFightCtrl;

	IMainTimeCtrlEvHandler* evHandler[nrOfEvHandlers];
};

} // namespace Obj

#endif // !defined(EA_6E455FCC_0A5B_4c22_8DE9_474B772394A6__INCLUDED_)
