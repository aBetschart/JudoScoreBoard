/*
 * TestClass.h
 *
 *  Created on: 11.11.2017
 *      Author: Aaron
 */

#ifndef TESTCLASS_H_
#define TESTCLASS_H_

#include "EvHandler/IBtnEvHandler.h"
#include "EvHandler/ITimeTickEvHandler.h"
#include "PltFrm/BtnDebounce/BtnDebounce.h"
#include "PltFrm/Btn/Btn.h"
#include "PltFrm/Led/Led.h"
#include "PltFrm/TimeTick/TimeTick.h"

class TestClass: public IBtnEvHandler, public ITimeTickEvHandler
{
public:
    TestClass():
        btnDeb( PltFrm::TimeTick::timeBtnTick ),
        ena( true ),
        tt( PltFrm::TimeTick::scoreBtnTick ),
        btn0( PltFrm::Btn::ipponBlBtn ),
        led0( PltFrm::Led::led0 ),
        led1( PltFrm::Led::led1 )
    {
        led0.turnOn();
        led1.turnOn();

        tt.registerOnEv(this);
        btn0.registerOnEv(this);

        tt.enable();
        btn0.enable();
    }

    virtual void onButtonEv( const PltFrm::Btn::BtnInstance& btn )
    {
        if( ena )
            tt.disable();
        else
            tt.enable();

        ena = !ena;
    }

    virtual void onTimeTickEv( const PltFrm::TimeTick::TimeTickInstance& inst )
    {
        led0.toggle();
        led1.toggle();
    }

private:
    PltFrm::BtnDebounce<1> btnDeb;
    PltFrm::TimeTick tt;
    PltFrm::Btn btn0;
    PltFrm::Led led0;
    PltFrm::Led led1;

    bool ena;
};

#endif /* TESTCLASS_H_ */
