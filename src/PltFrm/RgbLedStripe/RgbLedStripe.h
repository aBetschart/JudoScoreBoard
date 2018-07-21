///////////////////////////////////////////////////////////
//  RgbLedStripe.h
//  Implementation of the Class RgbLedStripe
//  Created on:      20-Nov-2017 14:23:20
//  Original author: aaron
///////////////////////////////////////////////////////////

#if !defined(EA_202B5FE8_581C_47b8_B4D2_2C6FF9E48864__INCLUDED_)
#define EA_202B5FE8_581C_47b8_B4D2_2C6FF9E48864__INCLUDED_

#include <stdint.h>

#include "../../EvHandler/ISpiEvHandler.h"
#include "../../EvHandler/ITimeTickEvHandler.h"
#include "../../Hal/Spi/Spi.h"
#include "../../Util/Stack/Stack.h"

class IRgbLedStripeEvHandler;

namespace PltFrm
{

class RgbLedStripe : public ISpiEvHandler, public ITimeTickEvHandler
{

public:
    enum RgbLedStripeInstance
    {
        displayStripe,
        nrOfRgbLedStripes
    };

    enum RgbLedStripeEv
    {
        evShiftComplete,
        nrOfRgbLedStripeEv
    };

    struct LedColor
    {
        uint8_t r; // red
        uint8_t g; // green
        uint8_t b; // blue
    };

	RgbLedStripe( const RgbLedStripeInstance& inst );
	virtual ~RgbLedStripe();

	void setShiftVal( const LedColor* val, int n );
	void shiftIn();

	bool isShifting() const;

	void registerOnEv( IRgbLedStripeEvHandler* handler );
	virtual void onSpiEv(const Hal::Spi::SpiInstance& inst, const Hal::Spi::SpiEv& ev);
	virtual void onTimeTickEv(const PltFrm::TimeTick::TimeTickInstance& inst);

	enum
	{
	    nrOfLeds = 11*7*2,
	    nrOfEvHandlers = 1
	};

protected:

	void notify( const RgbLedStripeEv& ev );

private:

	enum RgbLedStripeState
	{
	    idle,
	    ready,
	    shifting,
	};

	static RgbLedStripe* instance[nrOfRgbLedStripes];

	IRgbLedStripeEvHandler* evHandler[nrOfEvHandlers];
	Hal::Spi mSpi;
	PltFrm::TimeTick mTimeTick;

	Stack<uint8_t, nrOfLeds*3> stack;

	RgbLedStripeInstance mInst;
	RgbLedStripeState mState;
};

} /* namespace PltFrm */

#endif // !defined(EA_202B5FE8_581C_47b8_B4D2_2C6FF9E48864__INCLUDED_)
