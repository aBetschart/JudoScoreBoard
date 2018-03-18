///////////////////////////////////////////////////////////
//  OsaekTime.cpp
//  Implementation of the Class OsaekTime
//  Created on:      27-Nov-2017 14:35:12
//  Original author: Aaron
///////////////////////////////////////////////////////////

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "OsaekTime.h"

#include "../../EvHandler/IOsaekTimeEvHandler.h"
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------
static const PltFrm::TimeTick::TimeTickInstance mInst = PltFrm::TimeTick::osaekTimeTick;
//--------------------------------------------------------------
namespace Obj
{

//--------------------------------------------------------------
OsaekTime::OsaekTime( JudoDisplay* displ ):
 mTimeTick( mInst ), mDispl( displ )
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
        evHandler[i] = 0;

    mTimeTick.registerOnEv( this );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
OsaekTime::~OsaekTime()
{
    mTimeTick.disable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void OsaekTime::registerOnEv(IOsaekTimeEvHandler* handler)
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
void OsaekTime::onTimeTickEv(const PltFrm::TimeTick::TimeTickInstance& inst)
{
    if( inst == mInst )
    {
        this->incSec();

        switch( this->getSec() )
        {
        case wazariTime:
            this->notify( evWazariTime );
            break;

        case ipponTime:
            this->notify( evIpponTime );
            this->stop();
            break;

        default:
            break;
        }
    }

    mDispl->setOsaekTimeDigits( *this );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void OsaekTime::start()
{
    mTimeTick.enable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void OsaekTime::stop()
{
    mTimeTick.disable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void OsaekTime::notify(const OsaekTimeEv& ev)
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] != 0 )
            evHandler[i]->onOsaekTimeEv( ev );
    }
}
//--------------------------------------------------------------

} /* namespace Obj */
