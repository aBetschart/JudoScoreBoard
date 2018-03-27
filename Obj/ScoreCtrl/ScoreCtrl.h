///////////////////////////////////////////////////////////
//  ScoreCtrl.h
//  Implementation of the Class ScoreCtrl
//  Created on:      29-Nov-2017 14:33:14
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_63E61DC3_351A_4d70_9595_F56535AFC4E8__INCLUDED_)
#define EA_63E61DC3_351A_4d70_9595_F56535AFC4E8__INCLUDED_

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "../Score/Score.h"
#include "../OsaekTimeCtrl/OsaekTimeCtrl.h"

#include "../../PltFrm/Led/Led.h"

#include "../../EvHandler/IScoreEvHandler.h"
//--------------------------------------------------------------


class IScoreCtrlEvHandler;

namespace Obj
{

class JudoDisplay;
class FightCtrl;

class ScoreCtrl : public IScoreEvHandler
{

public:

    enum ScoreCtrlEv
    {
        // Controlling events
        evIppon,
        evIpponDel,
        evDisqual,
        evDisqualDel,
        evEqualScore,
        evEqualScoreLost,

        // Events, that trigger the event-handlers
        evWinnerFound,
        evWinnerCanceled,
    };

    enum { nrOfEvHandlers = 1 };

    ScoreCtrl( FightCtrl* fightCtrl, OsaekTimeCtrl* osaekCtrl, JudoDisplay* displ );
    virtual ~ScoreCtrl();

    void process( const ScoreCtrlEv& ev );

	bool equalScore();
	bool winnerFound();

	void registerOnEv( IScoreCtrlEvHandler* handler );

	virtual void onScoreEv( const Obj::Score::ScoreEv& ev );

protected:
	void notify( const ScoreCtrlEv& ev );

private:

	enum ScoreCtrlState
	{
	    stateNoWinner,
	    stateWinnerFound
	};

	ScoreCtrlState mState;

    Score mScore;
    PltFrm::Led winnerLed;

    FightCtrl* mFightCtrl;

    IScoreCtrlEvHandler* evHandler[nrOfEvHandlers];
};

} // namespace Obj

#endif // !defined(EA_63E61DC3_351A_4d70_9595_F56535AFC4E8__INCLUDED_)
