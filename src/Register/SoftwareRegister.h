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
#include "RegisterValueReader.h"
#include "RegisterActivityLogger.h"

namespace Register
{

template<typename Type>
class SoftwareRegister: public RegisterInterface<Type>
{
public:
	SoftwareRegister( const std::string& registerName, const Type& defaultValue = 0 );
    virtual ~SoftwareRegister();
	virtual void clearBits( const Type& bits );
	virtual void setBits( const Type& bits );
	virtual void insert( const Type& bits );
	virtual bool checkBits( const Type& bits ) const;
	virtual Type getVal() const;

private:
	RegisterActivityLogger<Type> activityLogger;
	RegisterValueReader<Type> valueReader;
    Type regVal;

	void updateLog();
};

} //Register

template<typename Type>
inline Register::SoftwareRegister<Type>::SoftwareRegister( const std::string& registerName, const Type& defaultValue ):
    activityLogger( registerName, defaultValue ), valueReader( registerName )
{
	regVal = valueReader.getActualValue();
}

template<typename Type>
inline Register::SoftwareRegister<Type>::~SoftwareRegister()
{

}

template<typename Type>
void inline Register::SoftwareRegister<Type>::clearBits( const Type& bits )
{
	regVal &= ~bits;
	updateLog();
}

template<typename Type>
void inline Register::SoftwareRegister<Type>::setBits( const Type& bits )
{
	regVal |= bits;
	updateLog();
}


template<typename Type>
void inline Register::SoftwareRegister<Type>::insert( const Type& bits )
{
	regVal = bits;
	updateLog();
}


template<typename Type>
bool inline Register::SoftwareRegister<Type>::checkBits( const Type& bits ) const
{
	return( ( regVal & bits ) == bits );
}


template<typename Type>
Type inline Register::SoftwareRegister<Type>::getVal() const
{
	return regVal;
}

template<typename Type>
void Register::SoftwareRegister<Type>::updateLog()
{
	activityLogger.logRegisterModification(regVal);
}

#endif /* HAL_SOFTWAREREGISTER_H_ */
