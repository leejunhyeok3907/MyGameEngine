#pragma once

class CScene;

class CSceneManager
{
	SINGLE(CSceneManager)

private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END];//모든 Scene의 목록
	CScene*		m_pCurScene;//현재 Scene


public:
	void init();
	void update();
	void render(HDC _dc);

public:
	CScene* GetCurScene() { return m_pCurScene; }

	void ChangeScene(SCENE_TYPE _eNext);
};

