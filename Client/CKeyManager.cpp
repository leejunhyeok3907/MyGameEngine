#include "pch.h"
#include "CKeyManager.h"
#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q','W','E','R','T','Y','U','I','O','P',
	'A','S','D','F','G','Z','X','C','V','B',
	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,
	VK_LBUTTON,
	VK_RBUTTON
};

CKeyManager::CKeyManager()
{

}

CKeyManager::~CKeyManager()
{

}

void CKeyManager::init()
{
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

//GetAsyncKeyState
//�񵿱� Ű ����� �Լ�
//�ڵ尡 ����Ǵ� ������ Ȯ���ϱ⶧���� �����찡 ��Ŀ�̵����ʾƵ� �۵���(��׶����ӿ��� �����).
//���� ������ ��Ʈ�� ��ȯ������ Ű�� ���� ���δ� ���� ������Ʈ���� Ȯ���ϸ� ��.

void CKeyManager::update()
{
	//������ ��Ŀ�� ���� �˾ƿ���
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();

	//������ ��Ŀ�����϶� �̺�Ʈ ����
	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			//Ű�� �����ִ�
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
				{
					//�������� �����־��ٸ�
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					//������ ���������ʴٸ�
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}

			//Ű�� ���������ʴ�
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					//������ �����־��ٸ�
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					//�������� ���������ʾҴٸ�
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevPush = false;
			}
		}

		//Mouse ��ġ ���
		POINT ptPos = {};
		GetCursorPos(&ptPos);

		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);
		m_vCurMousePos = Vec2(ptPos);

	}

	//������ ��Ŀ�� ��������
	else
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			m_vecKey[i].bPrevPush = false;
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}
