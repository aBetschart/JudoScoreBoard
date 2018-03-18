///////////////////////////////////////////////////////////
//  IRgbLedStripeEvHandler.h
//  Implementation of the Class IRgbLedStripeEvHandler
//  Created on:      23-Nov-2017 17:07:39
//  Original author: aaron
///////////////////////////////////////////////////////////

#if !defined(EA_BC6B366D_D46B_44f5_82AE_7A3165A88E98__INCLUDED_)
#define EA_BC6B366D_D46B_44f5_82AE_7A3165A88E98__INCLUDED_

#include "../PltFrm/RgbLedStripe/RgbLedStripe.h"

class IRgbLedStripeEvHandler
{

public:
	virtual void onRgbLedStripeEv( PltFrm::RgbLedStripe::RgbLedStripeInstance inst,
	                               PltFrm::RgbLedStripe::RgbLedStripeEv ev) = 0;

};
#endif // !defined(EA_BC6B366D_D46B_44f5_82AE_7A3165A88E98__INCLUDED_)
