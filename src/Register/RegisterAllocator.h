/*
 * RegisterActivityLogger.h
 *
 *  Created on: 31.07.2018
 *      Author: aaron
 */

#ifndef REGISTERALLOCATOR_H_
#define REGISTERALLOCATOR_H_

#include <stdint.h>
#include <new>
#include <string>

#include "Register.h"
#include "HwRegister.h"
#include "SoftwareRegister.h"
#include "AddressAndNameParsing/AddressAndNameParsing.h"

namespace Register
{

template<typename Type>
class RegisterAllocator
{
public:
    static RegisterInterface<Type>* allocateRegister(const int& address);

private:
    static std::string getRegisterNameFromAddress(const int& address);
};

template<typename Type>
inline RegisterInterface<Type>* RegisterAllocator<Type>::allocateRegister(const int& address)
{
#ifdef TESTING
    return new SoftwareRegister<Type>( getRegisterNameFromAddress( address ) );
#else

#endif
}

template<typename Type>
inline std::string RegisterAllocator<Type>::getRegisterNameFromAddress(
		const int& address)
{
	return AddressAndNameParsing::getNameFromAddress( address );
}

} //Register

#endif /* REGISTERALLOCATOR_H_ */
