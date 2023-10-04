#pragma once
#include "qoEnums.h"
#include "qoEntity.h"
#include "qoLayer.h"

namespace qo
{
	using namespace qo::enums;

	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		Layer* GetLayer(UINT index) { return&mLayers[index]; }
		void AddGameObject(GameObject* gameObject, UINT layerIndex);

		// 개체의 Transform, MeshRenderer, Collider를 입력한 값에 따라서 자동생성 해주는 함수
		void CreateAndSetUpGameObject(GameObject* object, LAYER objectLayer, float xPixels, float yPixels, float widthInPixels, float heightInPixels, const Vector4& color);


	private:
		Layer mLayers[LAYER::MAX];
	};
}
