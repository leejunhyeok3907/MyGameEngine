#include "pch.h"
#include "CUIManager.h"

#include "CSceneManager.h"
#include "CScene.h"
#include "CUI.h"

#include "CKeyManager.h"

CUIManager::CUIManager()
{

}

CUIManager::~CUIManager()
{

}

void CUIManager::update()
{
	//Focused UI 확인
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI) return;

	bool b_LButtonTap = KEY_TAP(KEY::LBUTTON);
	bool b_LButtonAway = KEY_AWAY(KEY::LBUTTON);

	// Forcued UI내에서, 부모 UI 포함, 자식 UI들 중 실제 타겟팅 된 UI를 가져온다.
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (b_LButtonTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (b_LButtonAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}

			//왼쪽 버튼 떼면, 눌렸던 체크를 다시 해제
			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void CUIManager::SetTargetedUI(CUI* _pUI)
{
	//이미 포커싱 중인 경우 or 포커싱 해제 요청인 경우
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneManager::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); iter++)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	//벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

CUI* CUIManager::GetTargetedUI(CUI* _pParentUI)
{
	bool b_LButtonTap = KEY_TAP(KEY::LBUTTON);
	bool b_LButtonAway = KEY_AWAY(KEY::LBUTTON);

	CUI* pTargetUI = nullptr;

	//1.부모 UI포함, 모든 자식들을 검사해야 한다.

	//함수 호출할때마다 지역객체로 생성하는것보다 정적객체로 둠
	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	//혹시 모를 데이터가 들어있을경우를 대비해 초기화
	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);


	//2.타겟 UI들중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI
	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		//큐에서 꺼내온 UI가 TargetUI인지 확인
		//타겟 UI들 중 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI
		if (pUI->IsMouseOn())
		{
			//ptargetUI가 교체되는경우
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}

			pTargetUI = pUI;
		}
		else
		{

			vecNoneTarget.push_back(pUI);
		}

		//왼쪽 버튼 떼면, 눌렸던 체크를 다시 해제
		if (b_LButtonAway)
		{
			for (size_t i = 0; i < vecNoneTarget.size(); i++)
			{
				vecNoneTarget[i]->m_bLbtnDown = false;
			}
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();

		for (size_t i = 0; i < vecChild.size(); i++)
		{
			queue.push_back(vecChild[i]);
		}
	}

	return pTargetUI;
}

CUI* CUIManager::GetFocusedUI()
{
	CScene* pCurScene = CSceneManager::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool b_LButtonTap = KEY_TAP(KEY::LBUTTON);

	//기존 포커싱 UI를 받아두고 변경되었는지 확인
	CUI* pFocusedUI = m_pFocusedUI;

	//왼쪽 클릭이 발생하지않았으면 포커싱 전환이 발생할 이유가 없음.
	if (b_LButtonTap)
	{
		vector<CObject*>::iterator target_iter = vecUI.end();
		vector<CObject*>::iterator iter = vecUI.begin();

		for (; iter!=vecUI.end(); iter++)
		{
			//조건에 맞을경우 계속 교체
			if (((CUI*)*iter)->IsMouseOn())
			{
				target_iter = iter;
			}
		}

		//모든 UI가 포커싱되지 않음.
		if (vecUI.end() == target_iter)
		{
			return nullptr;
		}

		//최종적으로 target_iter가 가지고있는 데이터가 클릭된 UI
		pFocusedUI = (CUI*)(*target_iter);

		//vector 내에서 맨 뒤로 순번 교체
		vecUI.erase(target_iter);
		vecUI.push_back(pFocusedUI);
	}


	return pFocusedUI;
}
