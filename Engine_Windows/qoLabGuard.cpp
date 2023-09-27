#include "qoLabGuard.h"

namespace qo
{
    LabGuard::LabGuard()
    {
        SetType(eMelee);
        SetStage(eSearch);
        SetHP(50);
        SetMovementSpeed(50);
        SetATK(10);
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
        int currentHP = GetHP();
        currentHP -= damage;
        SetHP(currentHP);
    }

    void LabGuard::Dead()
    {
        // 肺流 累己
    }
}
