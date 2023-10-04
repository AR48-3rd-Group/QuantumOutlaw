#pragma once
#include "..\\Engine_SOURCE\\qoScene.h"
#include "ArchitectureInclude.h"

namespace qo
{
	class Player;
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
		Player* mPlayer;
		DoorSwitch* OpenSwitch;
		LockedDoor* Goal;
	};
}
