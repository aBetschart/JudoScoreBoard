/*
 * Judo.h
 *
 *  Created on: 13.11.2017
 *      Author: Aaron
 */

#ifndef OBJ_JUDO_H_
#define OBJ_JUDO_H_

#include<stdint.h>

enum FighterColour
{
    blue,
    white,
    nrOfFighterColours
};

struct FighterScore
{
    uint8_t     shido;  // 3 shidos means ippon for opponent
    bool        wazari; // no limitations for wazari
    bool        ippon;  // ippon means victory
};


#endif /* OBJ_JUDO_H_ */
