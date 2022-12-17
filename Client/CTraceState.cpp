#include "pch.h"
#include "CTraceState.h"

#include "CSceneManager.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeManager.h"

CTraceState::CTraceState()
	: CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
}

void CTraceState::update()
{
	//Player의 위치 체크
	CPlayer* pPlayer = (CPlayer*)CSceneManager::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	Vec2 vMonPos = pMonster->GetPos();

	Vec2 vMonDir = vPlayerPos - vMonPos;
	vMonDir.Normalize();

	vMonPos += vMonDir * GetMonster()->GetInfo().fSpeed * fDT;

	GetMonster()->SetPos(vMonPos);
}

void CTraceState::Exit()
{
}
