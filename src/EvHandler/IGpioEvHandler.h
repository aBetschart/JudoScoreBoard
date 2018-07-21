/*
 * IGpioEventHandler.h
 *
 *  Created on: 31.08.2017
 *      Author: aaron
 */

#ifndef IGPIOEVHANDLER_H_
#define IGPIOEVHANDLER_H_

#include "../Hal/Gpio/Gpio.h"

class IGpioEvHandler
{
public:
    virtual void onGpioEv( const Hal::Gpio& gpio ) = 0;
};

#endif /* IGPIOEVHANDLER_H_ */
