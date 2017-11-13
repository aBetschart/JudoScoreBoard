///////////////////////////////////////////////////////////
//  Led.h
//  Implementation of the Class Led
//  Created on:      11-Nov-2017 15:48:09
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_7C778C6B_ECB9_441d_9CE0_91CDF8468214__INCLUDED_)
#define EA_7C778C6B_ECB9_441d_9CE0_91CDF8468214__INCLUDED_

#include "../../Hal/Gpio/Gpio.h"

namespace PltFrm
{

class Led
{

public:

    enum LedInstance
    {
        led0,
        led1,
        nrOfLeds
    };
	Led( const LedInstance& inst );
	virtual ~Led();


	void turnOff();
	void turnOn();
	void toggle();
	bool isTurnedOn() const;

private:
	static Led* instance[nrOfLeds];

	Hal::Gpio mGpio;
	LedInstance mInst;
};

} /* namespace PltFrm */

#endif // !defined(EA_7C778C6B_ECB9_441d_9CE0_91CDF8468214__INCLUDED_)
