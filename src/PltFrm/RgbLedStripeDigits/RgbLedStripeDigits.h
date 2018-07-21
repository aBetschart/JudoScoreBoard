/*
 * RgbLedStripeDigits.h
 *
 *  Created on: 04.01.2018
 *      Author: aaron
 */

#ifndef PLTFRM_RGBLEDSTRIPEDIGITS_RGBLEDSTRIPEDIGITS_H_
#define PLTFRM_RGBLEDSTRIPEDIGITS_RGBLEDSTRIPEDIGITS_H_

#include "../RgbLedStripe/RgbLedStripe.h"

#include "../../EvHandler/IRgbLedStripeEvHandler.h"

class IRgbLedStripeDigitsEvHandler;

namespace PltFrm
{

class RgbLedStripeDigits: public IRgbLedStripeEvHandler
{
public:

    enum RgbLedStripeDigitsEv
    {
        evDigitsActualized
    };

    RgbLedStripeDigits( RgbLedStripe* ledStripe );
    void setDigit( int digitIndex, int digitVal, RgbLedStripe::LedColor brghtCol );
    void actualizeDigits();

    void registerOnEv( IRgbLedStripeDigitsEvHandler* handler );
    virtual void onRgbLedStripeEv( PltFrm::RgbLedStripe::RgbLedStripeInstance inst,
                                   PltFrm::RgbLedStripe::RgbLedStripeEv ev);


    enum {
        nrOfEvHandlers = 1,
        nrOfDigits = 11,
        ledsPerSegment = 2
    };

protected:
    void notify( const RgbLedStripeDigitsEv& ev );

private:

    enum RgbLedStripeDigitsState
    {
        stateIdle,
        stateActualizing
    };

    RgbLedStripe* mLedStripe;
    RgbLedStripe::LedColor shiftVal[nrOfDigits*7*ledsPerSegment];

    RgbLedStripeDigitsState mState;

    IRgbLedStripeDigitsEvHandler* evHandler[nrOfEvHandlers];
};

} /* namespace PltFrm */

#endif /* PLTFRM_RGBLEDSTRIPEDIGITS_RGBLEDSTRIPEDIGITS_H_ */
