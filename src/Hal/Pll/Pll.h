/*
 * Pll.h
 *
 *  Created on: 03.11.2017
 *      Author: aaron
 */

#ifndef HAL_PLL_PLL_H_
#define HAL_PLL_PLL_H_

#include <stdint.h>

namespace Hal
{

class Pll
{
public:
    static void enablePll();
    static void disablePll();

    /**
      * fvco = fin*MDIV
     *
     * fin = fxtal / (( Q+1 )( N+1 ))
     * MDIV = MINT + (MFRAC/1024)
     *
     * MFRAC should be equal to zero to avoid jitter
     */
    static void setM( const uint8_t& val );
    static uint8_t getM();
    static void setQ( const uint8_t& val );
    static uint8_t getQ();
    static void setMint( const uint16_t& val );
    static uint16_t getMint();
    static void setMfrac( const uint16_t& val );
    static uint16_t getMfrac();

    /**
     * @brief   Returns clock frequency in Hz
     * @param   none
     * @return  Clock frequency in Hz
     */
    static uint32_t getPllFreq();
};

} /* namespace Hal */

#endif /* HAL_PLL_PLL_H_ */
