#pragma once
#include "..\\Engine_SOURCE\\qoScene.h"
#include "ArchitectureInclude.h"
#include "qoGameObject.h"

namespace qo
{
	class Player;
	class LabGuard;
	class LabTurret;
	class Stage1_2 : public Scene
	{
	public:
		Stage1_2();
		virtual ~Stage1_2();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		// 특정 tag 값을 가진 잠긴 문을 열어주는 함수
		void UnlockDoor(int tag);
		void ActivateElevator(int tag);

		void Enter() override;
		void Exit() override;

	private:
		static const int EventButtonCount = 7;
		EventSwitch* EventButton[EventButtonCount];

		static const int EventDoorCount = 3;
		LockedDoor* EventDoor[EventDoorCount];

		static const int EventElevatorCount = 6;
		Elevator* EventElevator[EventElevatorCount];

		static const int LabGuardCount = 28;
		LabGuard* EnemyLabGuard[LabGuardCount];

		static const int LabTurretCount = 12;
		LabTurret* EnemyLabTurret[LabTurretCount];

		Player* mPlayer;
	};
}
