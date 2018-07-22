///////////////////////////////////////////////////////////
//  RgbLedStripe.cpp
//  Implementation of the Class RgbLedStripe
//  Created on:      20-Nov-2017 14:23:20
//  Original author: aaron
///////////////////////////////////////////////////////////

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "../RgbLedStripe/RgbLedStripe.h"
#include "../../EvHandler/IRgbLedStripeEvHandler.h"

#include <cassert>
#include <new>
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------
PltFrm::RgbLedStripe* PltFrm::RgbLedStripe::instance[PltFrm::RgbLedStripe::nrOfRgbLedStripes] = {0};

static const Hal::Spi::SpiInit spiInit[PltFrm::RgbLedStripe::nrOfRgbLedStripes] =
{
 {Hal::Spi::spi3, Hal::Spi::master, Hal::Spi::transmit, 2, 12, false, false, false, 8, false }
};

static const PltFrm::TimeTick::TimeTickInstance timeTickInst[PltFrm::RgbLedStripe::nrOfRgbLedStripes] =
{
 PltFrm::TimeTick::ledStripeTick
};
//--------------------------------------------------------------

namespace PltFrm
{
//--------------------------------------------------------------
RgbLedStripe::RgbLedStripe( const RgbLedStripeInstance& inst ):
        mTimeTick( timeTickInst[inst] ),
        mInst( inst ), mSpi( spiInit[inst] ),
        mState( idle )
{
    assert( instance[inst] == 0 );
    instance[inst] = this;

    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
        evHandler[i] = 0;

    mTimeTick.disable();
    mTimeTick.registerOnEv( this );

    mSpi.enableIr( Hal::Spi::evEndOfTransmission );
    mSpi.registerOnEv( this );

    mSpi.setModuleIr( false );
    mSpi.setModule( true );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
RgbLedStripe::~RgbLedStripe()
{
    instance[mInst] = 0;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void RgbLedStripe::setShiftVal( const LedColor* val, int n )
{
    int up = n;

    if( up > nrOfLeds )
        up = nrOfLeds;

    if( (mState == idle) || (mState == ready) )
    {
        // empty the stack
        while( !stack.isEmpty() )
            stack.pop();

        // fill stack with the values
        for( int i = (up-1) ; i >= 0 ; --i )
        {
            stack.push( val[i].b );
            stack.push( val[i].g );
            stack.push( val[i].r );
        }

        mState = ready;
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void RgbLedStripe::shiftIn()
{
    if( mState == ready )
    {
        int i = 0;
        mState = shifting;

        while( (i < Hal::Spi::fifoSize ) &&
               (!stack.isEmpty()) )
        {
            mSpi.insertMsg( stack.pop() );
            ++i;
        }

        mSpi.setModuleIr( true );

        mTimeTick.enable();
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool RgbLedStripe::isShifting() const
{
    return(mState == shifting);
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void RgbLedStripe::onSpiEv(const Hal::Spi::SpiInstance& inst,
                        const Hal::Spi::SpiEv& ev)
{
    if( (ev == Hal::Spi::evEndOfTransmission) &&
        (inst == spiInit[mInst].inst) )
    {
        int i = 0;

        while( (i < Hal::Spi::fifoSize) &&
               (!stack.isEmpty()) )
        {
            mSpi.insertMsg( stack.pop() );
            ++i;
        }

        if ( stack.isEmpty() && (i == 0) )
        {
            mTimeTick.enable();
        }
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void RgbLedStripe::onTimeTickEv(const PltFrm::TimeTick::TimeTickInstance& inst)
{
    if( timeTickInst[mInst] == inst )
    {
        if( mState == shifting )
        {
            mTimeTick.disable();
            mState = idle;
            notify( evShiftComplete );
        }
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void RgbLedStripe::registerOnEv(IRgbLedStripeEvHandler* handler)
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
void RgbLedStripe::notify(const RgbLedStripeEv& ev)
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] != 0 )
            evHandler[i]->onRgbLedStripeEv( mInst, ev );
    }
}
//--------------------------------------------------------------

} /* namespace PltFrm */

