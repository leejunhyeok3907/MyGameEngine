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
	//�ؽ��� �ε��ϱ�
	//m_pTex=CResourceManager::GetInst()->LoadTexture(L"PlayerTex", L"texture\\image.bmp");

	CreateCollider();

	GetCollider()->SetOffsetPos(Vec2(-5.f, 20.f));
	GetCollider()->SetScale(Vec2(20.f, 20.f));

	//�ؽ��� �ε��ϱ�
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
	//������Ʈ(�浹ü, ect)���� �ִ°�� ����
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
	//������ ��ҿ� ���� ���º�ȯ ���� ����ؾ��ϱ� ������
	//�ܼ��ϰ� Ű �Է����θ� ��ȯ�� �̷������ �ִϸ��̼ǿ� ���װ� �����.

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
	//��� ��ҿ� ���� ���°� �ٲ��쿡�� ������Ʈ
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
	//�߷��� Ư¡
	// �Ϲ����� ���� ��� ������ �� ���� ������ Ŭ��� ������ �پ��µ� (F=M*A)
	// �߷¿� ���� ���� ��� ��ü�� ������ ū ������ �������ϱ⶧����
	// �߷��� ��� �������� ����(9.8m/s)�� ����Ѵ�

	GetRigidBody()->AddForce(Vec2(0.f, 500.f)); 
}
