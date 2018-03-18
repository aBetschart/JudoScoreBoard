///////////////////////////////////////////////////////////
//  MainTime.cpp
//  Implementation of the Class MainTime
//  Created on:      27-Nov-2017 15:10:08
//  Original author: Aaron
///////////////////////////////////////////////////////////

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "MainTime.h"

#include "../../EvHandler/IMainTimeEvHandler.h"
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------
static const PltFrm::TimeTick::TimeTickInstance mTickInst = PltFrm::TimeTick::mainTimeTick;
//--------------------------------------------------------------

namespace Obj
{
//--------------------------------------------------------------
MainTime::MainTime( JudoDisplay* displ ):
        mTimeTick( mTickInst ), mDir( down ),
        mDispl( displ ), Time( secInit, minInit )
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
        evHandler[i] = 0;

    mTimeTick.disable();

    mDispl->setMainTimeDigits( *this );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
MainTime::~MainTime()
{
    mTimeTick.disable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void MainTime::start()
{
    mTimeTick.enable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void MainTime::stop()
{
    mTimeTick.disable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Obj::MainTime::setCountDir(const MainTimeCountDir& dir)
{
    mDir = dir;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void MainTime::onTimeTickEv(const PltFrm::TimeTick::TimeTickInstance& inst)
{
    if( mTickInst == inst )
    {
        if( mDir == down )
        {
            this->decSec();

            if( this->isZero() )
            {
                this->notify( evTimeIsOver );
            }
        }
        else // up
        {
            this->incSec();
        }
    }
    mDispl->setMainTimeDigits( *this );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void MainTime::regsiterOnEv(IMainTimeEvHandler* handler)
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
void MainTime::notify(const MainTimeEv& ev)
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] != 0 )
            evHandler[i]->onMainTimeEv( ev );
    }
}
//--------------------------------------------------------------

} /* namespace Obj */
