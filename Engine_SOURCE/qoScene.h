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

		virtual void Enter() = 0;
		virtual void Exit() = 0;
	private:
		Layer mLayers[LAYER::MAX];
	};
}
