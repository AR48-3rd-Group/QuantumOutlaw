#pragma once
#include "..\\Engine_SOURCE\\qoScene.h"
#include "ArchitectureInclude.h"
#include "qoGameObject.h"

namespace qo
{
	class Player;
	class LabGuard;
	class LabTurret;
	class Trigger;
	class Stage1_1 : public Scene
	{
	public:
		Stage1_1();
		virtual ~Stage1_1();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void UnlockDoor(int tag);

		void Enter() override;
		void Exit() override;

	private:
		static const int LabGuardCount = 7;
		LabGuard* EnemyLabGuard[LabGuardCount];

		Player* mPlayer;
		EventSwitch* EventButton;
		LockedDoor* EventDoor;
	};
}
