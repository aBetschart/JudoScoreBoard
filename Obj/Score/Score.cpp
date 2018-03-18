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


namespace Obj
{
//--------------------------------------------------------------
Score::Score( JudoDisplay* displ, OsaekTimeCtrl* osaekCtrl ):
  mDispl( displ ), mOsaekCtrl( osaekCtrl ),
  locked(false), scoreSw( PltFrm::Switch::scoreSwitch ),
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

    mOsaekCtrl->registerOnEv( this );
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
        return( score[blue].wazari == score[white].wazari );
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
void Score::lock()
{
    locked = true;
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Score::unlock()
{
    locked = false;
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
    if( !locked )
    {
        bool swState = scoreSw.isSet();

        switch( btn )
        {

        // blue buttons
        case PltFrm::Btn::ipponBlBtn:
            if( swState )
            { // set ippon
                if( !hasWinner() )
                {
                    score[blue].ippon = true;
                    notify( evIppon );
                }
            }
            else
            { // unset ippon
                score[blue].ippon = false;
                notify( evIpponDel );
            }
            break;
        case PltFrm::Btn::wazariBlBtn:
        {
            bool scoreState = equalScore();

            if( swState )
            { // add wazari
                score[blue].wazari++;
                score[blue].wazari = score[blue].wazari % maxWazari;
            }
            else
            { // subtract wazari
                if( score[blue].wazari > 0 )
                    score[blue].wazari--;
            }

            if( scoreState != equalScore() )
            {
                if( equalScore() )
                    notify( evEqualScore );
                else
                    notify( evEqualScoreLost );
            }
            break;
        }
        case PltFrm::Btn::shidoBlBtn:
            if( swState )
            { // add shido
                if( score[blue].shido == (maxShido - 1) )
                {
                    if( !hasWinner() )
                    {
                        score[blue].shido++;
                        notify( evDisqual );
                    }
                }
                else
                {
                    score[blue].shido++;
                    notify( evShido );
                }
            }
            else
            { // subtract shido
                if( score[blue].shido == maxShido )
                {
                    score[blue].shido--;
                    notify( evDisqualDel );
                }
                else if( score[blue].shido > 0 )
                {
                    score[blue].shido--;
                    notify( evShidoDec );
                }
            }
            break;

            // white buttons
        case PltFrm::Btn::ipponWhBtn:

            break;
        case PltFrm::Btn::wazariWhBtn:

            break;
        case PltFrm::Btn::shidoWhBtn:

        default:
            break;
        }
    }
    mDispl->setScoreDigits( blue , score[blue] );
    mDispl->setScoreDigits( white, score[white] );
}
//--------------------------------------------------------------


//--------------------------------------------------------------
void Score::onOsaekTimeCtrlEv(Obj::OsaekTimeCtrl::OsaekCtrlEv ev)
{
    switch( ev )
    {
    case OsaekTimeCtrl::evWazariTimeBl:
    {
        bool scoreState = equalScore();

        score[blue].wazari++;
        score[blue].wazari = score[blue].wazari % maxWazari;

        if( scoreState != equalScore() )
        {
            if( equalScore() )
                notify( evEqualScore );
            else
                notify( evEqualScoreLost );
        }
        break;
    }
    case OsaekTimeCtrl::evIpponTimeBl:
        if( !hasWinner() )
        {
            score[blue].ippon = true;
            notify( evIppon );
        }
        break;
    case OsaekTimeCtrl::evWazariTimeWh:
    {
        bool scoreState = equalScore();

        score[white].wazari++;
        score[white].wazari = score[white].wazari % maxWazari;

        if( scoreState != equalScore() )
        {
            if( equalScore() )
                notify( evEqualScore );
            else
                notify( evEqualScoreLost );
        }
    }
    break;
    case OsaekTimeCtrl::evIpponTimeWh:
        if( !hasWinner() )
        {
            score[white].ippon = true;
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
