/**
 *
 * Date: 31.07.18
 * Author: Aaron
 */

#ifndef TM4CREGISTERNAMEMAP_H_
#define TM4CREGISTERNAMEMAP_H_

#include <string>

namespace AddressAndNameParsing
{

std::string getNameFromAddress( const int& address );
int getAddressFromName( const std::string& registerName );

} //RegisterAddressMapping

#endif // TM4CREGISTERNAMEMAP_H_
