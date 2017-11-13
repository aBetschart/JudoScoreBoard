/*
 * Rcgc.h
 *
 *  Created on: 17.10.2017
 *      Author: aaron
 */

#ifndef HAL_RCGC_RCGC_H_
#define HAL_RCGC_RCGC_H_

#include "../Gpio/Gpio.h"
#include "../Spi/Spi.h"
#include "../Timer/Timer.h"
namespace Hal
{

class Rcgc
{
public:
    static void enaGpioPort( const Hal::Gpio::GpioPort& p );
    static void enaSsiModule( const Hal::Spi::SpiInstance& inst );
    static void enaTimerModule( const Hal::Timer::TimerInstance& inst );
};

} /* namespace Hal */

#endif /* HAL_RCGC_RCGC_H_ */
