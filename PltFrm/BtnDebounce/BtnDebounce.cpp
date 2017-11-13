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
template<int nrOfBtns>
inline PltFrm::BtnDebounce<nrOfBtns>::BtnDebounce(
        const PltFrm::TimeTick::TimeTickInstance& inst)
{
    for( int i = 0 ; i < nrOfBtns ; ++i )
            mBtn[i] = 0;

        mTimeTick.disable();
        mTimeTick.registerOnEv( this );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
template<int nrOfBtns>
BtnDebounce<nrOfBtns>::~BtnDebounce()
{
    for( int i = 0 ; i < nrOfBtns ; ++i )
        if( mBtn[i] != 0 )
            mBtn[i]->enable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
template<int nrOfBtns>
inline void PltFrm::BtnDebounce<nrOfBtns>::registerBtn(PltFrm::Btn* btn)
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
template<int nrOfBtns>
void BtnDebounce<nrOfBtns>::onButtonEv( const PltFrm::Btn::BtnInstance& btn )
{
    for( int i = 0 ; i < nrOfBtns ; ++i )
        mBtn[i]->disable();

    mTimeTick.enable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
template<int nrOfBtns>
void BtnDebounce<nrOfBtns>::onTimeTickEv( const PltFrm::TimeTick::TimeTickInstance& inst )
{
    if( mTimeTick.getInstance() == inst )
    {
        mTimeTick.disable();

        for( int i = 0 ; i < nrOfBtns ; ++i )
            mBtn[i]->enable();
    }
}
//--------------------------------------------------------------

} /* namespace PltFrm*/
