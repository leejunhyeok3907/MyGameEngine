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
	//Focused UI Ȯ��
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI) return;

	bool b_LButtonTap = KEY_TAP(KEY::LBUTTON);
	bool b_LButtonAway = KEY_AWAY(KEY::LBUTTON);

	// Forcued UI������, �θ� UI ����, �ڽ� UI�� �� ���� Ÿ���� �� UI�� �����´�.
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

			//���� ��ư ����, ���ȴ� üũ�� �ٽ� ����
			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void CUIManager::SetTargetedUI(CUI* _pUI)
{
	//�̹� ��Ŀ�� ���� ��� or ��Ŀ�� ���� ��û�� ���
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

	//���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

CUI* CUIManager::GetTargetedUI(CUI* _pParentUI)
{
	bool b_LButtonTap = KEY_TAP(KEY::LBUTTON);
	bool b_LButtonAway = KEY_AWAY(KEY::LBUTTON);

	CUI* pTargetUI = nullptr;

	//1.�θ� UI����, ��� �ڽĵ��� �˻��ؾ� �Ѵ�.

	//�Լ� ȣ���Ҷ����� ������ü�� �����ϴ°ͺ��� ������ü�� ��
	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	//Ȥ�� �� �����Ͱ� ���������츦 ����� �ʱ�ȭ
	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);


	//2.Ÿ�� UI����, �� �켱������ ���� ������ �� ���� ������ �ڽ� UI
	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		//ť���� ������ UI�� TargetUI���� Ȯ��
		//Ÿ�� UI�� �� �� �켱������ ���� ������ �� ���� ������ �ڽ� UI
		if (pUI->IsMouseOn())
		{
			//ptargetUI�� ��ü�Ǵ°��
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

		//���� ��ư ����, ���ȴ� üũ�� �ٽ� ����
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

	//���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ��
	CUI* pFocusedUI = m_pFocusedUI;

	//���� Ŭ���� �߻������ʾ����� ��Ŀ�� ��ȯ�� �߻��� ������ ����.
	if (b_LButtonTap)
	{
		vector<CObject*>::iterator target_iter = vecUI.end();
		vector<CObject*>::iterator iter = vecUI.begin();

		for (; iter!=vecUI.end(); iter++)
		{
			//���ǿ� ������� ��� ��ü
			if (((CUI*)*iter)->IsMouseOn())
			{
				target_iter = iter;
			}
		}

		//��� UI�� ��Ŀ�̵��� ����.
		if (vecUI.end() == target_iter)
		{
			return nullptr;
		}

		//���������� target_iter�� �������ִ� �����Ͱ� Ŭ���� UI
		pFocusedUI = (CUI*)(*target_iter);

		//vector ������ �� �ڷ� ���� ��ü
		vecUI.erase(target_iter);
		vecUI.push_back(pFocusedUI);
	}


	return pFocusedUI;
}
