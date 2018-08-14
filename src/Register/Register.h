/*
 * Register.h
 *
 *  Created on: 25.07.2018
 *      Author: Aaron
 */

#ifndef HAL_REGISTER_H_
#define HAL_REGISTER_H_

namespace Register
{

template<typename T>
class RegisterInterface
{
public:
    virtual void clearBits( const T& bits ) = 0;
    virtual void setBits( const T& bits ) = 0;
    virtual void insert( const T& bits ) = 0;
    virtual bool checkBits( const T& bits ) const = 0;
    virtual T getVal() const = 0;

private:
};

} //Register

#endif /* HAL_REGISTER_H_ */

