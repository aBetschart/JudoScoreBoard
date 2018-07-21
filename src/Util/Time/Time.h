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
    Time( const int& pMin = 0, const int& pSec = 0 );

    void decSec();
    void incSec();
    void decMin();
    void incMin();

    int getSec() const;
    int getLowerSec() const;
    int getUpperSec() const;
    int getMin() const;

    bool isZero() const;

    void reset( const int& pSec = 0, const int& pMin = 0 );

private:
    int sec;
    int min;
};

#endif /* UTIL_TIME_TIME_H_ */
