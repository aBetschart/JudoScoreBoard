/*
 * HwRegister.h
 *
 *  Created on: 30.07.2017
 *      Author: Aaron
 */

#ifndef HAL_HWREGISTER_HWREGISTER_H_
#define HAL_HWREGISTER_HWREGISTER_H_

namespace Hal
{

template<typename T>
class HwRegister
{
public:
    void clearBits( const T& bits ){ regVal &= ~bits; }
    void setBits( const T& bits ){ regVal |= bits; }
    void insert( const T& bits ){ regVal = bits; }
    bool checkBits( const T& bits ) const{ return ( (regVal & bits ) == bits ); }
    T getVal() const { return regVal; }

private:
    ~HwRegister(){};
    volatile T regVal;
};

} /* namespace Hal */

#endif /* HAL_HWREGISTER_HWREGISTER_H_ */
