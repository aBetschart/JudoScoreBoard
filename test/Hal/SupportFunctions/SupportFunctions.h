/**
 * author: Aaron
 * date: 30.08.18
 */

#ifndef HALTESTSUPPORTFUNCTIONS_H_
#define HALTESTSUPPORTFUNCTIONS_H_

int getRegisterValueFromAddress( const int& registerAddress );
void checkSetBitsInValue( const int& value, const int& bits );
void checkNotSetBitsInValue( const int& value, const int& bits );

#endif //HALTESTSUPPORTFUNCTIONS_H_
