/*
 * RgbLedStripeDigits.cpp
 *
 *  Created on: 04.01.2018
 *      Author: aaron
 */

#include "RgbLedStripeDigits.h"

#include <stdint.h>

#include "../../EvHandler/IRgbLedStripeDigitsEvHandler.h"

static const bool ssegLut[10][7] =
{    /* 0      1      2      3      4      5      6     */
/*0*/ { true , true , true , false, true , true , true  },
/*1*/ { false, false, true , false, false, false, true  },
/*2*/ { false, true , true , true , true , true , false },
/*3*/ { false, true , true , true , false, true , true  },
/*4*/ { true , false, true , true , false, false, true  },
/*5*/ { true , true , false, true , false, true , true  },
/*6*/ { true , true , false, true , true , true , true  },
/*7*/ { false, true , true , false, false, false, true  },
/*8*/ { true , true , true , true , true , true , true  },
/*9*/ { true , true , true , true , false, true , true  }
};

namespace PltFrm
{

RgbLedStripeDigits::RgbLedStripeDigits( RgbLedStripe* ledStripe ):
mState ( stateIdle ), mLedStripe( ledStripe )
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
        evHandler[i] = 0;

    mLedStripe->registerOnEv( this );

    for( int i = 0 ; i < (nrOfDigits*7*ledsPerSegment) ; ++i )
    {
        shiftVal[i].r = 0;
        shiftVal[i].g = 0;
        shiftVal[i].b = 0;
    }

    mLedStripe->setShiftVal( shiftVal, sizeof(shiftVal)/sizeof(shiftVal[0]));
}

void RgbLedStripeDigits::setDigit( int digitIndex, int digitVal,
                                   RgbLedStripe::LedColor brghtCol )
{
    int index;

    if( digitIndex < 0 )
        digitIndex = 0;
    else if( digitIndex >= nrOfDigits )
        digitIndex = nrOfDigits - 1;

    if( digitVal < 0 )
        digitVal = 0;
    else if( digitVal > 9 )
        digitVal = 9;

    index = digitIndex*7*ledsPerSegment;

    for( int seg = 0 ; seg < 7 ; ++seg )
    {
        for( int led = 0 ; led < ledsPerSegment ; ++led )
        {
            if( ssegLut[digitVal][seg] )
                shiftVal[index] = brghtCol;
            else
            {
                shiftVal[index].r = 0;
                shiftVal[index].g = 0;
                shiftVal[index].b = 0;
            }

            index++;
        }
    }
}

void RgbLedStripeDigits::registerOnEv( IRgbLedStripeDigitsEvHandler* handler )
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] == 0 )
        {
            evHandler[i] = handler;
            break;
        }
    }
}

void RgbLedStripeDigits::onRgbLedStripeEv(
        PltFrm::RgbLedStripe::RgbLedStripeInstance inst,
        PltFrm::RgbLedStripe::RgbLedStripeEv ev)
{
    if( ev == RgbLedStripe::evShiftComplete )
    {
        if( mState == stateActualizing )
        {
            mState = stateIdle;
            this->notify( evDigitsActualized );
        }
    }
}

void RgbLedStripeDigits::actualizeDigits()
{
    if( mState == stateIdle )
    {
        mState = stateActualizing;
        mLedStripe->setShiftVal( shiftVal, sizeof(shiftVal)/sizeof(shiftVal[0]) );
        mLedStripe->shiftIn();
    }
}

void RgbLedStripeDigits::notify(const RgbLedStripeDigitsEv& ev)
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] != 0 )
            evHandler[i]->onRgbLedStripeDigitsEv( ev );
    }
}

} /* namespace PltFrm */
