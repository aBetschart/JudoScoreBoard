/*
 * Timer.cpp
 *
 *  Created on: 18.10.2017
 *      Author: aaron
 */

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "Timer.h"

#include <new>
#include <cassert>

#include "../../EvHandler/ITimerEvHandler.h"
#include "../Nvic/Nvic.h"
#include "../Rcgc/Rcgc.h"
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- interrupt call back wrapper functions
//--------------------------------------------------------------
extern "C"
{
void timer0ACallBackWr(void)
{
    Hal::Timer::timer0ACallBack();
}

void timer0BCallBackWr(void)
{
    Hal::Timer::timer0BCallBack();
}

void timer1ACallBackWr(void)
{
    Hal::Timer::timer1ACallBack();
}

void timer1BCallBackWr(void)
{
    Hal::Timer::timer1BCallBack();
}

void timer2ACallBackWr(void)
{
    Hal::Timer::timer2ACallBack();
}

void timer2BCallBackWr(void)
{
    Hal::Timer::timer2BCallBack();
}

void timer3ACallBackWr(void)
{
    Hal::Timer::timer3ACallBack();
}

void timer3BCallBackWr(void)
{
    Hal::Timer::timer3BCallBack();
}

void timer4ACallBackWr(void)
{
    Hal::Timer::timer4ACallBack();
}

void timer4BCallBackWr(void)
{
    Hal::Timer::timer4BCallBack();
}

void timer5ACallBackWr(void)
{
    Hal::Timer::timer5ACallBack();
}

void timer5BCallBackWr(void)
{
    Hal::Timer::timer5BCallBack();
}

void timer6ACallBackWr(void)
{
    Hal::Timer::timer6ACallBack();
}

void timer6BCallBackWr(void)
{
    Hal::Timer::timer6BCallBack();
}

void timer7ACallBackWr(void)
{
    Hal::Timer::timer7ACallBack();
}

void timer7BCallBackWr(void)
{
    Hal::Timer::timer7BCallBack();
}
} /* extern C */
//--------------------------------------------------------------

namespace Hal
{

//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------
static const uint32_t timerBaseAddr[Hal::Timer::nrOfTimers] =
{
 0x40030000, 0x40031000, 0x40032000, 0x40033000,
 0x40034000, 0x40035000, 0x400E0000, 0x400E1000
};

static const uint16_t irBitMask[Hal::Timer::nrOfTimerEv] =
{
 0x0001, 0x0002, 0x0008, 0x0010, 0x0020, 0x0040,
};

static const Hal::Nvic::irInstance irInst[Timer::nrOfTimers][Timer::nrOfSubTimers] =
{
 {Nvic::timer0A, Nvic::timer0B},
 {Nvic::timer1A, Nvic::timer1B},
 {Nvic::timer2A, Nvic::timer2B},
 {Nvic::timer3A, Nvic::timer3B},
 {Nvic::timer4A, Nvic::timer4B},
 {Nvic::timer5A, Nvic::timer5B},
 {Nvic::timer6A, Nvic::timer6B},
 {Nvic::timer7A, Nvic::timer7B},
};

Timer* Timer::instance[Timer::nrOfTimers][Timer::nrOfSubTimers] = {0};
//--------------------------------------------------------------


//--------------------------------------------------------------
Timer::Timer( const TimerInit& init ): mInst( init.inst ),
        mSubInst( init.subInst ), mMode( init.mode ),
        isConcat( init.concat )
{
    // checkout instance and register
    if( mMode == rtc )
    {
        // timer must have size 32
        assert( instance[mInst][0] == 0 &&
                instance[mInst][1] == 0 );
        instance[mInst][0] = this;
        instance[mInst][1] = this;
    }
    else if( (mMode == oneShot) || (mMode == periodic) )
    {
        // timer possibly of size 32 bit (concatenated)
        if( isConcat )
        {
            assert( instance[mInst][0] == 0 &&
                    instance[mInst][1] == 0 );
            instance[mInst][0] = this;
            instance[mInst][1] = this;
        }
        else
        {
            assert( instance[mInst][mSubInst] == 0 );
            instance[mInst][mSubInst] = this;
        }
    }
    else
    { // timer can't be concatenated
        isConcat = false;
        assert( instance[mInst][mSubInst] == 0 );
        instance[mInst][mSubInst] = this;
    }

    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
        evHandler[i] = 0;

    Rcgc::enaTimerModule( mInst );
    ctrlReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x00C )) Register::HwRegister<uint16_t>;

    // initialization of the timer
    this->stop();

    this->setMode( mMode );
    this->setCountDir( init.dir );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
Timer::~Timer()
{
    if( isConcat )
    {
        instance[mInst][0] = 0;
        instance[mInst][1] = 0;
    }
    else
    {
        instance[mInst][mSubInst] = 0;
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool Timer::isConcatenated() const
{
    return( isConcat );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
Timer::TimerCountDir Timer::getCountDirection()
{
    Register::HwRegister<uint32_t>* modeReg;

    if( isConcat || (mSubInst == subTimerA))
        modeReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x004 )) Register::HwRegister<uint32_t>;
    else // subtimer B
        modeReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x008 )) Register::HwRegister<uint32_t>;

    if( modeReg->checkBits(0x10) )
        return up;
    else
        return down;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::start()
{
    if( isConcat )
    {
        ctrlReg->setBits(0x0001);
    }
    else if ( mSubInst == subTimerA )
    {
        ctrlReg->setBits(0x0001);
    }
    else // subTimerB
    {
        ctrlReg->setBits(0x0100);
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::stop()
{
    if( isConcat )
    {
        ctrlReg->clearBits(0x0101);
    }
    else if ( mSubInst == subTimerA )
    {
        ctrlReg->clearBits(0x0001);
    }
    else // subTimerB
    {
        ctrlReg->clearBits(0x0100);
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::clearCountVal()
{
    Register::HwRegister<uint32_t>* timerValReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x050 )) Register::HwRegister<uint32_t>;

    timerValReg->insert( 0x00000000 );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::setMode(const TimerMode& mode)
{
    Register::HwRegister<uint32_t>* modeReg;
    Register::HwRegister<uint8_t>* cfgReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x000 )) Register::HwRegister<uint8_t>;

    if( isConcat || (mSubInst == subTimerA))
        modeReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x004 )) Register::HwRegister<uint32_t>;
    else // subtimer B
        modeReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x008 )) Register::HwRegister<uint32_t>;

    // clearing the mode bits
    modeReg->clearBits(0x0003);
    cfgReg->clearBits(0x07);

    switch( mode )
    {
    case oneShot:
        if( !isConcat )
            cfgReg->setBits(0x0004);

        modeReg->setBits(0x1);
        break;
    case periodic:
        if( !isConcat )
            cfgReg->setBits(0x0004);

        modeReg->setBits(0x2);
        break;
    case rtc:
        cfgReg->setBits(0x01);
        break;
    case edgeCount:
        cfgReg->setBits(0x04);
        modeReg->setBits(0x0003);   // select capture mode
        modeReg->clearBits(0x0004); // select edge-count-mode
        break;
    case edgeTime:
        cfgReg->setBits(0x04);
        modeReg->setBits(0x0003); // select capture mode
        modeReg->setBits(0x0004); // select edge-time-mode
        break;
    case pwm:
        cfgReg->setBits(0x04);

        modeReg->setBits(0x08);   // set AMS bit
        modeReg->clearBits(0x04); // select edge-count-mode
        modeReg->clearBits(0x03); // clear mode bits
        modeReg->setBits(0x02);   // select periodic-timer-mode
        break;
    default:
        break;
    }

    mMode = mode;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::setCountDir(const TimerCountDir& dir)
{
    Register::HwRegister<uint32_t>* modeReg;

    if( isConcat || (mSubInst == subTimerA))
        modeReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x004 )) Register::HwRegister<uint32_t>;
    else // subtimer B
        modeReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x008 )) Register::HwRegister<uint32_t>;

    if( dir == up )
    {
        if( mMode == pwm ) // no up counting in PWM-mode
            return;

        modeReg->setBits(0x10);
    }
    else // down
    {
        if( mMode == rtc ) // no down counting in RTC-mode
            return;

        modeReg->clearBits(0x10);
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::setIntervalBorder(const uint32_t& border)
{
    Register::HwRegister<uint32_t>* interReg;
    Register::HwRegister<uint8_t>*  prescReg;

    if( isConcat )
    {
        interReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x028 )) Register::HwRegister<uint32_t>;
        interReg->insert(border);
    }
    else if( mSubInst == subTimerA )
    {
        interReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x028 )) Register::HwRegister<uint32_t>;
        prescReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x038 )) Register::HwRegister<uint8_t>;

        if( this->getCountDirection() == up )
        {
            uint8_t  prescValue = (border >> 16);
            uint16_t interValue = (border & 0x0000FFFF);
            prescReg->insert(prescValue);
            interReg->insert(interValue);
        }
        else // down
        {
            uint8_t  prescValue = (border & 0x000000FF);
            uint16_t interValue = (border >> 8);
            prescReg->insert(prescValue);
            interReg->insert(interValue);
        }
    }
    else // subTimer B
    {
        interReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x02C )) Register::HwRegister<uint32_t>;
        prescReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x03C )) Register::HwRegister<uint8_t>;

        if( this->getCountDirection() == up )
        {
            uint8_t  prescValue = (border >> 16);
            uint16_t interValue = (border & 0x0000FFFF);
            prescReg->insert(prescValue);
            interReg->insert(interValue);
        }
        else // down
        {
            uint8_t  prescValue = (border & 0x000000FF);
            uint16_t interValue = (border >> 8);
            prescReg->insert(prescValue);
            interReg->insert(interValue);
        }
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::setMatchValue(const uint32_t& val)
{
    Register::HwRegister<uint32_t>* matchReg;
    Register::HwRegister<uint8_t>*  prescReg;

    if( isConcat )
    {
        matchReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x030 )) Register::HwRegister<uint32_t>;
        matchReg->insert(val);
    }
    else if( mSubInst == subTimerA )
    {
        matchReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x030 )) Register::HwRegister<uint32_t>;
        prescReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x040 )) Register::HwRegister<uint8_t>;

        if( this->getCountDirection() == up )
        {
            uint8_t  prescValue = (val >> 16);
            uint16_t interValue = (val & 0x0000FFFF);
            prescReg->insert(prescValue);
            matchReg->insert(interValue);
        }
        else // down
        {
            uint8_t  prescValue = (val & 0x000000FF);
            uint16_t interValue = (val >> 8);
            prescReg->insert(prescValue);
            matchReg->insert(interValue);
        }
    }
    else // subTimer B
    {
        matchReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x034 )) Register::HwRegister<uint32_t>;
        prescReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x044 )) Register::HwRegister<uint8_t>;

        if( this->getCountDirection() == up )
        {
            uint8_t  prescValue = (val >> 16);
            uint16_t interValue = (val & 0x0000FFFF);
            prescReg->insert(prescValue);
            matchReg->insert(interValue);
        }
        else // down
        {
            uint8_t  prescValue = (val & 0x000000FF);
            uint16_t interValue = (val >> 8);
            prescReg->insert(prescValue);
            matchReg->insert(interValue);
        }
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::setCaptureEv(const TimerCaptureEv& ev)
{
    ctrlReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x00C )) Register::HwRegister<uint16_t>;

    if( isConcat || mSubInst == subTimerB )
    {
        ctrlReg->clearBits( 0x3 << 2 );
        ctrlReg->setBits( ev << 2 );
    }
    else
    {
        ctrlReg->clearBits( 0x3 << 10 );
        ctrlReg->setBits( ev << 10 );
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::setModuleIr(const bool& on)
{
    if( this->isConcatenated() || (mSubInst == subTimerA ))
    {
        if( on )
        {
            Register::HwRegister<uint16_t>* irClearReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x024 )) Register::HwRegister<uint16_t>;
            irClearReg->clearBits( 0x3F3F );
            Nvic::enableIr( irInst[mInst][subTimerA] );
        }
        else
            Nvic::disableIr( irInst[mInst][subTimerA] );
    }
    else
    {
        if( on )
            Nvic::enableIr( irInst[mInst][subTimerB] );
        else
            Nvic::disableIr( irInst[mInst][subTimerB] );
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::enableIr(const TimerEv& ev)
{
    Register::HwRegister<uint16_t>* irMaskReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x018 )) Register::HwRegister<uint16_t>;

    if( isConcat || (mSubInst == subTimerA) )
    {
        irMaskReg->setBits( irBitMask[ev] );
    }
    else // Timer B
    {
        irMaskReg->setBits( (irBitMask[ev] << 8) );
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::disableIr(const TimerEv& ev)
{
    Register::HwRegister<uint16_t>* irMaskReg = new (reinterpret_cast<void*>( timerBaseAddr[mInst] + 0x018 )) Register::HwRegister<uint16_t>;

    if( isConcat || (mSubInst == subTimerB) )
    {
        irMaskReg->clearBits( irBitMask[ev] );
    }
    else // Timer B
    {
        irMaskReg->clearBits( (irBitMask[ev] << 8) );
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::registerOnEv(ITimerEvHandler* handler)
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
bool Timer::operator ==(const Timer& timer)
{
    if( this->isConcatenated() )
    {
        if( timer.isConcatenated() )
        {
            return( timer.instance == this->instance) ;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if( !(timer.isConcatenated()) )
        {
            return( (timer.mInst == this->mInst) &&
                    (timer.mSubInst == this->mSubInst) );
        }
        else
        {
            return false;
        }
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::notify(const TimerEv& ev)
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] != 0 )
            evHandler[i]->onTimerEv(*this, ev);
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Timer::checkIrStatus( const TimerInstance& inst,
                           const SubTimerInstance& subInst  )
{
    Register::HwRegister<uint16_t>* irStatReg = new (reinterpret_cast<void*>( timerBaseAddr[inst] + 0x020 )) Register::HwRegister<uint16_t>;
    Register::HwRegister<uint16_t>* irClearReg = new (reinterpret_cast<void*>( timerBaseAddr[inst] + 0x024 )) Register::HwRegister<uint16_t>;

    if( instance[inst][subInst]->isConcatenated() ||
            (subInst == subTimerA) )
    {
        for( int i = 0 ; i < nrOfTimerEv ; ++i )
        {
            if( irStatReg->checkBits( irBitMask[i] ) )
            {
                if( instance[inst][subInst] != 0 )
                    instance[inst][subTimerA]->notify( static_cast<TimerEv>(i) );

                irClearReg->setBits(irBitMask[i]);
            }
        }
    }
    else
    {
        for( int i = 0 ; i < nrOfTimerEv ; ++i )
        {
            if( irStatReg->checkBits( (irBitMask[i] << 8) ) )
            {
                instance[inst][subTimerB]->notify( static_cast<TimerEv>(i) );
                irClearReg->setBits( (irBitMask[i] << 8) );
            }
        }
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- interrupt call back functions
//--------------------------------------------------------------
void Timer::timer0ACallBack()
{
    checkIrStatus( timer0, subTimerA );
}

void Timer::timer0BCallBack()
{
    checkIrStatus( timer0, subTimerB );
}

void Timer::timer1ACallBack()
{
    checkIrStatus( timer1, subTimerA );
}

void Timer::timer1BCallBack()
{
    checkIrStatus( timer1, subTimerB );
}

void Timer::timer2ACallBack()
{
    checkIrStatus( timer2, subTimerA );
}

void Timer::timer2BCallBack()
{
    checkIrStatus( timer2, subTimerB );
}

void Timer::timer3ACallBack()
{
    checkIrStatus( timer3, subTimerA );
}

void Timer::timer3BCallBack()
{
    checkIrStatus( timer3, subTimerB );
}

void Timer::timer4ACallBack()
{
    checkIrStatus( timer4, subTimerA );
}

void Timer::timer4BCallBack()
{
    checkIrStatus( timer4, subTimerB );
}

void Timer::timer5ACallBack()
{
    checkIrStatus( timer5, subTimerA );
}

void Timer::timer5BCallBack()
{
    checkIrStatus( timer5, subTimerB );
}

void Timer::timer6ACallBack()
{
    checkIrStatus( timer6, subTimerA );
}

void Timer::timer6BCallBack()
{
    checkIrStatus( timer6, subTimerB );
}

void Timer::timer7ACallBack()
{
    checkIrStatus( timer7, subTimerA );
}

void Timer::timer7BCallBack()
{
    checkIrStatus( timer7, subTimerB );
}
//--------------------------------------------------------------
} /* namespace Hal */
