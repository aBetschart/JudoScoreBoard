///////////////////////////////////////////////////////////
//  OsaekTimeCtrl.cpp
//  Implementation of the Class OsaekTimeCtrl
//  Created on:      29-Nov-2017 14:35:09
//  Original author: Aaron
///////////////////////////////////////////////////////////

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "OsaekTimeCtrl.h"

#include "../FightCtrl/FightCtrl.h"

#include "../../EvHandler/IOsaekCtrlEvHandler.h"
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------

//--------------------------------------------------------------

namespace Obj
{
//--------------------------------------------------------------
OsaekTimeCtrl::OsaekTimeCtrl( JudoDisplay* displ, FightCtrl* fightCtrl ):
        osaekBlBtn( PltFrm::Btn::osaekBlBtn ),
        osaekWhBtn( PltFrm::Btn::osaekWhBtn ),
        mOsaekTime( displ ), mState( stateStop ),
        mBtnDeb( PltFrm::TimeTick::osaekTimeTick ),
        mFightCtrl( fightCtrl )
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
        evHandler[i] = 0;

    osaekBlBtn.registerOnEv( this );
    osaekWhBtn.registerOnEv( this );

    mBtnDeb.registerBtn( &osaekBlBtn );
    mBtnDeb.registerBtn( &osaekWhBtn );

    osaekBlBtn.enable();
    osaekWhBtn.enable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
OsaekTimeCtrl::~OsaekTimeCtrl()
{
    osaekBlBtn.disable();
    osaekWhBtn.disable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void OsaekTimeCtrl::process(const OsaekCtrlEv& ev)
{
    switch( ev )
    {
    case evStartBl:
        if( mState == stateStop )
        {
            if( mFightCtrl->timeIsRunning() )
            {
                mState = stateOsaekBl;
                mOsaekTime.reset();
                mOsaekTime.start();
            }
        }
        break;
    case evStartWh:
        if( mState == stateStop )
        {
            if( mFightCtrl->timeIsRunning() )
            {
                mState = stateOsaekWh;
                mOsaekTime.reset();
                mOsaekTime.start();
            }
        }
        break;
    case evStopBl:
        if( mState == stateOsaekBl )
        {
            mState = stateStop;
            mOsaekTime.stop();
            mOsaekTime.reset();
            notify( evOsaekOver );
        }
        break;
    case evStopWh:
        if ( mState == stateOsaekWh )
        {
            mState = stateStop;
            mOsaekTime.stop();
            mOsaekTime.reset();
            notify( evOsaekOver );
        }
        break;
    case evIpponTime:
        if( mState == stateOsaekBl )
        {
            mState = stateStop;
            mOsaekTime.stop();
            notify( evIpponTimeBl );
        }
        else if( mState == stateOsaekWh )
        {
            mState = stateStop;
            mOsaekTime.stop();
            notify( evIpponTimeWh );
        }
        notify( evOsaekOver );
        break;
    case evWazariTime:
        if( mState == stateOsaekBl )
        {
            notify( evWazariTimeBl );
        }
        else if( mState == stateOsaekWh )
        {
            notify( evWazariTimeWh );
        }
        break;
    default:
        break;
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool OsaekTimeCtrl::osaekomiRunning()
{
    return (mState != stateStop);
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void OsaekTimeCtrl::registerOnEv(IOsaekCtrlEvHandler* handler)
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
//--------------------------------------------------------------


//--------------------------------------------------------------
void OsaekTimeCtrl::onOsaekTimeEv( const Obj::OsaekTime::OsaekTimeEv& ev )
{
    switch( ev )
    {
    case OsaekTime::evWazariTime:
        this->process( evWazariTime );
        break;
    case OsaekTime::evIpponTime:
        this->process( evIpponTime );
        break;
    default:
        break;
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void OsaekTimeCtrl::onButtonEv(const PltFrm::Btn::BtnInstance& btn)
{
    switch( btn )
    {
    case PltFrm::Btn::osaekBlBtn:
        if( this->osaekomiRunning() )
            this->process( evStopBl );
        else
            this->process( evStartBl );
        break;
    case PltFrm::Btn::osaekWhBtn:
        if( this->osaekomiRunning() )
            this->process( evStopWh );
        else
            this->process( evStartWh );
        break;
    default:
        break;
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void OsaekTimeCtrl::notify(const OsaekCtrlEv& ev)
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] != 0 )
        {
            evHandler[i]->onOsaekTimeCtrlEv( ev );
        }
    }
}
//--------------------------------------------------------------

} // namespace Obj
