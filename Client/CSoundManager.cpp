#include "pch.h"
#include "CSoundManager.h"

#include "CSound.h"

#include "CCore.h"

CSoundManager::CSoundManager()
	: m_pSound(nullptr)
	, m_pBGM(nullptr)
{

}

CSoundManager::~CSoundManager()
{

}

int CSoundManager::init()
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"�������̽� ���� ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	HWND hWnd = CCore::GetInst()->GetMainHwnd();

	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))//Flag�� ����
	{
		MessageBox(NULL, L"�������̽� �������� ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void CSoundManager::RegisterToBGM(CSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}
