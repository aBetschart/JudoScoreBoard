///////////////////////////////////////////////////////////
//  Switch.h
//  Implementation of the Class Switch
//  Created on:      27-Nov-2017 22:02:12
//  Original author: aaron
///////////////////////////////////////////////////////////

#if !defined(EA_B79EA148_AA33_426f_8E9B_31000B893617__INCLUDED_)
#define EA_B79EA148_AA33_426f_8E9B_31000B893617__INCLUDED_

#include "../../Hal/Gpio/Gpio.h"


namespace PltFrm
{

class Switch
{

public:
    enum SwitchInstance
    {
        scoreSwitch,
        nrOfSwitches
    };

	Switch( const SwitchInstance& inst );
	virtual ~Switch();

	bool isSet() const;

private:
	static Switch* instance[nrOfSwitches];
	SwitchInstance mInst;

	Hal::Gpio mGpio;
};

} /* namespace PltFrm */

#endif // !defined(EA_B79EA148_AA33_426f_8E9B_31000B893617__INCLUDED_)
