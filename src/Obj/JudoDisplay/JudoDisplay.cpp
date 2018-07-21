///////////////////////////////////////////////////////////
//  JudoDisplay.cpp
//  Implementation of the Class JudoDisplay
//  Created on:      15-Nov-2017 11:22:11
//  Original author: Aaron
///////////////////////////////////////////////////////////

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "JudoDisplay.h"

#include "../../PltFrm/RgbLedStripe/RgbLedStripe.h"
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------
static const PltFrm::TimeTick::TimeTickInstance ttInst = PltFrm::TimeTick::displayTick;

static const PltFrm::RgbLedStripe::RgbLedStripeInstance ledStripeInst = PltFrm::RgbLedStripe::displayStripe;

static const PltFrm::RgbLedStripe::LedColor brghtCol[3] =
{
     {.r = 20, .g =  0, .b =  0},
     {.r =  0, .g = 20, .b =  0},
     {.r =  0, .g =  0, .b = 20}
};
//--------------------------------------------------------------

namespace Obj
{
//--------------------------------------------------------------
JudoDisplay::JudoDisplay():
        mTimeTick( ttInst ), mState( idle ), mLedStripe( ledStripeInst ), digit( &mLedStripe )
{
    for( int i = 0 ; i < nrOfScoreDigits ; ++i )
        scoreDigit[i] = 0;

    for( int i = 0 ; i < nrOfMainTimeDigits ; ++i )
        mainTimeDigit[i] = 0;

    for( int i = 0 ; i < nrOfOsaekTimeDigits ; ++i )
        osaekTimeDigit[i] = 0;

    mTimeTick.registerOnEv( this );
    digit.registerOnEv( this );

    mTimeTick.enable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
JudoDisplay::~JudoDisplay()
{
    mTimeTick.disable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void JudoDisplay::setScoreDigits(const FighterColour& col,
                                 const FighterScore& score)
{
    int shiftIndex = nrOfScoreDigits/2;

    scoreDigit[0 + shiftIndex*col] = score.shido;

    if( score.wazari )
        scoreDigit[1 + shiftIndex*col] = 1;
    else
        scoreDigit[1 + shiftIndex*col] = 0;

    if( score.ippon )
        scoreDigit[2 + shiftIndex*col] = 1;
    else
        scoreDigit[2 + shiftIndex*col] = 0;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void JudoDisplay::setMainTimeDigits(const Time& t)
{
    mainTimeDigit[0] = t.getLowerSec();
    mainTimeDigit[1] = t.getUpperSec();
    mainTimeDigit[2] = t.getMin();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void JudoDisplay::setOsaekTimeDigits(const Time& t)
{
    osaekTimeDigit[0] = t.getLowerSec();
    osaekTimeDigit[1] = t.getUpperSec();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void JudoDisplay::onTimeTickEv(const PltFrm::TimeTick::TimeTickInstance& inst)
{
    if( inst == ttInst )
    {
        if( mState == idle )
        {
            mState = refreshing;

            // shift score digits
            digit.setDigit(0, scoreDigit[2], brghtCol[0]);
            digit.setDigit(1, scoreDigit[1], brghtCol[0]);
            digit.setDigit(2, scoreDigit[0], brghtCol[0]);

            digit.setDigit(3, scoreDigit[5], brghtCol[0]);
            digit.setDigit(4, scoreDigit[4], brghtCol[0]);
            digit.setDigit(5, scoreDigit[3], brghtCol[0]);

            // set main time digits
            digit.setDigit(6, mainTimeDigit[2], brghtCol[1]);
            digit.setDigit(7, mainTimeDigit[1], brghtCol[1]);
            digit.setDigit(8, mainTimeDigit[0], brghtCol[1]);

            // set osaekomi time digits
            digit.setDigit(9, osaekTimeDigit[1], brghtCol[2]);
            digit.setDigit(10, osaekTimeDigit[0], brghtCol[2]);

            digit.actualizeDigits();
        }
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void JudoDisplay::onRgbLedStripeDigitsEv( const PltFrm::RgbLedStripeDigits::RgbLedStripeDigitsEv& ev )
{
    if( ev == PltFrm::RgbLedStripeDigits::evDigitsActualized )
    {
        mState = idle;
    }
}
//--------------------------------------------------------------

} /* namespace Obj */
