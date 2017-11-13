/*
 * Timer.h
 *
 *  Created on: 18.10.2017
 *      Author: aaron
 */

#ifndef HAL_TIMER_TIMER_H_
#define HAL_TIMER_TIMER_H_

#include <stdint.h>

#include "../HwRegister/HwRegister.h"


class ITimerEvHandler;

namespace Hal
{

class Timer
{
public:

    /**
     * Number of the used timer
     */
    enum TimerInstance
    {
        timer0, timer1, timer2, timer3,
        timer4, timer5, timer6, timer7,
        nrOfTimers
    };

    /**
     * 16 bit timer A or B
     */
    enum SubTimerInstance
    {
        subTimerA, subTimerB,
        nrOfSubTimers
    };

    /**
     * Mode of the timer
     */
    enum TimerMode
    {
        oneShot,
        periodic,
        rtc,
        edgeCount,
        edgeTime,
        pwm
    };

    /**
     * Count direction of the timer
     */
    enum TimerCountDir
    {
        up,
        down
    };

    /**
     * Selects the trigger ev for edge-count-
     * or edge-time-mode
     */
    enum TimerCaptureEv
    {
        risingEdge,
        fallingEdge,
        bothEdge
    };

    /**
     * Possible interrupt evs
     */
    enum TimerEv
    {
        evTimeOut,
        evCaptureMatch,
        evCaptureEv,
        evRtc,
        evMatch,
        evDmaDone,
        nrOfTimerEv
    };

    /**
     * Structure used for timer initialization
     */
    struct TimerInit
    {
        TimerInstance       inst;
        SubTimerInstance    subInst;
        bool                concat;
        TimerMode           mode;
        TimerCountDir       dir;
    };

    /**
     * Number of possible eventhandlers
     */
    enum { nrOfEvHandlers = 5 };

    /**
     * @brief   Constructor
     * @param   init initialization struct with all necessary information
     * @return  none
     * @see     struct TimerInit
     */
    Timer( const TimerInit& init );

    /**
     * @brief   Destructor
     * @param   none
     * @return  none
     */
    virtual ~Timer();

    /**
     * @brief   Returns whether the timer is  of size 32 bit
     *          (concatenated) or not
     * @param   none
     * @return  true:  timer is concatenated (32 bit)
     *          false: Timer isn't concatenated (16 bit)
     */
    bool isConcatenated() const;

    TimerCountDir getCountDirection();

    void start();
    void stop();
    void clearCountVal();

    void setMode( const TimerMode& mode );
    void setCountDir( const TimerCountDir& dir );
    
	void setIntervalBorder( const uint32_t& border );
    void setMatchValue( const uint32_t& val );
	
	void setCaptureEv( const TimerCaptureEv& ev );
	
	void setModuleIr( const bool& on );
    void enableIr( const TimerEv& ev );
    void disableIr( const TimerEv& ev );

    void registerOnEv( ITimerEvHandler* handler );

    /**
     * @brief   Comparing operator ==
     * @param   timer    Compared Timer
     * @return  true if same Timer, false if not
     */
    bool operator==( const Timer& timer );

    static void timer0ACallBack();
    static void timer0BCallBack();

    static void timer1ACallBack();
    static void timer1BCallBack();

    static void timer2ACallBack();
    static void timer2BCallBack();

    static void timer3ACallBack();
    static void timer3BCallBack();

    static void timer4ACallBack();
    static void timer4BCallBack();

    static void timer5ACallBack();
    static void timer5BCallBack();

    static void timer6ACallBack();
    static void timer6BCallBack();

    static void timer7ACallBack();
    static void timer7BCallBack();

protected:
    void notify( const TimerEv& ev );
    static void checkIrStatus( const TimerInstance& inst,
                               const SubTimerInstance& subInst );

private:
    bool isConcat;
    TimerInstance       mInst;
    SubTimerInstance    mSubInst;
    TimerMode           mMode;

    HwRegister<uint16_t>* ctrlReg;

    ITimerEvHandler* evHandler[nrOfEvHandlers];

    static Timer* instance[nrOfTimers][nrOfSubTimers];
};

} /* namespace Hal */

#endif /* HAL_TIMER_TIMER_H_ */
