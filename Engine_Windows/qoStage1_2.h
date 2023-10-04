#pragma once
#include "..\\Engine_SOURCE\\qoScene.h"
#include "ArchitectureInclude.h"
#include "qoGameObject.h"

namespace qo
{
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

	private:
		static const int EventSwitchCount = 2;
		DoorSwitch* EventSwitch[EventSwitchCount];
		static const int EventDoorCount = 3;
		LockedDoor* EventTrap;
		LockedDoor* EventDoor[EventDoorCount];
	};
}
