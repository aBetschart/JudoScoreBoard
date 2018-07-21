/*
 * IRgbLedStripeDigitsEvHandler.h
 *
 *  Created on: 04.01.2018
 *      Author: aaron
 */

#ifndef EVHANDLER_IRGBLEDSTRIPEDIGITSEVHANDLER_H_
#define EVHANDLER_IRGBLEDSTRIPEDIGITSEVHANDLER_H_

#include "../PltFrm/RgbLedStripeDigits/RgbLedStripeDigits.h"

class IRgbLedStripeDigitsEvHandler
{
public:
    virtual void onRgbLedStripeDigitsEv( const PltFrm::RgbLedStripeDigits::RgbLedStripeDigitsEv& ev ) = 0;
};

#endif /* EVHANDLER_IRGBLEDSTRIPEDIGITSEVHANDLER_H_ */
