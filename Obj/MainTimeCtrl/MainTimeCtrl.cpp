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
    mMainTime.regsiterOnEv( this );

    startBtn.registerOnEv( this );
    stopBtn.registerOnEv( this );

    startBtn.enable();
    stopBtn.enable();
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
        if( !mFightCtrl->hasWinner() )
        {
            if( mState == stateStopCountDown )
            {
                mState = stateCountDown;
                timeRunLed.turnOn();
                mMainTime.start();
            }
            else if( mState == stateStopCountUp )
            {
                mState = stateCountUp;
                timeRunLed.turnOn();
                mMainTime.start();
            }
        }
        break;
    case evStop:
        if( !mFightCtrl->osaekomiIsRunning() )
        {
            if( mState == stateCountDown )
            {
                mState = stateStopCountDown;
                timeRunLed.turnOff();
                mMainTime.stop();
            }
            else if( mState == stateCountUp )
            {
                mState = stateStopCountUp;
                timeRunLed.turnOff();
                mMainTime.stop();
            }
        }
        break;
    case evTimeIsOver:
        if( mState == stateCountDown )
        {
            if( mFightCtrl->equalScore() )
            {
                mState = stateStopCountUp;
                mMainTime.stop();
                mMainTime.reset();
                mMainTime.setCountDir( Obj::MainTime::up );
                timeRunLed.turnOff();
            }
            else
            {
                mState = stateStopCountDown;
                mMainTime.stop();
                mMainTime.reset();
                timeRunLed.turnOff();
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


//--------------------------------------------------------------
void MainTimeCtrl::registerOnEv(IMainTimeCtrlEvHandler* handler)
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
void MainTimeCtrl::onButtonEv( const PltFrm::Btn::BtnInstance& btn )
{
    switch( btn )
    {
    case PltFrm::Btn::startBtn:
        this->process( evStart );
        break;
    case PltFrm::Btn::stopBtn:
        this->process( evStop );
        break;

    default:
        break;
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void MainTimeCtrl::notify(const MainTimeCtrlEv& ev)
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] != 0 )
            evHandler[i]->onMainTimeCtrlEv( ev );
    }
}
//--------------------------------------------------------------
} // namespace Obj
