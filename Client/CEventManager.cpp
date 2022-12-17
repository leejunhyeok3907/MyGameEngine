#include "pch.h"
#include "CEventManager.h"

#include "CObject.h"
#include "CSceneManager.h"
#include "CScene.h"

#include "AI.h"
#include "CState.h"

#include "CUIManager.h"

CEventManager::CEventManager()
{

}

CEventManager::~CEventManager()
{

}

void CEventManager::update()
{
	// ================================================
	// ���� �����ӿ��� ����ص� Dead Object���� ������.
	// ================================================
	for (size_t i = 0; i < m_vecDeadObj.size(); i++)
	{
		delete m_vecDeadObj[i];
	}
	m_vecDeadObj.clear();

	// ===========
	// Event ó��
	// ===========

	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventManager::Execute(const tEvent& _event)
{
	//switch-case�� �ȿ��� ������ �����ϱ� ���ؼ� ��ȣ�� ���� ������־����.
	switch (_event.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		//lParam : Object Address
		//wParam : Group Type

		CObject* pNewObj = (CObject*)_event.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_event.wParam;

		CSceneManager::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
	break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		//lParam : Object Address
		//Object�� Dead���·� ����
		//���� ���� Object���� ��Ƶ�
		CObject* pDeadObj = (CObject*)_event.lParam;
		pDeadObj->SetDead();
		m_vecDeadObj.push_back(pDeadObj);
	}
	break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		//lParam : Next SceneType
		//Scene ����
		CSceneManager::GetInst()->ChangeScene((SCENE_TYPE)_event.lParam);

		//��Ŀ�� UI ���� (���� SCene�� UI�� ����Ű�� �ֱ� ����)
		CUIManager::GetInst()->SetTargetedUI(nullptr);

		//Scene�� ����ɶ� ��κ��� Scene���� ��ü���� ������Ų��.
		//�ش� Scene�� Object ���õǾ��ִ� �̺�Ʈ�� �߻��� ��� ������ �ּ��� ��ġ�� �����Ͽ� �̺�Ʈ�� �߻���ų�������Ƿ�
		//Scene Change ������ �̺�Ʈ�� �����ؼ��� ó���� �ʿ���.
	}
	break;
	case EVENT_TYPE::CHANGE_AI_STATE:
	{
		//lParam:AI
		//wParam:Next Type
		AI* pAI = (AI*)_event.lParam;
		MON_STATE eNextState = (MON_STATE)_event.wParam;

		pAI->ChangeState(eNextState);
	}
	break;
	}
}
