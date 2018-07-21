///////////////////////////////////////////////////////////
//  BtnDebounce.cpp
//  Implementation of the Class BtnDebounce
//  Created on:      13-Nov-2017 11:04:32
//  Original author: Aaron
///////////////////////////////////////////////////////////

#include "BtnDebounce.h"

namespace PltFrm
{
//--------------------------------------------------------------
BtnDebounce::BtnDebounce(
        const PltFrm::TimeTick::TimeTickInstance& inst):
                mTimeTick( inst )
{
    for( int i = 0 ; i < nrOfBtns ; ++i )
            mBtn[i] = 0;

    mTimeTick.disable();
    mTimeTick.registerOnEv( this );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
BtnDebounce::~BtnDebounce()
{
    for( int i = 0 ; i < nrOfBtns ; ++i )
        if( mBtn[i] != 0 )
            mBtn[i]->enable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void PltFrm::BtnDebounce::registerBtn(PltFrm::Btn* btn)
{
    for( int i = 0 ; i < nrOfBtns ; ++i )
    {
        if( mBtn[i] == 0 )
        {
            mBtn[i] = btn;
            mBtn[i]->registerOnEv( this );
            break;
        }
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void BtnDebounce::onButtonEv( const PltFrm::Btn::BtnInstance& btn )
{
    for( int i = 0 ; i < nrOfBtns ; ++i )
    {
        if( mBtn[i] != 0 )
            mBtn[i]->disable();
    }

    mTimeTick.enable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void BtnDebounce::onTimeTickEv( const PltFrm::TimeTick::TimeTickInstance& inst )
{
    if( mTimeTick.getInstance() == inst )
    {
        mTimeTick.disable();

        for( int i = 0 ; i < nrOfBtns ; ++i )
        {
            if( mBtn[i] != 0 )
                mBtn[i]->enable();
        }
    }
}
//--------------------------------------------------------------

} /* namespace PltFrm*/
