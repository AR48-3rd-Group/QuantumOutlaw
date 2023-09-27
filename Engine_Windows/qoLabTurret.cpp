#include "qoLabTurret.h"

namespace qo
{
    LabTurret::LabTurret()
    {
        SetType(eRanged);
        SetStage(eSearch);
        SetHP(80);
        SetMovementSpeed(0);
        SetATK(15);
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
        int currentHP = GetHP();
        currentHP -= damage;
        SetHP(currentHP);
    }

    void LabTurret::Dead()
    {
        // 肺流 累己
    }
}
