/*
 * TestClass2.h
 *
 *  Created on: 04.12.2017
 *      Author: aaron
 */

#ifndef TESTCLASS2_H_
#define TESTCLASS2_H_

#include "Hal/Spi/Spi.h"

#include "PltFrm/Btn/Btn.h"
#include "PltFrm/BtnDebounce/BtnDebounce.h"
#include "PltFrm/TimeTick/TimeTick.h"

#include "EvHandler/IBtnEvHandler.h"
#include "EvHandler/ISpiEvHandler.h"
#include "EvHandler/ITimeTickEvHandler.h"

enum
{
    nrOfLed = 17,
    brghtnVal = 0x05
};


Hal::Spi::SpiInit spiInit =
{
     Hal::Spi::spi3,
     Hal::Spi::master,
     Hal::Spi::transmit,
     2,
     4,
     false,
     false,
     false,
     8,
     false
};

PltFrm::Btn::BtnInstance btnInstance = PltFrm::Btn::ipponBlBtn;

class TestClass2: public ISpiEvHandler, public IBtnEvHandler, public ITimeTickEvHandler
{
public:
    TestClass2(): mSpi( spiInit ), mBtn( btnInstance ),
                  debouncer( PltFrm::TimeTick::displayTick ),
                  mTimeTick( PltFrm::TimeTick::ledStripeTick ), n( 0 )
    {
        for( int i = 0 ; i < nrOfLed*3 ; ++i )
            msg[i] = 0;

        debouncer.registerBtn( &mBtn );
        mSpi.enableIr( Hal::Spi::evEndOfTransmission );

        mSpi.registerOnEv( this );

        mBtn.registerOnEv( this );

        mTimeTick.registerOnEv( this );

        mTimeTick.disable();
        mSpi.setModuleIr( true );
        mBtn.enable();
    }

    void shiftVal()
    {
        for( int i = 0 ; i < ( (nrOfLed-1)*3 ) ; ++i )
        {
            msg[i] = msg[i + 3];
        }

        msg[nrOfLed*3 - 1] = brghtnVal;
        msg[nrOfLed*3 - 2] = brghtnVal;
        msg[nrOfLed*3 - 3] = brghtnVal;
    }

    virtual void onSpiEv( const Hal::Spi::SpiInstance& inst, const Hal::Spi::SpiEv& ev)
    {
        if( ev == Hal::Spi::evEndOfTransmission )
        {
            if( n < (nrOfLed*3 - 1) )
            {
                mTimeTick.enable();
            }
            else
            {
                n = 0;
            }
        }
    }

    virtual void onButtonEv( const PltFrm::Btn::BtnInstance& btn )
    {
        if( btn == btnInstance )
        {
            mTimeTick.enable();
            this->shiftVal();
        }
    }

    virtual void onTimeTickEv( const PltFrm::TimeTick::TimeTickInstance& inst )
    {
        for( int i = 0 ; i < Hal::Spi::fifoSize ; ++i )
        {
            mSpi.insertMsg( msg[n] );
            n++;
        }

        mSpi.setModule( true );
        mTimeTick.disable();
    }


private:
    Hal::Spi mSpi;
    PltFrm::Btn mBtn;
    PltFrm::TimeTick mTimeTick;
    PltFrm::BtnDebounce debouncer;

    int n;
    int msg[nrOfLed*3];
};

#endif /* TESTCLASS2_H_ */
