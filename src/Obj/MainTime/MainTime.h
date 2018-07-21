///////////////////////////////////////////////////////////
//  MainTime.h
//  Implementation of the Class MainTime
//  Created on:      27-Nov-2017 15:10:08
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_7400D07F_A1CE_4fbc_8E83_AE2C9A8521B7__INCLUDED_)
#define EA_7400D07F_A1CE_4fbc_8E83_AE2C9A8521B7__INCLUDED_

#include "../JudoDisplay/JudoDisplay.h"
#include "../../PltFrm/TimeTick/TimeTick.h"
#include "../../EvHandler/ITimeTickEvHandler.h"
#include "../../Util/Time/Time.h"

class IMainTimeEvHandler;

namespace Obj
{

class MainTime : public ITimeTickEvHandler, public Time
{

public:

    enum MainTimeEv
    {
        evTimeIsOver
    };

    enum MainTimeCountDir
    {
        up,
        down
    };

    enum
    {
        nrOfEvHandlers = 1,
        minInit = 4,
        secInit = 0
    };

	MainTime( JudoDisplay* displ );
	virtual ~MainTime();

	void start();
	void stop();
	void setCountDir( const MainTimeCountDir& dir );

	void regsiterOnEv( IMainTimeEvHandler* handler );
	virtual void onTimeTickEv(const PltFrm::TimeTick::TimeTickInstance& inst);

protected:
	void notify( const MainTimeEv& ev );

private:
    JudoDisplay *mDispl;
    PltFrm::TimeTick mTimeTick;

    MainTimeCountDir mDir;

    IMainTimeEvHandler* evHandler[nrOfEvHandlers];
};

} /* namespace Obj */

#endif // !defined(EA_7400D07F_A1CE_4fbc_8E83_AE2C9A8521B7__INCLUDED_)
