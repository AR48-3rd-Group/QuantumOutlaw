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
		// 개체의 Transform, MeshRenderer, Collider를 입력한 값에 따라서 자동생성 해주는 함수
		void CreateAndSetUpGameObject(GameObject* object, LAYER objectLayer,float xPixels, float yPixels, float widthInPixels, float heightInPixels, const Vector4& color);

	private:
		DoorSwitch* OpenSwitch;
		LockedDoor* Goal;
	};
}
