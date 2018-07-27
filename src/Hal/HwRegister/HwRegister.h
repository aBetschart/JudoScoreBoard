/*
 * HwRegister.h
 *
 *  Created on: 30.07.2017
 *      Author: Aaron
 */

#ifndef HAL_HWREGISTER_HWREGISTER_H_
#define HAL_HWREGISTER_HWREGISTER_H_

#include "Register.h"

namespace Hal
{

template<typename T>
class HwRegister: public Register<T>
{
public:
    virtual void clearBits( const T& bits ){ regVal &= ~bits; }
    virtual void setBits( const T& bits ){ regVal |= bits; }
    virtual void insert( const T& bits ){ regVal = bits; }
    virtual bool checkBits( const T& bits ) const{ return ( (regVal & bits ) == bits ); }
    virtual T getVal() const { return regVal; }

private:
    ~HwRegister(){};
    volatile T regVal;
};

} /* namespace Hal */

#endif /* HAL_HWREGISTER_HWREGISTER_H_ */
