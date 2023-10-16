#include "qoLabTurretScript.h"
#include "qoLabTurret.h"
#include "qoTransform.h"
#include "qoRigidbody.h"
#include "qoPlayer.h"
#include "qoTurretAttack.h"
#include "qoCollider.h"
#include "qoMeshRenderer.h"
#include "qoResourceManager.h"
#include "qoSceneManager.h"
#include "qoBulletScript.h"

namespace qo
{
	LabTurretScript::LabTurretScript()
		: mLabTurret(nullptr)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, AttackTime(0.f)
		, mDamagedDlay(0.f)
	{

	}

	LabTurretScript::~LabTurretScript()
	{
	}

	void LabTurretScript::Initialize()
	{
		mLabTurret = dynamic_cast<LabTurret*>(GetOwner());
		mTransform = mLabTurret->GetComponent<Transform>();
		//mRigidbody = mLabTurret->GetComponent<Rigidbody>();
		LabTurretPos = mTransform->GetPosition();

		mPlayer = dynamic_cast<LabTurret*>(GetOwner())->mPlayer;
		mPlayerTr = mPlayer->GetComponent<Transform>();

		assert(mLabTurret);
	}

	void LabTurretScript::Update()
	{
		PlayerPos = mPlayerTr->GetPosition();
		LabTurretPos = mTransform->GetPosition();

		switch (mLabTurret->GetStage())
		{
		case eStage::eSearch:
			Search();
			break;
		case eStage::eFall:
			Fall();
			break;
		case eStage::eAttack:
			Attack();
			break;
		case eStage::eHit:
			Hit();
			break;
		case eStage::eDead:
			Dead();
			break;
		default:
			break;
		}
	}

	void LabTurretScript::LateUpdate()
	{
	}

	void LabTurretScript::Render()
	{
	}

	void LabTurretScript::Search()
	{
		/*if (!mRigidbody->GetGround())
		{
			mLabTurret->SetStage(eStage::eFall);
		}*/

		// +-0.5 ���� ���� �÷��̾ �����ϸ� attack �Լ���
		if ((LabTurretPos.x - 1.f <= PlayerPos.x) && (LabTurretPos.x + 1.f >= PlayerPos.x)
			&& (LabTurretPos.y - 0.5f <= PlayerPos.y) && (LabTurretPos.y + 0.5f >= PlayerPos.y))
		{
			mLabTurret->SetStage(eStage::eAttack);
		}
	}

	void LabTurretScript::Fall()
	{
	/*	if (mRigidbody->GetGround())
		{
			mLabTurret->SetStage(eStage::eSearch);
		}*/
	}

	void LabTurretScript::Attack()
	{
		// �Ѿ� ����� (���� �����ְ�)
		// +- 0.5 ���� ���� �÷��̾ �����ϸ� �����Ѵ�
		if ((LabTurretPos.x - 0.5f <= PlayerPos.x) && (LabTurretPos.x + 0.5f >= PlayerPos.x))
		{
			AttackTime += Time::DeltaTime();

			if (AttackTime > 1.f)
			{
				Vector3 Dir = PlayerPos - LabTurretPos;
				Dir.Normalize();
				TurretAttack* turretattack = new TurretAttack(Dir);

				Transform* tr = turretattack->AddComponent<Transform>();
				tr->SetPosition(LabTurretPos); // �Ѿ� ������ġ�� ����ġ�� ����
				tr->SetScale(Vector3(0.1f, 0.1f, 0.1f));
				tr->SetColor(Vector4(1.0f, 1.0f, 0.0f, 0.0f));

				MeshRenderer* meshRenderer = turretattack->AddComponent<MeshRenderer>();
				meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"CircleMesh"));
				meshRenderer->SetShader(ResourceManager::Find<Shader>(L"CircleShader"));

				Collider* col = turretattack->AddComponent<Collider>();
				col->SetScale(Vector3(0.1f, 0.1f, 0.1f));

				turretattack->AddComponent<BulletScript>();

				turretattack->Initialize();

				SceneManager::GetActiveScene()->AddGameObject(turretattack, LAYER::BULLET);
				AttackTime = 0.f;
			}

		}

		// +- 0.5 ���� ���� �÷��̾ �������� ������ search
		else
		{
			AttackTime = 0.f;
			mLabTurret->SetStage(eStage::eSearch);
		}
	}

	void LabTurretScript::Hit()
	{
		mDamagedDlay += Time::DeltaTime();

		if (mDamagedDlay > 1.f)
		{
			mLabTurret->SetStage(eStage::eSearch);
			mDamagedDlay = 0.f;
		}
	}

	void LabTurretScript::Dead()
	{
		Destroy(mLabTurret);
	}
}
