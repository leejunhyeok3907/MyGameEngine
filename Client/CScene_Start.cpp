#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CGround.h"

#include "CCore.h"

#include "CPathManager.h"
#include "CTexture.h"

#include "CCollisionManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CTimeManager.h"
#include "CCamera.h"

#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"

#include "CRigidBody.h"
#include "SelectGDI.h"

CScene_Start::CScene_Start()
	: m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	//CScene::update(); //부모쪽에 구현해둔 맴버함수를 그대로 이용

	//if (KEY_TAP(KEY::ENTER))
	//{
	//	ChangeScene(SCENE_TYPE::TOOL);
	//}

	if (KEY_TAP(KEY::LBUTTON))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetClientPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt); 
	}

	if (KEY_HOLD(KEY::LBUTTON))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
	}

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);

		for (size_t j = 0; j < vecObj.size(); j++)
		{
			if (!vecObj[j]->IsDead())
			{
				if (m_bUseForce && vecObj[j]->GetRigidBody())
				{
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();

					if (fLen < m_fForceRadius)
					{
						float fRatio = 1.f - (fLen / m_fForceRadius);
						float fForce = m_fForce * fRatio;

						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);
					}
				}

				vecObj[j]->update();
			}
		}
	}
}

void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);

	if (!m_bUseForce) return;

	SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	m_fCurRadius += m_fForceRadius * 3.f * fDT;

	if (m_fCurRadius > m_fForceRadius)
	{
		m_fCurRadius = 0.f;
	}

	Vec2 RenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);

	Ellipse(_dc,
		RenderPos.x - m_fCurRadius,
		RenderPos.y - m_fCurRadius,
		RenderPos.x + m_fCurRadius,
		RenderPos.y + m_fCurRadius);
}

void CScene_Start::Enter()
{
	//Object 추가
	CObject* pObj = new CPlayer;
	
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));

	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CObject* anotherPlayer = pObj->Clone();
	//anotherPlayer->SetPos(Vec2(740.f, 384.f));
	//AddObject(anotherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));

	AddObject(pMon, GROUP_TYPE::MONSTER);


	CObject* pGround = new CGround;
	pGround->SetName(L"Ground");
	pGround->SetPos(Vec2(640.f, 584.f));
	pGround->SetScale(Vec2(200.f, 60.f));
	AddObject(pGround, GROUP_TYPE::GROUND);

	//타일 로딩
	//LoadTile(L"Tile\\Start.tile");

	//충돌 지정
	//Player그룹과 Monster그룹 간의 충돌체크
	CCollisionManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJECTILE_PLAYER);
	CCollisionManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	//Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	init();
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionManager::GetInst()->Reset();
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetClientPos(MOUSE_POS);
}
