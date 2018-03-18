/*
 * main.cpp
 */


#include "Obj/JudoDisplay/JudoDisplay.h"
#include "Obj/OsaekTime/OsaekTime.h"
#include "Obj/Judo.h"

int main(void)
{
    FighterScore score[2];

    score[0].ippon = true;
    score[0].wazari = 5;
    score[0].shido = 2;

    score[1].ippon = false;
    score[1].wazari = 1;
    score[1].shido = 1;

    Obj::JudoDisplay displ;
    Obj::OsaekTime osaekTime(&displ);

    displ.setScoreDigits(blue, score[0]);
    displ.setScoreDigits(white, score[1]);

    osaekTime.start();

    while(1);
}
