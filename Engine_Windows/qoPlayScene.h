#pragma once
#include "..\\Engine_SOURCE\\qoScene.h"
#include "ArchitectureInclude.h"

namespace qo
{
	class Player;
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void Enter() override;
		void Exit() override;

	private:
		DoorSwitch* doorswitch;
		LockedDoor* lockeddoor;
		Player*		mPlayer;
	};
}
