/*
 * Spi.h
 *
 *  Created on: 05.10.2017
 *      Author: aaron
 */

#ifndef HAL_SPI_SPI_H_
#define HAL_SPI_SPI_H_

#include<stdint.h>

#include "../../Register/Register.h"

class ISpiEvHandler;

namespace Hal
{

class Spi
{
public:

    enum SpiInstance
    {
        spi0, spi1,
        spi2, spi3,
        nrOfSpi
    };

    enum SpiType
    {
        master,
        slave
    };

    enum SpiDir
    {
        receive,
        transmit
    };

    /**
     * Possible interrupts, that can occur
     */
    enum SpiEv
    {
        evReceiveFifoOverrun,
        evReceiveFifoTimeOut,
        evReceivFifoServ,
        evTransmFifoServ,
        evEndOfTransmission,
        nrOfSpiEvs
    };

    /**
     * SsiClk = SysClk / ( cpsvdr * ( 1 + scr ) )
     * cpsvdr = [2, 4, 6, ..., 254]
     * scr    = [1:256]
     *
     * dataSize = [4, 5, ..., 16]
     */
    struct SpiInit
    {
        SpiInstance     inst;
        SpiType         type;
        SpiDir          direction;
        uint8_t         cpsvdr; // clock prescaler 1
        uint8_t         scr; // clock prescaler 2
        bool            enaFss; // low during transmission
        bool            spo; // clock polarity
        bool            sph; // clock phase
        uint8_t         dataSize; // dataSize = [4, 5, ..., 16]
        bool            enaIr; // enable interrupt or not
    };

    enum{
        nrOfEvHandlers = 5,
        fifoSize = 8
    };

    /**
     * @see     struct SpiInit
     */
    Spi( const SpiInit& init );
    ~Spi();

    /**
     * @brief   Inserts a message into the transmit FIFO.
     *          To start the transmission, you have to enable
     *          the module.
     */
    void insertMsg( const uint16_t& msg );

    /**
     * @brief   Returns the first received message that was not
     *          read already
     */
    uint16_t getMsg();

    /**
     * @brief   Enables or disables the interface
     */
    void setModule( const bool& on );

    /**
     * @brief   Enables or disables the interrupts of the interface
     */
    void setModuleIr( const bool& on );

    /**
     * @brief   Enables interrupt of a specific ev
     * @param   ev  Interruptev, that is enabled
     * @see     enum SpiEv
     */
    void enableIr( const SpiEv& ev );

    /**
     * @brief   Disables interrupt of a specific ev
     * @param   ev  Interruptev, that is disabled
     * @see     enum SpiEv
     */
    void disableIr( const SpiEv& ev );

    /**
     * @brief   Registers ev handler on enabled interrupt
     * @param   handler Evhandler that wants to be registered
     */
    void registerOnEv( ISpiEvHandler* handler );

    /**
     * Interrupt callbacks
     */
    static void ssi0CallBack();
    static void ssi1CallBack();
    static void ssi2CallBack();
    static void ssi3CallBack();

protected:

    /**
     * @brief   Notifies all registered handlers, that an interrupt ev occured
     * @see     enum SpiEv
     */
    void notify( const SpiEv& ev );

    /**
     * @brief   checks interrupt status of the interface with
     *          instance inst and calls the notify function
     *          with the occured events
     */
    static void checkIrStatus( const SpiInstance& inst );

private:
    Spi( const Spi& spi ){} /**< no copies of Spi objects are allowed */

    Register::RegisterInterface<uint16_t>* dataReg;
    Register::RegisterInterface<uint16_t>* ctrlReg1;

    SpiInstance mInst;
    SpiDir      mDir;

    ISpiEvHandler* evHandler[nrOfEvHandlers];

    static Spi* instance[nrOfSpi];
};

} /* namespace Hal */

#endif /* HAL_SPI_SPI_H_ */
