#include "qoLabTurret.h"

namespace qo
{
    LabTurret::LabTurret()
        : myTYPE(eRanged)
        , mySTAGE(eSearch)
        , myHP(80)
        , mySPEED(0)
        , myATK(15)
    {
        SetType(myTYPE);
        SetStage(mySTAGE);
        SetHP(myHP);
        SetMovementSpeed(mySPEED);
        SetATK(myATK);
    }

    LabTurret::~LabTurret()
    {
    }

    void LabTurret::Search()
    {
        // 肺流 累己
    }

    void LabTurret::Chase()
    {
        // 肺流 累己
    }

    void LabTurret::Attack()
    {
        // 肺流 累己
    }

    void LabTurret::Hit(int damage)
    {
        myHP -= damage;
    }

    void LabTurret::Dead()
    {
        // 肺流 累己
    }
}
