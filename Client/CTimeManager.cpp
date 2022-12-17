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
	//���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);

	//�ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeManager::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//���� �������� ī���ð� ���� �������� ī���� ���� ���̸� ���Ѵ�.
	m_dDeltaTime=(double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)/(double)m_llFrequency.QuadPart;

	//���� ī��Ʈ ���� ���簪���� ����
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
