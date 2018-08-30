/**
 * name: aaron
 * date: 30.08.18
 */

#include "gtest/gtest.h"

#include "Hal/Spi/Spi.h"

class SpiTest: public ::testing::Test
{

};

TEST_F( SpiTest, failingTest ) {
	Hal::Spi::SpiInit init =
	{
			.inst 		= Hal::Spi::spi0,
			.type 		= Hal::Spi::master,
			.direction 	= Hal::Spi::transmit,
			.cpsvdr 	= 2, // clock prescaler 1
			.scr 		= 3,// clock prescaler 2
			.enaFss 	= false, // low during transmission
			.spo 		= false, // clock polarity
			.sph 		= false, // clock phase
			.dataSize 	= 16, // dataSize = [4, 5, ..., 16]
			.enaIr 		= false // enable interrupt or not
	};

	Hal::Spi testedSpi( init );
}
