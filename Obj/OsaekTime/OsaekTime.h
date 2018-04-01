///////////////////////////////////////////////////////////
//  OsaekTime.h
//  Implementation of the Class OsaekTime
//  Created on:      27-Nov-2017 14:35:12
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_DFD44571_52F2_4385_9903_C618732A12AC__INCLUDED_)
#define EA_DFD44571_52F2_4385_9903_C618732A12AC__INCLUDED_

#include "../JudoDisplay/JudoDisplay.h"
#include "../../EvHandler/ITimeTickEvHandler.h"
#include "../../PltFrm/TimeTick/TimeTick.h"
#include "../../Util/Time/Time.h"

class IOsaekTimeEvHandler;

namespace Obj
{

class OsaekTime : public ITimeTickEvHandler, public Time
{

public:

    enum OsaekTimeEv
    {
        evIpponTime,
        evWazariTime
    };

    enum
    {
        nrOfEvHandlers = 1,
        wazariTime = 10,
        ipponTime  = 20
    };

	OsaekTime( JudoDisplay* displ );
	virtual ~OsaekTime();

	void start();
	void stop();

	void registerOnEv( IOsaekTimeEvHandler* handler );
	virtual void onTimeTickEv(const PltFrm::TimeTick::TimeTickInstance& inst);

protected:
	void notify( const OsaekTimeEv& ev );

private:

	JudoDisplay* mDispl;
	PltFrm::TimeTick mTimeTick;

	IOsaekTimeEvHandler* evHandler[nrOfEvHandlers];
};

}/* namespace Obj */

#endif // !defined(EA_DFD44571_52F2_4385_9903_C618732A12AC__INCLUDED_)
