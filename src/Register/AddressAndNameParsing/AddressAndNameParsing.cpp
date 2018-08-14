/**
 *
 * Date: 31.07.18
 * Author: Aaron
 */

#include <iomanip>

#include "AddressAndNameParsing.h"

enum {
	addressLength = 8
};

std::string Register::AddressAndNameParsing::getNameFromAddress( const int& address )
{
	int absoluteValue = abs( address );

	std::stringstream stream;
	stream << "0x"
		   << std::setfill( '0' )
		   << std::setw( addressLength )
		   << std::hex << absoluteValue;

	return stream.str();
}
