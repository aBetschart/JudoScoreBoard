///////////////////////////////////////////////////////////
//  FightCtrl.cpp
//  Implementation of the Class FightCtrl
//  Created on:      29-Nov-2017 14:31:27
//  Original author: Aaron
///////////////////////////////////////////////////////////

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "FightCtrl.h"
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------

//--------------------------------------------------------------

namespace Obj
{

//--------------------------------------------------------------
FightCtrl::FightCtrl():
    mOsaekTimeCtrl( &displ, this ),
    mScoreCtrl( this, &mOsaekTimeCtrl, &displ ),
    mMainTimeCtrl( &displ, this ),
    mState( stateNormal )
{

    mMainTimeCtrl.registerOnEv( this );
    mOsaekTimeCtrl.registerOnEv( this );
    mScoreCtrl.registerOnEv( this );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
FightCtrl::~FightCtrl()
{

}
//--------------------------------------------------------------


//--------------------------------------------------------------
void FightCtrl::process(const FightCtrlEv& ev)
{

    switch( ev )
    {
    case evOsaekOver:
        if( mState == stateWaitForOsaekomi )
        {
            if( equalScore() )
            {
                mState = stateGoldenScore;
                mMainTimeCtrl.process( MainTimeCtrl::evGoldenScore );
            }
            else
            {
                mState = stateTimeIsOver;
            }
        }
        break;

    case evTimeIsOver:
        if( mState == stateNormal )
        {
            if( osaekomiIsRunning() )
            {
                mState = stateWaitForOsaekomi;
            }
            else if( equalScore() )
            {
                mState = stateGoldenScore;
                mMainTimeCtrl.process( MainTimeCtrl::evGoldenScore );
            }
            else // !equalScore && !osaekomiRunning
            {
                mState = stateTimeIsOver;
            }
        }
        break;

    case evWinnerFound:
        if( mState == stateNormal )
        {
            mState = stateWinnerFound;
            mMainTimeCtrl.process( MainTimeCtrl::evStop );
        }
        else if( mState == stateGoldenScore )
        {
            mState = stateGoldenScoreEnd;
            mMainTimeCtrl.process( MainTimeCtrl::evStop );
        }
        break;

    case evWinnerCanceled:
        if( mState == stateWinnerFound )
        {
            mState = stateNormal;
        }
        else if( mState == stateGoldenScoreEnd )
        {
            mState = stateGoldenScore;
        }
        else if( mState == stateTimeIsOver )
        {
            if( equalScore() )
            {
                mState = stateGoldenScore;
                mMainTimeCtrl.process( MainTimeCtrl::evGoldenScore );
            }
        }
        break;

    default:
        break;
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool FightCtrl::goldenScore()
{
    return( (mState == stateGoldenScore) ||
            (mState == stateGoldenScoreEnd) );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool FightCtrl::timeIsRunning()
{
    return mMainTimeCtrl.isRunning();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool FightCtrl::osaekomiIsRunning()
{
    return mOsaekTimeCtrl.osaekomiRunning();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool FightCtrl::equalScore()
{
    return mScoreCtrl.equalScore();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool FightCtrl::hasWinner()
{
    return mScoreCtrl.winnerFound();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void FightCtrl::onOsaekTimeCtrlEv(Obj::OsaekTimeCtrl::OsaekCtrlEv ev)
{
    if( ev == OsaekTimeCtrl::evOsaekOver )
        this->process( evOsaekOver );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void FightCtrl::onMainTimeCtrlEv(const Obj::MainTimeCtrl::MainTimeCtrlEv& ev)
{
    if( ev == MainTimeCtrl::evTimeIsOver )
        this->process( evTimeIsOver );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void FightCtrl::onScoreCtrlEv(const Obj::ScoreCtrl::ScoreCtrlEv& ev)
{
    if( ev == ScoreCtrl::evWinnerFound )
        this->process( evWinnerFound );
    else if( ev == ScoreCtrl::evWinnerCanceled )
        this->process( evWinnerCanceled );
}
//--------------------------------------------------------------
}// namespace Obj
