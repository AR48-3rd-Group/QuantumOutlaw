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

    void LabTurret::Dead()
    {
    }

    void LabTurret::TakeHit(int DamageAmount, math::Vector3 HitDir)
    {
    }
}
