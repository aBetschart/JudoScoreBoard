/*
 * Time.h
 *
 *  Created on: 15.11.2017
 *      Author: aaron
 */

#ifndef UTIL_TIME_TIME_H_
#define UTIL_TIME_TIME_H_

class Time
{
public:
    Time( const int& pHour = 0, const int& pMin = 0, const int& pSec = 0 );

    void decSec();
    void incSec();
    void decMin();
    void incMin();
    void decHour();
    void incHour();

    int getSec() const;
    int getOnesOfSec() const;
    int getTensOfSec() const;
    int getMin() const;
    int getOnesOfMin() const;
    int getTensOfMin() const;
    int getHour() const;

    bool isZero() const;

    void reset( const int& pHour = 0, const int& pMin = 0, const int& pSec = 0 );

private:
    int sec;
    int min;
    int hour;

    int getAbsoluteValue( const int& value );
    void initializeTimeAttributes(const int& pSec, const int& pMin,
                                  const int& pHour);
};

#endif /* UTIL_TIME_TIME_H_ */
