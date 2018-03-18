/*
 * TestClass3.h
 *
 *  Created on: 24.12.2017
 *      Author: Aaron
 */

#ifndef TESTCLASS3_H_
#define TESTCLASS3_H_

#include <stdint.h>

#include "PltFrm/RgbLedStripe/RgbLedStripe.h"
#include "PltFrm/TimeTick/TimeTick.h"

#include "EvHandler/IRgbLedStripeEvHandler.h"
#include "EvHandler/ITimeTickEvHandler.h"
#include "EvHandler/IBtnEvHandler.h"

class TestClass3: IRgbLedStripeEvHandler, ITimeTickEvHandler, IBtnEvHandler
{
public:


    enum
    {
        brghtnVal = 25,
        brghtnStep = 0x1
    };

    enum ColorState
    {
        red,
        green,
        blue
    };

    TestClass3(): ledStr( PltFrm::RgbLedStripe::displayStripe ),
    mTimeTick( PltFrm::TimeTick::mainTimeTick ), n1(0), n2(1), state( red ),
    started( false), mBtn( PltFrm::Btn::ipponBlBtn )
    {
        for( int i = 1 ; i < PltFrm::RgbLedStripe::nrOfLeds ; ++i )
        {
            val[i].r = 0;
            val[i].g = 0;
            val[i].b = 0;
        }

        val[0].r  = brghtnVal;
        val[0].g  = 0;
        val[0].b  = 0;

        ledStr.registerOnEv( this );
        mTimeTick.registerOnEv( this );

        ledStr.setShiftVal(val, sizeof(val)/sizeof(val[0]));
        ledStr.shiftIn();

        mBtn.registerOnEv( this );
        mBtn.enable();
    }

    virtual void onButtonEv( const PltFrm::Btn::BtnInstance& btn )
    {
        if( !started )
        {
            started = true;
            mTimeTick.enable();
        }
    }

    void onRgbLedStripeEv( PltFrm::RgbLedStripe::RgbLedStripeInstance inst,
                                       PltFrm::RgbLedStripe::RgbLedStripeEv ev)
    {
        if( (inst == PltFrm::RgbLedStripe::displayStripe) &&
            (ev == PltFrm::RgbLedStripe::evShiftComplete ) )
        {
            mTimeTick.enable();
        }
    }

    virtual void onTimeTickEv( const PltFrm::TimeTick::TimeTickInstance& inst )
    {
        mTimeTick.disable();

        switch( state )
        {
        case red:
            val[n1].r -= brghtnStep;
            val[n1].g += brghtnStep;
            if( val[n1].r == 0 )
            {
                state = green;
                val[n1].g = brghtnVal;
            }
            break;
        case green:
            val[n1].g -= brghtnStep;
            val[n1].b += brghtnStep;
            if( val[n1].g == 0 )
            {
                state = blue;
            }
            break;
        case blue:
            val[n1].b -= brghtnStep;
            val[n2].r += brghtnStep;
            if( val[n1].b == 0 )
            {
                state = red;
                n1 = n2;
                n2 = (n2+1) % PltFrm::RgbLedStripe::nrOfLeds;
            }
            break;
        default:
            break;
        }

        ledStr.setShiftVal( val , sizeof(val)/sizeof(val[0]) );
        ledStr.shiftIn();
    }

private:
    bool started;
    int n1;
    int n2;

    ColorState state;

    PltFrm::RgbLedStripe::LedColor val[PltFrm::RgbLedStripe::nrOfLeds];

    PltFrm::RgbLedStripe ledStr;
    PltFrm::TimeTick mTimeTick;
    PltFrm::Btn mBtn;
};




#endif /* TESTCLASS3_H_ */
