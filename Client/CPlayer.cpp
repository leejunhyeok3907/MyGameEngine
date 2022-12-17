#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CSceneManager.h"
#include "CScene.h"

#include "CMissile.h"

#include "CResourceManager.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CRigidBody.h"
#include "CGravity.h"

#include <time.h>

CPlayer::CPlayer()
	: m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_iCurDir(1)
	, m_iPrevDir(1)
{
	//텍스쳐 로딩하기
	//m_pTex=CResourceManager::GetInst()->LoadTexture(L"PlayerTex", L"texture\\image.bmp");

	CreateCollider();

	GetCollider()->SetOffsetPos(Vec2(-5.f, 20.f));
	GetCollider()->SetScale(Vec2(20.f, 20.f));

	//텍스쳐 로딩하기
	//CTexture* pTex = CResourceManager::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Male-Average-Average-Sprite-Sheet.bmp");
	CreateAnimator();

	GetAnimator()->LoadAnimation(L"animation\\player_idle.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_jump.anim");

	//GetAnimator()->CreateAnimation(L"PLAYER_IDLE", pTex, Vec2(3.f, 0.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.1f, 6);
	//GetAnimator()->CreateAnimation(L"PLAYER_WALK", pTex, Vec2(3.f, 64.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.1f, 6);
	//GetAnimator()->CreateAnimation(L"PLAYER_JUMP", pTex, Vec2(3.f, 320.f), Vec2(32.f, 64.f), Vec2(32.f, 0.f), 0.1f, 6);

	GetAnimator()->Play(L"PLAYER_IDLE", true);

	//GetAnimator()->FindAnimation(L"PLAYER_IDLE")->Save(L"animation\\player_idle.anim");
	//GetAnimator()->FindAnimation(L"PLAYER_WALK")->Save(L"animation\\player_walk.anim");
	//GetAnimator()->FindAnimation(L"PLAYER_JUMP")->Save(L"animation\\player_jump.anim");

	CreateRigidBody();

	CreateGravity();
}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	update_move();

	update_state();

	update_animation();

	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2(640.f, 384.f));
	}

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iCurDir;
}

void CPlayer::render(HDC _dc)
{
	//컴포넌트(충돌체, ect)등이 있는경우 렌더
	Component_render(_dc);

	//CTexture* pTex = CResourceManager::GetInst()->LoadTexture(L"PT", L"texture\\img.bmp");

	//Vec2 vPos = GetPos();
	//vPos = CCamera::GetInst()->GetRenderPos(vPos);

	//float width = (float)pTex->GetWidth();
	//float height = (float)pTex->GetHeight();

	//BLENDFUNCTION bf = {};

	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = AC_SRC_ALPHA;
	//bf.SourceConstantAlpha = 255;
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (L"Ground" == pOtherObj->GetName())
	{
		Vec2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;


	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(-1.f, -7.f));

	CreateObject(pMissile, GROUP_TYPE::PROJECTILE_PLAYER);
}

void CPlayer::update_state()
{
	//외적의 요소에 의한 상태변환 또한 고려해야하기 때문에
	//단순하게 키 입력으로만 전환이 이루어지면 애니메이션에 버그가 생긴다.

	if (KEY_HOLD(KEY::A))
	{
		m_iCurDir = -1;

		if (PLAYER_STATE::JUMP != m_eCurState)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (KEY_HOLD(KEY::D))
	{
		m_iCurDir = 1;

		if (PLAYER_STATE::JUMP != m_eCurState)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (0.f == GetRigidBody()->GetSpeed() && PLAYER_STATE::JUMP != m_eCurState)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		m_eCurState = PLAYER_STATE::JUMP;
		if (GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -300.f));
		}
	}
}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-200.f, 0.f));
	}

	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(200.f, 0.f));
	}


	if (KEY_TAP(KEY::A))
	{
		pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
	}

	if (KEY_TAP(KEY::D))
	{
		pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
	}
}

void CPlayer::update_animation()
{
	//어떠한 요소에 의해 상태가 바뀔경우에만 업데이트
	if (m_ePrevState == m_eCurState
		&& m_iPrevDir == m_iCurDir) return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iCurDir==-1)
		{
			GetAnimator()->Play(L"PLAYER_IDLE", true);
		}
		else
		{
			GetAnimator()->Play(L"PLAYER_IDLE", true);
		}
	}
		break;
	case PLAYER_STATE::WALK:
		if (m_iCurDir==-1)
		{
			GetAnimator()->Play(L"PLAYER_WALK", true);
		}
		else
		{
			GetAnimator()->Play(L"PLAYER_WALK", true);
		}
		break;
	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DEAD:

		break;
	case PLAYER_STATE::JUMP:
		if (m_iCurDir == -1)
		{
			GetAnimator()->Play(L"PLAYER_JUMP", true);
		}
		else
		{
			GetAnimator()->Play(L"PLAYER_JUMP", true);
		}
		break;
	}
}

void CPlayer::update_gravity()
{
	//중력의 특징
	// 일반적인 힘의 경우 동일한 힘 내에 질량이 클경우 가속이 줄어드는데 (F=M*A)
	// 중력에 의한 힘의 경우 물체의 질량은 큰 영향을 주지못하기때문에
	// 중력의 경우 고정적인 가속(9.8m/s)을 줘야한다

	GetRigidBody()->AddForce(Vec2(0.f, 500.f)); 
}
