///////////////////////////////////////////////////////////
//  Score.cpp
//  Implementation of the Class Score
//  Created on:      27-Nov-2017 17:14:15
//  Original author: Aaron
///////////////////////////////////////////////////////////

//--------------------------------------------------------------
// -- includes
//--------------------------------------------------------------
#include "Score.h"

#include "../../EvHandler/IScoreEvHandler.h"
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- variables
//--------------------------------------------------------------

//--------------------------------------------------------------


//--------------------------------------------------------------
// -- enums
//--------------------------------------------------------------
enum Scoring
{
    shido,
    wazari,
    ippon
};
//--------------------------------------------------------------


namespace Obj
{
//--------------------------------------------------------------
Score::Score( JudoDisplay* displ, OsaekTimeCtrl* osaekCtrl ):
  mDispl( displ ), locked(false),
  scoreSw( PltFrm::Switch::scoreSwitch ),
  ipponBlBtn( PltFrm::Btn::ipponBlBtn ),
  wazariBlBtn( PltFrm::Btn::wazariBlBtn ),
  shidoBlBtn( PltFrm::Btn::shidoBlBtn ),
  ipponWhBtn( PltFrm::Btn::ipponWhBtn ),
  wazariWhBtn( PltFrm::Btn::wazariWhBtn ),
  shidoWhBtn( PltFrm::Btn::shidoWhBtn ),
  btnDeb( PltFrm::TimeTick::scoreBtnTick )
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
        evHandler[i] = 0;

    for( int i = 0 ; i < nrOfFighterColours ; ++i )
    {
        score[i].shido  = 0;
        score[i].wazari = 0;
        score[i].ippon  = false;
    }

    mDispl->setScoreDigits( blue, score[blue]);
    mDispl->setScoreDigits( white, score[white]);

    btnDeb.registerBtn( &ipponBlBtn );
    btnDeb.registerBtn( &wazariBlBtn );
    btnDeb.registerBtn( &shidoBlBtn );

    btnDeb.registerBtn( &ipponWhBtn );
    btnDeb.registerBtn( &wazariWhBtn );
    btnDeb.registerBtn( &shidoWhBtn );

    ipponBlBtn.registerOnEv( this );
    wazariBlBtn.registerOnEv( this );
    shidoBlBtn.registerOnEv( this );
    ipponWhBtn.registerOnEv( this );
    wazariWhBtn.registerOnEv( this );
    shidoWhBtn.registerOnEv( this );

    ipponBlBtn.enable();
    wazariBlBtn.enable();
    shidoBlBtn.enable();
    ipponWhBtn.enable();
    wazariWhBtn.enable();
    shidoWhBtn.enable();

    osaekCtrl->registerOnEv( this );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
Score::~Score()
{
    ipponBlBtn.disable();
    wazariBlBtn.disable();
    shidoBlBtn.disable();
    ipponWhBtn.disable();
    wazariWhBtn.disable();
    shidoWhBtn.disable();
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool Score::equalScore()
{
    if( !hasWinner() )
        return( score[blue].wazari && score[white].wazari );
    else
        return false;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
bool Score::hasWinner()
{
    bool ret = score[white].ippon || score[blue].ippon;
    ret = ret || ( score[white].shido == maxShido );
    ret = ret || ( score[blue].shido  == maxShido );

    return ret;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Score::registerOnEv(IScoreEvHandler* handler)
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] == 0 )
        {
            evHandler[i] = handler;
            break;
        }
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Score::onButtonEv(const PltFrm::Btn::BtnInstance& btn)
{
    bool swState = scoreSw.isSet();
    FighterColour scoreCol;
    FighterColour otherCol;
    Scoring actScore;

    // seting variables for the following alogrithm
    switch( btn )
    {
    // blue buttons
    case PltFrm::Btn::ipponBlBtn:
        scoreCol = blue;
        otherCol = white;
        actScore = ippon;
        break;
    case PltFrm::Btn::wazariBlBtn:
        scoreCol = blue;
        otherCol = white;
        actScore = wazari;
        break;
    case PltFrm::Btn::shidoBlBtn:
        scoreCol = blue;
        otherCol = white;
        actScore = shido;
        break;

    // white buttons
    case PltFrm::Btn::ipponWhBtn:
        scoreCol = white;
        otherCol = blue;
        actScore = ippon;
        break;
    case PltFrm::Btn::wazariWhBtn:
        scoreCol = white;
        otherCol = blue;
        actScore = wazari;
        break;
    case PltFrm::Btn::shidoWhBtn:
        scoreCol = white;
        otherCol = blue;
        actScore = shido;
    default:
        break;
    }

    // scoring algorithm
    switch( actScore )
    {
    case ippon:
        if( swState )
        {
            if( !hasWinner() )
            {
                score[scoreCol].ippon = true;
                notify( evIppon );
            }
        }
        else
        {
            if( score[scoreCol].ippon )
            {
                score[scoreCol].ippon = false;
                notify( evIpponDel );
            }
        }
        break;
    case wazari:
    {
        bool scoreState = equalScore();

        if( swState )
        {
            if( score[scoreCol].wazari )
            {
                if( !score[otherCol].ippon )
                {
                    score[scoreCol].ippon  = true;
                    score[scoreCol].wazari = false;
                    notify( evIppon );
                }
            }
            else
            {
                if( !score[scoreCol].ippon )
                    score[scoreCol].wazari = true;
            }
        }
        else
        {
            if( score[scoreCol].ippon )
            {
                score[scoreCol].ippon  = false;
                score[scoreCol].wazari = true;
                notify( evIpponDel );
            }
            else
                score[scoreCol].wazari = false;
        }

        // comparing score before/after score states
        if( scoreState != equalScore() )
        {
            if( equalScore() )
                notify( evEqualScore );
            else
                notify( evEqualScoreLost );
        }
        break;
    }
    case shido:
        if( swState )
        { // incrementing shido
            if( score[scoreCol].shido == (maxShido - 1) )
            {
                if( !hasWinner() )
                {
                    score[scoreCol].shido = maxShido;
                    score[otherCol].ippon = true;
                    notify( evDisqual );
                }
            }
            else
                score[scoreCol].shido++;
        }
        else
        { // decrementing shido
            if( score[scoreCol].shido == maxShido )
            {
                score[scoreCol].shido = maxShido - 1;
                score[otherCol].ippon = false;
                notify( evDisqualDel );
            }
            else
            {
                if( score[scoreCol].shido > 0 )
                    score[scoreCol].shido--;
            }
        }
        break;

    default:
        break;
    }

    // actualize Digits
    mDispl->setScoreDigits( blue , score[blue] );
    mDispl->setScoreDigits( white, score[white] );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Score::onOsaekTimeCtrlEv(Obj::OsaekTimeCtrl::OsaekCtrlEv ev)
{
    FighterColour scoreCol;
    FighterColour otherCol;
    Scoring scoring;

    // setting variables for the following algorithm
    switch( ev )
    {
    case OsaekTimeCtrl::evWazariTimeBl:
        scoreCol = blue;
        otherCol = white;
        scoring  = wazari;
        break;
    case OsaekTimeCtrl::evIpponTimeBl:
        scoreCol = blue;
        otherCol = white;
        scoring  = ippon;
        break;
    case OsaekTimeCtrl::evWazariTimeWh:
        scoreCol = white;
        otherCol = blue;
        scoring  = wazari;
        break;
    case OsaekTimeCtrl::evIpponTimeWh:
        scoreCol = white;
        otherCol = blue;
        scoring  = ippon;
        break;
    default:
        break;
    }

    // Score algorithm
    switch( scoring )
    {
    case wazari:
    {
        bool scoreState = equalScore();

        if( score[scoreCol].wazari )
        {
            if( !score[otherCol].ippon )
            {
                score[scoreCol].ippon  = true;
                score[scoreCol].wazari = false;
                notify( evIppon );
            }
        }
        else
        {
            if( !score[scoreCol].ippon )
                score[scoreCol].wazari = true;
        }

        // comparing score before/after score states
        if( scoreState != equalScore() )
        {
            if( equalScore() )
                notify( evEqualScore );
            else
                notify( evEqualScoreLost );
        }
        break;
    }
    case ippon:
        if( !hasWinner() )
        {
            score[scoreCol].ippon = true;
            notify( evIppon );
        }
        break;
    default:
        break;
    }
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Score::notify(const ScoreEv& ev)
{
    for( int i = 0 ; i < nrOfEvHandlers ; ++i )
    {
        if( evHandler[i] != 0 )
        {
            evHandler[i]->onScoreEv( ev );
        }
    }
}
//--------------------------------------------------------------

} /* namespace Obj */
