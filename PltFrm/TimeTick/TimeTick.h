///////////////////////////////////////////////////////////
//  TimeTick.h
//  Implementation of the Class TimeTick
//  Created on:      12-Nov-2017 20:06:50
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_827A203B_1849_40e3_B09A_A1FB64B0B711__INCLUDED_)
#define EA_827A203B_1849_40e3_B09A_A1FB64B0B711__INCLUDED_

#include "../../Hal/Timer/Timer.h"
#include "../../EvHandler/ITimerEvHandler.h"

class ITimeTickEvHandler;

namespace PltFrm
{

class TimeTick : public ITimerEvHandler
{

public:
    enum TimeTickInstance
    {
        mainTimeTick,  // 1 s
        osaekTimeTick, // 1 s
        scoreBtnTick,  // 300 ms
        timeBtnTick,   // 300 ms
        nrOfTimeTicks
    };

    enum { nrOfEvHandlers = 1 };

	TimeTick( const TimeTickInstance& t );
	virtual ~TimeTick();

	void enable();
	void disable();

	TimeTickInstance getInstance();

	virtual void onTimerEv( const Hal::Timer::Timer& timer,
                            const Hal::Timer::TimerEv ev );
	void registerOnEv( ITimeTickEvHandler* handler );

protected:
	void notify();

private:

	TimeTickInstance mInst;

	static TimeTick* instance[nrOfTimeTicks];

	Hal::Timer mTimer;
	ITimeTickEvHandler* evHandler[nrOfEvHandlers];

};

} /* namespace PltFrm*/
#endif // !defined(EA_827A203B_1849_40e3_B09A_A1FB64B0B711__INCLUDED_)
