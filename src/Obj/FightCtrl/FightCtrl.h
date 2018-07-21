///////////////////////////////////////////////////////////
//  FightCtrl.h
//  Implementation of the Class FightCtrl
//  Created on:      29-Nov-2017 14:31:27
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_E2DCEA2C_B151_4c9b_867F_2042C6939179__INCLUDED_)
#define EA_E2DCEA2C_B151_4c9b_867F_2042C6939179__INCLUDED_

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "../JudoDisplay/JudoDisplay.h"

#include "../MainTimeCtrl/MainTimeCtrl.h"
#include "../ScoreCtrl/ScoreCtrl.h"
#include "../OsaekTimeCtrl/OsaekTimeCtrl.h"

#include "../../EvHandler/IOsaekCtrlEvHandler.h"
#include "../../EvHandler/IMainTimeCtrlEvHandler.h"
#include "../../EvHandler/IScoreCtrlEvHandler.h"
//--------------------------------------------------------------

namespace Obj
{

class FightCtrl : public IOsaekCtrlEvHandler, public IScoreCtrlEvHandler, public IMainTimeCtrlEvHandler
{

public:

    enum FightCtrlEv
    {
        evOsaekOver,
        evTimeIsOver,
        evWinnerFound,
        evWinnerCanceled
    };

	FightCtrl();
	virtual ~FightCtrl();

	void process( const FightCtrlEv& ev );

	bool goldenScore();
	bool timeIsRunning();
	bool osaekomiIsRunning();
	bool equalScore();
	bool hasWinner();

	virtual void onOsaekTimeCtrlEv( Obj::OsaekTimeCtrl::OsaekCtrlEv ev );
	virtual void onMainTimeCtrlEv( const Obj::MainTimeCtrl::MainTimeCtrlEv& ev);
	virtual void onScoreCtrlEv( const Obj::ScoreCtrl::ScoreCtrlEv& ev );

private:

	enum FightCtrlState
	{
	    stateNormal,
	    stateWinnerFound,
	    stateTimeIsOver,
	    stateWaitForOsaekomi,
	    stateGoldenScore,
	    stateGoldenScoreEnd
	};

	FightCtrlState mState;

	JudoDisplay displ;
	//Fight mFight;
	MainTimeCtrl mMainTimeCtrl;
	OsaekTimeCtrl mOsaekTimeCtrl;
	ScoreCtrl mScoreCtrl;
};

} // namespace Obj

#endif // !defined(EA_E2DCEA2C_B151_4c9b_867F_2042C6939179__INCLUDED_)
