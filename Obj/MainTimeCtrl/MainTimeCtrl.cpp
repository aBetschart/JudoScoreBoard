///////////////////////////////////////////////////////////
//  MainTimeCtrl.cpp
//  Implementation of the Class MainTimeCtrl
//  Created on:      29-Nov-2017 14:33:28
//  Original author: Aaron
///////////////////////////////////////////////////////////

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "MainTimeCtrl.h"

#include "../FightCtrl/FightCtrl.h"
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------

//--------------------------------------------------------------

namespace Obj
{

//--------------------------------------------------------------
MainTimeCtrl::MainTimeCtrl( JudoDisplay* displ, FightCtrl* fightCtrl ):
  mMainTime( displ ), mState( stateStopCountDown ),
  startBtn( PltFrm::Btn::startBtn ),
  stopBtn( PltFrm::Btn::stopBtn ),
  timeRunLed( PltFrm::Led::timeLed ),
  mBtnDebounce( PltFrm::TimeTick::timeBtnTick ),
  mFightCtrl( fightCtrl )
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
        evHandler[i] = 0;

    mMainTime.setCountDir( Obj::MainTime::down );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
MainTimeCtrl::~MainTimeCtrl()
{
    mMainTime.stop();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void MainTimeCtrl::process(const MainTimeCtrlEv& ev)
{
    switch( ev )
    {
    case evStart:
        if( mState == stateStopCountDown )
        {
            mState = stateCountDown;
            mMainTime.start();
        }
        else if( mState == stateStopCountUp )
        {
            mState = stateCountUp;
            mMainTime.start();
        }
        break;

    case evStop:
        if( mState == stateCountDown )
        {
            mState = stateStopCountDown;
            mMainTime.stop();
        }
        else if( mState == stateCountUp )
        {
            mState = stateStopCountUp;
            mMainTime.stop();
        }
        break;

    case evTimeIsOver:
        if( mState == stateCountDown )
        {
            if( !mFightCtrl->equalScore() )
            {
                mState = stateStopCountUp;
                mMainTime.stop();
                mMainTime.reset();
                mMainTime.setCountDir( Obj::MainTime::up );
            }
            else
            {
                mState = stateStopCountDown;
                mMainTime.stop();
                mMainTime.reset();
            }
        }
        break;

    case evGoldenScore:
        if( mState == stateStopCountDown )
        {
            mState = stateStopCountUp;
            mMainTime.setCountDir( Obj::MainTime::up );
        }
        break;
    default:
        break;
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool MainTimeCtrl::isRunning()
{
    return( (mState == stateCountUp) ||
            (mState == stateCountDown));
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void MainTimeCtrl::onMainTimeEv( const Obj::MainTime::MainTimeEv& ev )
{
    if( ev == MainTime::evTimeIsOver )
    {
        this->process( evTimeIsOver );
    }
}
//--------------------------------------------------------------

} // namespace Obj
