#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"

#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CResourceManager.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
	, m_pVeilTex(nullptr)
{
}

CCamera::~CCamera()
{

}

void CCamera::init()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	m_pVeilTex = CResourceManager::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
}

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
	{
		m_vLookAt.y -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		m_vLookAt.y += 500.f * fDT;
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		m_vLookAt.x -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		m_vLookAt.x += 500.f * fDT;
	}

	//화면 중앙 좌표와 카메라 LookAt 좌표간의 차이값 계산
	CalDiff();
}

void CCamera::render(HDC _dc)
{
	if (m_listCamEffect.empty()) return;

	//시간 누적
	tCamEffect& effect = m_listCamEffect.front();
	effect.fCurTime += fDT;

	float fRatio = 0.f;//이펙트 진행 비율
	fRatio = effect.fCurTime / effect.fDuration;

	if (fRatio < 0.f)
		fRatio = 0.f;
	
	if (fRatio > 1.f)
		fRatio = 1.f;

	int iAlpha = 0;

	if (CAM_EFFECT::FADE_OUT == effect.eEffect)
	{
		iAlpha = (int)(255.f * fRatio);
	}
	else if(CAM_EFFECT::FADE_IN == effect.eEffect)
	{
		iAlpha = (int)(255.f * (1.f - fRatio));
	}

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	AlphaBlend(_dc, 0, 0
		, m_pVeilTex->GetWidth()
		, m_pVeilTex->GetHeight()
		, m_pVeilTex->GetDC(), 0, 0
		, m_pVeilTex->GetWidth()
		, m_pVeilTex->GetHeight(), bf);

	//진행 시간이 이펙트 지정 시간을 넘어선 경우
	if (effect.fDuration < effect.fCurTime)
	{
		//효과 종료
		m_listCamEffect.pop_front();
	}
}

void CCamera::CalDiff()
{
	//이전 LookAt과 현재 Look의 차이값을 보정해서 현재의 LookAt을 구한다.

	m_fAccTime += fDT;

	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vDir = m_vLookAt - m_vPrevLookAt;

		if (!vDir.IsZero())
		{
			m_vCurLookAt = m_vPrevLookAt + vDir.Normalize() * m_fSpeed * fDT;
		}
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}
