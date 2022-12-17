#include "CButtonUI.h"
#include "CScene.h"

CButtonUI::CButtonUI()
	: CUI(false)
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneInst(nullptr)
	, m_pSceneFunc(nullptr)
{
}

CButtonUI::~CButtonUI()
{
}

void CButtonUI::MouseOn()
{
}

void CButtonUI::MouseLbtnDown()
{
}

void CButtonUI::MouseLbtnUp()
{
}

void CButtonUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);
	}

	//두값 모두 주소값이 채워져있는 경우
	if (m_pSceneFunc && m_pSceneInst)
	{
		//객체로 맴버함수의 주소를 호출
		((*m_pSceneInst).*m_pSceneFunc)();
	}
}

void CButtonUI::SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
{
	m_pSceneInst = _pScene;
	m_pSceneFunc = _pSceneFunc;
}