#pragma once
#include "qoEntity.h"
#include "qoComponent.h"
#include "qoScript.h"

namespace qo
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Paused,
			Dead,
		};

		friend __forceinline static void Destroy(GameObject* obj);

		GameObject();
		virtual ~GameObject();

		template <typename T>
		T* AddComponent()
		{
			T* component = new T();
			Component* comp = dynamic_cast<Component*>(component);
			if (comp)
			{
				int myOrder = comp->GetUpdateOrder();
				mComponents[myOrder] = comp;
				mComponents[myOrder]->mOwner = this;
			}

			Script* script = dynamic_cast<Script*>(component);
			if (script != nullptr)
			{
				mScripts.push_back(script);
				script->SetOwner(this);
			}

			return component;
		}

		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (auto c : mComponents)
			{
				component = dynamic_cast<T*>(c);

				if (component != nullptr)
					return component;
			}

			return nullptr;
		}

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		eState GetGameObjectState() const { return mState; }

	private:
		void Dead() { mState = eState::Dead; }

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;
	};

	__forceinline static void Destroy(GameObject* obj)
	{
		obj->Dead();
	}
}
