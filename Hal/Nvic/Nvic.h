/*
 * Nvic.h
 *
 *  Created on: 31.08.2017
 *      Author: aaron
 */

#ifndef HAL_NVIC_NVIC_H_
#define HAL_NVIC_NVIC_H_

namespace Hal
{

class Nvic
{
public:
    enum irInstance
    {
        gpioPortA = 0,
        gpioPortB,
        gpioPortC,
        gpioPortD,
        gpioPortE,
        ssi0 = 7,
        timer0A = 19,
        timer0B,
        timer1A,
        timer1B,
        timer2A,
        timer2B,
        gpioPortF = 30,
        gpioPortG,
        gpioPortH,
        ssi1 = 34,
        timer3A,
        timer3B,
        gpioPortJ = 51,
        gpioPortK,
        gpioPortL,
        ssi2,
        ssi3,
        timer4A = 63,
        timer4B,
        timer5A,
        timer5B,
        timer6A = 98,
        timer6B,
        timer7A,
        timer7B
    };

    static void enableIr( const irInstance& nr );
    static void disableIr( const irInstance& nr );
};


} /* namespace Hal */

#endif /* HAL_NVIC_NVIC_H_ */
