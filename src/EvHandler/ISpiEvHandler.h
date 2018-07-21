/*
 * IQssiEvHandler.h
 *
 *  Created on: 05.10.2017
 *      Author: aaron
 */

#ifndef TARGETCONFIGS_IQSSIEVENTHANDLER_H_
#define TARGETCONFIGS_IQSSIEVENTHANDLER_H_

#include "../Hal/Spi/Spi.h"

class ISpiEvHandler
{
public:
    virtual void onSpiEv( const Hal::Spi::SpiInstance& inst, const Hal::Spi::SpiEv& ev) = 0;
};

#endif /* TARGETCONFIGS_IQSSIEVENTHANDLER_H_ */
