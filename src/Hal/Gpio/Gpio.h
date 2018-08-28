/*
 * Gpio.h
 *
 *  Created on: 29.07.2017
 *      Author: Aaron
 */

#ifndef HAL_GPIO_GPIO_H_
#define HAL_GPIO_GPIO_H_

#include <stdint.h>

#include "../../Register/HwRegister.h"

class IGpioEvHandler;

namespace Hal
{

class Gpio
{
public:

    /**
     * Direction setting of the GPIO
     */
    enum GpioDir
    {
        dirOutput,
        dirInput
    };

    enum GpioPort
    {
        portA, portB, portC,
        portD, portE, portF,
        portG, portH, portJ,
        portK, portL, portM,
        portN, portP, portQ,
        nrOfGpioPorts
    };

    enum GpioPinNr
    {
        pin0, pin1, pin2, pin3,
        pin4, pin5, pin6, pin7,
        nrOfPins
    };

    /**
     * Output configuration on the GPIO
     */
    enum GpioPinResistor
    {
        noResistor,
        pullUpRes,
        pullDownRes
    };

    /**
     * Ev that triggers interrupt on GPIO input
     */
    enum GpioIrEv
    {
        evRisingEdge,
        evFallingEdge,
        evBothEdge
    };

    /**
     * Special function or peripherial that has control of GPIO
     */
    enum GpioFunc
    {
        specialFunc,
        analogFunc = 0x00,
        dig1 , dig2 , dig3,
        dig4 , dig5 , dig6,
        dig7 , dig8 , dig9,
        dig10, dig11, dig12,
        dig13, dig14, dig15,
        noSpecFunc
    };

    /**
     * Drive strength of GPIO output
     */
    enum GpioDrStr
    {
        ma2 = 0x500,
        ma4 = 0x504,
        ma8 = 0x508
    };

    /**
     * Initialization-structure that is needed to instantiate a GPIO
     */
    struct GpioInit
    {
        GpioDir         dir;        // port direction
        GpioPort        port;       // gpio Port
        GpioPinNr       nr;         // pin number
        GpioPinResistor outCfg;     // configuration of output
        bool            openDrain;  // true: open drain activated
    };

    enum{ nrOfEvHandlers = 2 };

    /**
     * @param   init initialization struct with all necessary information
     * @see     struct GpioInit
     */
    Gpio( const GpioInit& init );

    /**
     * @brief   Special constructor for modules (interfaces like SPI etc.)
     * @param   f   Special function setting
     * @see     enum GpioFunc
     */
    Gpio( const GpioPort& p, const GpioPinNr& pin, const GpioFunc& f );

    ~Gpio();

    /**
     * @brief   Sets the controlling element (peripherie) of the GPIO
     * @param   f The function or peripherie, that controls the GPIO
     * @see     enum GpioFunc
     */
    void setSpecialFunc( const GpioFunc& f );

    /**
     * @brief   Sets the drive strength of the GPIO
     * @param   str  The activated drive strength
     * @see     enum GpioDrStr
     */
    void setDriveStrength( const GpioDrStr& str );

    /**
     * @brief   Sets the output configuration (works just on outputs)
     * @param   res  Configuration of the output
     * @see     enum GpioPinResistor
     */
    void setPinCfg( const GpioPinResistor& res, const bool& openDrain );

    /**
     * @brief   Enables or disables interrupts
     * @param   on  true enables, false disables interrupt
     */
    void setInterrupt( const bool& on );

    /**
     * @brief   Sets the ev, that triggers the interrupt
     * @param   ev Triggering ev, that is enabled
     * @see     enum GpioIrEv
     */
    void configIr( const GpioIrEv& ev );

    /**
     * @brief   Registers ev handler on enabled interrupt
     * @param   handler Evhandler that wants to be registered
     */
    void registerOnEv( IGpioEvHandler* const handler );

    /**
     * @brief   returns whether the GPIO is high or low
     * @return  true if high, false if low
     */
    bool isSet() const;

    /**
     * @brief   Sets the level of the GPIO output
     * @param   on  true -> high, false -> low
     */
    void set( const bool& on );

    /**
     * @brief   Comparing operator ==
     * @param   gpio    Compared GPIO
     * @return  true if same GPIO, false if not
     */
    bool operator==( const Gpio& gpio );

    static void gpioCallBackPortA();
    static void gpioCallBackPortB();
    static void gpioCallBackPortC();
    static void gpioCallBackPortD();
    static void gpioCallBackPortE();
    static void gpioCallBackPortF();
    static void gpioCallBackPortG();
    static void gpioCallBackPortH();
    static void gpioCallBackPortJ();
    static void gpioCallBackPortK();
    static void gpioCallBackPortL();
    static void gpioCallBackPortM();
    static void gpioCallBackPortN();
    static void gpioCallBackPortP();
    static void gpioCallBackPortQ();

protected:

    /**
     * @brief   Notifies all registered handlers, that an interrupt ev occured
     */
    void notify();

    /**
     * @brief   checks interrupt status of port p, and calls the notify function
     *          of the pins, on which an interrupt occured
     * @param   p   The inspected port
     */
    static void checkIrStatus( const GpioPort& p );

private:
    Gpio( const Gpio& gpio ){} /**< no copies of gpio's are allowed */

    bool inp; /**< true if Gpio is an input, false if output */
    uint8_t mBit;
    GpioPort mPort; /**< port, on which the gpio lays */

    Register::HwRegister<uint8_t>*  dataReg;
    Register::HwRegister<uint8_t>*  irMaskReg;

    IGpioEvHandler* evHandler[nrOfEvHandlers];

    static Gpio* instance[nrOfGpioPorts][nrOfPins];
};

} /* namespace Hal */

#endif /* HAL_GPIO_GPIO_H_ */
