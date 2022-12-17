#include "pch.h"
#include "CIdleState.h"

#include "CSceneManager.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{

}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
}

void CIdleState::update()
{
	//Player�� ��ġ üũ
	CPlayer* pPlayer = (CPlayer*)CSceneManager::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	//������ ���� ������ ������ �������� ��ȯ
	CMonster* pMonster = GetMonster();
	Vec2 vMonPos = pMonster->GetPos();

	Vec2 vDiff = vPlayerPos - vMonPos;
	float fLen = vDiff.Length();

	//�÷��̾ ������ �νĹ��� ������ ����
	if (fLen < pMonster->GetInfo().fRecogRange)
	{
		ChangeAIState(GetAI(), MON_STATE::TRACE);  
	}
}

void CIdleState::Exit()
{
}
