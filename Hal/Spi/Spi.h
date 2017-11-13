/*
 * Spi.h
 *
 *  Created on: 05.10.2017
 *      Author: aaron
 */

#ifndef HAL_SPI_SPI_H_
#define HAL_SPI_SPI_H_

#include<stdint.h>
#include "../HwRegister/HwRegister.h"

class ISpiEvHandler;

namespace Hal
{

class Spi
{
public:

    /**
     * There are four possible SPI interfaces [spi0 ... spi3]
     */
    enum SpiInstance
    {
        spi0, spi1,
        spi2, spi3,
        nrOfSpi
    };

    /**
     * Defines whether the interface is a master or a slave
     */
    enum SpiType
    {
        master,
        slave
    };

    /**
     * Defines the direction of
     * the interface (receiver or transmitter)
     */
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
     * Initialization structure, that contains all information
     * that is used to init the SPI-interface
     *
     * SsiClk = SysClk / ( cpsvdr * ( 1 + scr ) )
     * cpsvdr = [2, 4, 6, ..., 254]
     * scr    = [1:256]
     *
     * dataSize = [3, 4, ..., 15]
     * But the actual data size is equal dataSize + 1.
     * E.g. dataSize = 3, actual data Size = 4
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
        uint8_t         dataSize; // dataSize = [3, 4, ..., 15]
        bool            enaIr; // enable interrupt or not
    };

    /**
     * Number of handlers that can be registered on interrupts
     * of one interface
     */
    enum{ nrOfEvHandlers = 5 };

    /**
     * @brief   Constructor
     * @param   init initialization struct with all necessary information
     * @return  none
     * @see     struct SpiInit
     */
    Spi( const SpiInit& init );

    /**
     * @brief   Destructor
     * @param   none
     * @return  none
     */
    ~Spi();

    /**
     * @brief   Inserts a message into the transmit FIFO.
     *          To start the transmission, you have to enable
     *          the module.
     * @param   msg     The inserted message
     * @return  none
     */
    void insertMsg( const uint16_t& msg );

    /**
     * @brief   Returns the first received message that was not
     *          read already
     * @param   none
     * @return  none
     */
    uint16_t getMsg();

    /**
     * @brief   Enables or disables the interface
     * @param   on  true:   Interface enabled,
     *              false:  Interface disabled
     * @return  none
     */
    void setModule( const bool& on );

    /**
     * @brief   Enables or disables the interrupts of the interface
     * @param   on  true:   Interrupt enabled
     *              false:  Interrupt disabled
     * @return  none
     */
    void setModuleIr( const bool& on );

    /**
     * @brief   Enables interrupt of a specific ev
     * @param   ev  Interruptev, that is enabled
     * @return  none
     * @see     enum SpiEv
     */
    void enableIr( const SpiEv& ev );

    /**
     * @brief   Disables interrupt of a specific ev
     * @param   ev  Interruptev, that is disabled
     * @return  none
     * @see     enum SpiEv
     */
    void disableIr( const SpiEv& ev );

    /**
     * @brief   Registers ev handler on enabled interrupt
     * @param   handler Evhandler that wants to be registered
     * @return  none
     */
    void registerOnEv( ISpiEvHandler* handler );

    /**
     * @brief   Interrupt callback of interface SSI0
     */
    static void ssi0CallBack();

    /**
     * @brief   Interrupt callback of interface SSI1
     */
    static void ssi1CallBack();

    /**
     * @brief   Interrupt callback of interface SSI2
     */
    static void ssi2CallBack();

    /**
     * @brief   Interrupt callback of interface SSI3
     */
    static void ssi3CallBack();

protected:

    /**
     * @brief   Notifies all registered handlers, that an interrupt ev occured
     * @param   ev  Ev that has occured
     * @return  none
     * @see     enum SpiEv
     */
    void notify( const SpiEv& ev );

    /**
     * @brief   checks interrupt status of the interface with
     *          instance inst and calls the notify function
     *          with the occured events
     * @param   inst    The inspected interface
     * @return  none
     */
    static void checkIrStatus( const SpiInstance& inst );

private:
    Spi( const Spi& spi ){} /**< no copies of Spi objects are allowed */

    /**
     * Data register for reception and transmission
     */
    HwRegister<uint16_t>* dataReg;

    /**
     * Control register that is used often (to enable/disable
     * the interface)
     */
    HwRegister<uint16_t>* ctrlReg1;

    SpiInstance mInst;  /**< Instance of the object */
    SpiDir      mDir;   /**< The direction of the interface */

    /**
     * Ev handlers (interrupt callbacks)
     */
    ISpiEvHandler* evHandler[nrOfEvHandlers];

    /**
     * All existing SPI interfaces are registered here
     */
    static Spi* instance[nrOfSpi];
};

} /* namespace Hal */

#endif /* HAL_SPI_SPI_H_ */
