/*
 * Clk.h
 *
 *  Created on: 10.11.2017
 *      Author: aaron
 */

#ifndef HAL_CLK_H_
#define HAL_CLK_H_

#include<stdint.h>

namespace Hal
{

class Clk
{
public:

    enum ClkSource
    {
        piosc,
        lfiosc,
        mosc,
        rtcosc,
        nrOfClkSources
    };

    /**
     *  @brief  sets the active clocksource
     */
    static void setClkSource( const ClkSource& clk );

    /**
     * @return  Active clocksource
     * @see     enum ClkSource
     */
    static ClkSource getOscClkSource();

    /**
     * @warning Just PIOSC and MOSC possible
     * @see     enum ClkSource
     */
    static void setPllClkSource( const ClkSource& clk );

    /**
     * @warning Divisor has just the size of 10 bits
     */
    static void setOscClkDivisor( const uint16_t& div );

    /**
     * @warning Divisor has just the size of 10 bits
     */
    static uint16_t getOscClkDivisor();

    /**
     * @warning Divisor has just the size of 10 bits
     */
    static void setPllClkDivisor( const uint16_t& div );

    /**
     * @warning Divisor has just the size of 10 bits
     */
    static uint16_t getPllClkDivisor();

    /**
     * @return  The active clock that supplies the PLL
     */
    static ClkSource getPllClkSource();

    /**
     * @return  clockfrequency in Hz
     */
    static uint32_t getClkFreq();

    /**
     * @param   clk Clock source, that's frequency is desired to know
     * @return  Frequency of clocksource clk
     */
    static uint32_t getRawClkFreq( const ClkSource& clk );

    /**
     * @return  true if PLL is enabled, false if disabled
     */
    static bool pllEnabled();

};

} /* namespace Hal */

#endif /* HAL_CLK_H_ */
