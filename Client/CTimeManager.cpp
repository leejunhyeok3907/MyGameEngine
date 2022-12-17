#include "pch.h"
#include "CTimeManager.h"
#include "CCore.h"

CTimeManager::CTimeManager()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDeltaTime(0.f)
	, m_dAcc(0.f)
	, m_iCallCount(0)
	, m_iFPS(0)
{

}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::init()
{
	//현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);

	//초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeManager::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//이전 프레임의 카운팅과 현재 프레임의 카운팅 값의 차이를 구한다.
	m_dDeltaTime=(double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)/(double)m_llFrequency.QuadPart;

	//이전 카운트 값을 현재값으로 갱신
	m_llPrevCount = m_llCurCount;

#ifdef _DEBUG
	if (m_dDeltaTime > (1. / 60.))
		m_dDeltaTime = (1. / 60.);
#endif // DEBUG
}

void CTimeManager::render()
{
	m_iCallCount++;
	m_dAcc += m_dDeltaTime;

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %lf", m_iFPS, m_dDeltaTime);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
