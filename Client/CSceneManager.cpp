#include "pch.h"
#include "CSceneManager.h"
#include "CScene_Start.h"
#include "CScene_Tool.h"

CSceneManager::CSceneManager()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{

}

CSceneManager::~CSceneManager()
{
	//Scene ���� ����

	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneManager::init()
{
	//Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");

	/*
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage01;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage02;*/

	//���� Scene ����
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void CSceneManager::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}

void CSceneManager::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

void CSceneManager::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)_eNext];

	m_pCurScene->Enter();
}
