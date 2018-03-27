///////////////////////////////////////////////////////////
//  Score.h
//  Implementation of the Class Score
//  Created on:      27-Nov-2017 17:14:15
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_24F90FAF_BD0A_4f4e_89D4_AC7E5B538EAF__INCLUDED_)
#define EA_24F90FAF_BD0A_4f4e_89D4_AC7E5B538EAF__INCLUDED_

#include "../JudoDisplay/JudoDisplay.h"
#include "../OsaekTimeCtrl/OsaekTimeCtrl.h"
#include "../../PltFrm/Switch/Switch.h"
#include "../../PltFrm/Btn/Btn.h"
#include "../../EvHandler/IBtnEvHandler.h"
#include "../../EvHandler/IOsaekCtrlEvHandler.h"
#include "../../PltFrm/BtnDebounce/BtnDebounce.h"
#include "../Judo.h"


class IScoreEvHandler;

namespace Obj
{

class Score : public IBtnEvHandler, public IOsaekCtrlEvHandler
{

public:

    enum ScoreEv
    {
        evIppon,
        evIpponDel,
        evDisqual,
        evDisqualDel,
        evEqualScore,
        evEqualScoreLost
    };

    enum { nrOfEvHandlers = 1 };

    enum
    {
        maxShido  = 3
    };

	Score( JudoDisplay* displ, OsaekTimeCtrl* osaekCtrl );
	virtual ~Score();

	bool equalScore();
	bool hasWinner();

	void lock();
	void unlock();

	void registerOnEv( IScoreEvHandler* handler );
	virtual void onButtonEv(const PltFrm::Btn::BtnInstance& btn);
	virtual void onOsaekTimeCtrlEv(Obj::OsaekTimeCtrl::OsaekCtrlEv ev);

protected:
	void notify( const ScoreEv& ev );

private:

	bool locked;
	FighterScore score[nrOfFighterColours];

	PltFrm::Switch scoreSw;

	PltFrm::Btn ipponBlBtn;
	PltFrm::Btn wazariBlBtn;
	PltFrm::Btn shidoBlBtn;

	PltFrm::Btn ipponWhBtn;
	PltFrm::Btn wazariWhBtn;
	PltFrm::Btn shidoWhBtn;

	PltFrm::BtnDebounce btnDeb;

	JudoDisplay *mDispl;
	OsaekTimeCtrl *mOsaekCtrl;

    IScoreEvHandler* evHandler[nrOfEvHandlers];
};

} /* namespace Obj */

#endif // !defined(EA_24F90FAF_BD0A_4f4e_89D4_AC7E5B538EAF__INCLUDED_)
