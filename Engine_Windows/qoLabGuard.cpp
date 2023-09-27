#include "qoLabGuard.h"

namespace qo
{
    LabGuard::LabGuard()
        : myTYPE(eMelee)
        , mySTAGE(eSearch)
        , myHP(50)
        , mySPEED(50)
        , myATK(10)
    {
        SetType(myTYPE);
        SetStage(mySTAGE);
        SetHP(myHP);
        SetMovementSpeed(mySPEED);
        SetATK(myATK);
    }

    LabGuard::~LabGuard()
    {
    }

    void LabGuard::Search()
    {
        // 肺流 累己
    }

    void LabGuard::Chase()
    {
        // 肺流 累己
    }

    void LabGuard::Attack()
    {
        // 肺流 累己
    }

    void LabGuard::Hit(int damage)
    {
        myHP -= damage;
    }

    void LabGuard::Dead()
    {
        // 肺流 累己
    }
}
