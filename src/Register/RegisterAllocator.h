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

#define TESTING

namespace Register
{

template<typename Type>
class RegisterAllocator
{
public:
    static RegisterInterface<Type>* allocateRegister(const int& address);
};

template<typename Type>
inline RegisterInterface<Type>* RegisterAllocator<Type>::allocateRegister(const int& address)
{
#ifdef TESTING
	std::string registerName = AddressAndNameParsing::getNameFromAddress( address );
	return new SoftwareRegister<Type>( registerName );
#else
	return new (reinterpret_cast<void*>( address )) Register::HwRegister<Type>;
#endif
}

} //Register

#endif /* REGISTERALLOCATOR_H_ */
