///////////////////////////////////////////////////////////
//  Btn.h
//  Implementation of the Class Btn
//  Created on:      11-Nov-2017 14:37:54
//  Original author: Aaron
///////////////////////////////////////////////////////////

#if !defined(EA_B46B9049_4150_4e96_B24B_62AA6227343F__INCLUDED_)
#define EA_B46B9049_4150_4e96_B24B_62AA6227343F__INCLUDED_

#include "../../Hal/Gpio/Gpio.h"
#include "../../EvHandler/IGpioEvHandler.h"

class IBtnEvHandler;

namespace PltFrm
{

class Btn : public IGpioEvHandler
{

public:

    enum BtnInstance
    {
        ipponBlBtn,
        wazariBlBtn,
        shidoBlBtn,
        ipponWhBtn,
        wazariWhBtn,
        shidoWhBtn,

        startBtn,
        stopBtn,

        osaekBlBtn,
        osaekWhBtn,

        nrOfBtns
    };

    enum{ nrOfEvHandlers = 2 };

    Btn( const BtnInstance& btn );
	virtual ~Btn();

	void disable();
	void enable();
	BtnInstance getInstance();
	void registerOnEv( IBtnEvHandler* handler );
	virtual void onGpioEv(const Hal::Gpio& gpio);

protected:
	void notify();

private:
	BtnInstance mInst;
	static Btn* instance[nrOfBtns];

	IBtnEvHandler* evHandler[nrOfEvHandlers];
	Hal::Gpio mGpio;
};

} /* namespace PltFrm */
#endif // !defined(EA_B46B9049_4150_4e96_B24B_62AA6227343F__INCLUDED_)
