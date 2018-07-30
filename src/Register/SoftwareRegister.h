/*
 * HwRegister.h
 *
 *  Created on: 30.07.2017
 *      Author: Aaron
 */

#ifndef HAL_SOFTWAREREGISTER_HWREGISTER_H_
#define HAL_SOFTWAREREGISTER_HWREGISTER_H_

#include <string>

#include "Register.h"

template<typename T>
class SoftwareRegister: public Register<T>
{
public:
	SoftwareRegister( const std::string& registerName ): name( registerName )
	{

	}

	virtual void clearBits( const T& bits ){
		regVal &= ~bits;
	}

	virtual void setBits( const T& bits ){
		regVal |= bits;
	}

	virtual void insert( const T& bits ){
		regVal = bits;
	}

	virtual bool checkBits( const T& bits ) const
	{ return ( (regVal & bits ) == bits );
	}

	virtual T getVal() const
	{
		return regVal;
	}

    virtual ~SoftwareRegister(){}


private:
    T regVal;
    std::string name;
};

#endif /* HAL_SOFTWAREREGISTER_H_ */
