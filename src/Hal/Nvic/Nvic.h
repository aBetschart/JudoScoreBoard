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
    enum InterruptInstance
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
        gpioPortM = 72,
        gpioPortN,
        gpioPortP = 76,
        gpioPortQ = 84,
        timer6A = 98,
        timer6B,
        timer7A,
        timer7B
    };

    static void enableIr( const InterruptInstance& nr );
    static void disableIr( const InterruptInstance& nr );
};


} /* namespace Hal */

#endif /* HAL_NVIC_NVIC_H_ */
