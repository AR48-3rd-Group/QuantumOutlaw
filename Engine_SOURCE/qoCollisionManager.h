#pragma once

#include "qoCollider.h"

namespace qo
{
	union ColliderID
	{
		struct
		{
			UINT left;
			UINT right;
		};
		UINT64 id;
	};

	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render();

		static void Clear();
		static void CollisionLayerCheck(LAYER left, LAYER right, bool enable);
		static void LayerCollision(class Scene* scene, LAYER left, LAYER right);
		static void ColliderCollision(Collider* left, Collider* right);
		static bool Intersect(Collider* left, Collider* right);
		
		static void ForceCollisionExit(Collider* DeadCol);

	private:
		static std::map<UINT64, bool> mCollisionMap;
		static std::bitset<(UINT)LAYER::MAX> mLayersMasks[(UINT)LAYER::MAX];
	};
}


