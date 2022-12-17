#pragma once
// Sound��� - ��� ���� �߿�
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

// �ڵ�
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class CSound;

class CSoundManager
{
	SINGLE(CSoundManager);

private:
	LPDIRECTSOUND8 m_pSound;	//���� ī�� ��ǥ ��ü
	CSound* m_pBGM;				//���� ������ BGM Sound

public:
	int init();
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(CSound* _pSound);
};

