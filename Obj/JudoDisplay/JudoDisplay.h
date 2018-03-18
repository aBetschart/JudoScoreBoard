///////////////////////////////////////////////////////////
//  JudoDisplay.h
//  Implementation of the Class JudoDisplay
//  Created on:      15-Nov-2017 11:22:10
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_62DD92B3_88E0_4928_B206_640A0A112CAE__INCLUDED_)
#define EA_62DD92B3_88E0_4928_B206_640A0A112CAE__INCLUDED_

#include "../../PltFrm/TimeTick/TimeTick.h"
#include "../../PltFrm/RgbLedStripeDigits/RgbLedStripeDigits.h"

#include "../../EvHandler/ITimeTickEvHandler.h"
#include "../../EvHandler/IRgbLedStripeDigitsEvHandler.h"
#include "../Judo.h"
#include "../../Util/Time/Time.h"

namespace Obj
{

class JudoDisplay : public ITimeTickEvHandler, public IRgbLedStripeDigitsEvHandler
{

public:
	JudoDisplay();
	virtual ~JudoDisplay();

	void setScoreDigits( const FighterColour& col,
	                     const FighterScore& score );
	void setMainTimeDigits( const Time& t );
	void setOsaekTimeDigits( const Time& t );

	virtual void onTimeTickEv(const PltFrm::TimeTick::TimeTickInstance& inst);
	virtual void onRgbLedStripeDigitsEv( const PltFrm::RgbLedStripeDigits::RgbLedStripeDigitsEv& ev );


	enum {
	    nrOfScoreDigits = nrOfFighterColours*3,
	    nrOfMainTimeDigits = 3,
	    nrOfOsaekTimeDigits = 2,
	    nrOfDigits =  nrOfScoreDigits + nrOfMainTimeDigits + nrOfOsaekTimeDigits
	};

private:

	enum JudoDisplayState
	{
	    idle,
	    refreshing
	};

    PltFrm::TimeTick mTimeTick;
    PltFrm::RgbLedStripe mLedStripe;
    PltFrm::RgbLedStripeDigits digit;

    JudoDisplayState mState;

    int scoreDigit[nrOfScoreDigits];
    int mainTimeDigit[nrOfMainTimeDigits];
    int osaekTimeDigit[nrOfOsaekTimeDigits];
};

} /* namespace Obj */

#endif // !defined(EA_62DD92B3_88E0_4928_B206_640A0A112CAE__INCLUDED_)
