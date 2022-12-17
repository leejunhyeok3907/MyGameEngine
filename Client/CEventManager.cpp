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
	// 이전 프레임에서 등록해둔 Dead Object들을 삭제함.
	// ================================================
	for (size_t i = 0; i < m_vecDeadObj.size(); i++)
	{
		delete m_vecDeadObj[i];
	}
	m_vecDeadObj.clear();

	// ===========
	// Event 처리
	// ===========

	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventManager::Execute(const tEvent& _event)
{
	//switch-case문 안에서 변수를 생성하기 위해선 괄호로 블럭을 만들어주어야함.
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
		//Object를 Dead상태로 변경
		//삭제 예정 Object들을 모아둠
		CObject* pDeadObj = (CObject*)_event.lParam;
		pDeadObj->SetDead();
		m_vecDeadObj.push_back(pDeadObj);
	}
	break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		//lParam : Next SceneType
		//Scene 변경
		CSceneManager::GetInst()->ChangeScene((SCENE_TYPE)_event.lParam);

		//포커스 UI 해제 (이전 SCene의 UI를 가리키고 있기 때문)
		CUIManager::GetInst()->SetTargetedUI(nullptr);

		//Scene이 변경될때 대부분은 Scene내의 객체들을 삭제시킨다.
		//해당 Scene의 Object 관련되어있는 이벤트가 발생할 경우 삭제된 주소의 위치를 참조하여 이벤트를 발생시킬수있으므로
		//Scene Change 이후의 이벤트에 관련해서는 처리가 필요함.
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
