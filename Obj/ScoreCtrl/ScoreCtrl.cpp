///////////////////////////////////////////////////////////
//  ScoreCtrl.cpp
//  Implementation of the Class ScoreCtrl
//  Created on:      29-Nov-2017 14:33:14
//  Original author: Aaron
///////////////////////////////////////////////////////////

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "ScoreCtrl.h"

#include "../FightCtrl/FightCtrl.h"

#include "../../EvHandler/IScoreCtrlEvHandler.h"
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------

//--------------------------------------------------------------

namespace Obj
{

//--------------------------------------------------------------
ScoreCtrl::ScoreCtrl(FightCtrl* fightCtrl, OsaekTimeCtrl* osaekCtrl, JudoDisplay* displ):
  mScore( displ, osaekCtrl ), winnerLed( PltFrm::Led::winnerLed ),
  mState( stateNoWinner )
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
        evHandler[i] = 0;

    mScore.registerOnEv( this );

    winnerLed.turnOff();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
ScoreCtrl::~ScoreCtrl()
{
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void ScoreCtrl::process(const ScoreCtrlEv& ev)
{
    switch( ev )
    {
    case evIppon:
        if( mState == stateNoWinner )
        {
            mState = stateWinnerFound;
            notify( evWinnerFound );
            winnerLed.turnOn();
        }
        break;
    case evIpponDel:
        if( mState == stateWinnerFound )
        {
            if( mFightCtrl->goldenScore() )
            {
                if( equalScore() )
                {
                    mState = stateNoWinner;
                    notify( evWinnerCanceled );
                    winnerLed.turnOff();
                }
            }
            else
            {
                mState = stateNoWinner;
                notify( evWinnerCanceled );
                winnerLed.turnOff();
            }
        }
        break;
    case evDisqual:
        if( mState == stateNoWinner )
        {
            mState = stateWinnerFound;
            winnerLed.turnOn();
        }
        break;
    case evDisqualDel:
        if( mState == stateWinnerFound )
        {
            if( mFightCtrl->goldenScore() )
            {
                if( equalScore() )
                {
                    mState = stateNoWinner;
                    notify( evWinnerCanceled );
                    winnerLed.turnOff();
                }
            }
            else
            {
                mState = stateNoWinner;
                notify( evWinnerCanceled );
                winnerLed.turnOff();
            }
        }
        break;
    case evEqualScore:
        if( mFightCtrl->goldenScore() &&
            (mState == stateWinnerFound) )
        {
            mState = stateNoWinner;
            notify( evWinnerCanceled );
            winnerLed.turnOff();
        }
        break;
    case evEqualScoreLost:
        if( mFightCtrl->goldenScore() &&
            (mState == stateNoWinner ) )
        {
            mState = stateWinnerFound;
            notify( evWinnerFound );
            winnerLed.turnOn();
        }
        break;
    default:
        break;
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool ScoreCtrl::equalScore()
{
	return ( mScore.equalScore() );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool ScoreCtrl::winnerFound()
{
    return ( mState == stateWinnerFound );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void ScoreCtrl::registerOnEv( IScoreCtrlEvHandler* handler )
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
void ScoreCtrl::onScoreEv( const Obj::Score::ScoreEv& ev )
{
    switch( ev )
    {
    case Score::evIppon:
        process( evIppon );
        break;
    case Score::evIpponDel:
        process( evIpponDel );
        break;
    case Score::evDisqual:
        process( evDisqual );
        break;
    case Score::evDisqualDel:
        process( evDisqualDel );
        break;
    case Score::evEqualScore:
        process( evEqualScore );
        break;
    case Score::evEqualScoreLost:
        process( evEqualScoreLost );
        break;
    default:
        break;
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void ScoreCtrl::notify(const ScoreCtrlEv& ev)
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] != 0 )
            evHandler[i]->onScoreCtrlEv( ev );
    }
}
//--------------------------------------------------------------
}// namespace Obj
