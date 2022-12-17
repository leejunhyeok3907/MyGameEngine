#include "pch.h"
#include "CScene_Tool.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CTile.h"

#include "CCore.h"
#include "CResourceManager.h"
#include "CPathManager.h"
#include "CUIManager.h"

#include "resource.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CButtonUI.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
	: m_pUI(nullptr)
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();

	if (KEY_TAP(KEY::LSHIFT))
	{
		SaveTileData();
		//CUIManager::GetInst()->SetTargetedUI(m_pUI);
	}

	if (KEY_TAP(KEY::CTRL))
	{
		LoadTileData();
	}
}

void CScene_Tool::Enter()
{
	//�� Scene���� ����� �޴� ����
	CCore::GetInst()->DockMenu();

	//Ÿ�� ����
	CreateTile(5, 5);

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 150.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

	CButtonUI* pBtnUI = new CButtonUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	//�ɹ��Լ��������� ��� �ּ�ǥ��(&)�� �ݵ�� �ٿ��־����
	//�θ�ü�� �̿��� �Լ��� ȣ���ų��� ĳ���� �������
	((CButtonUI*)pBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SaveTileData);
	pPanelUI->AddChild(pBtnUI);

	AddObject(pPanelUI, GROUP_TYPE::UI);

	//���纻 UI
	//CUI* pClonePanel = pPanelUI->Clone();
	//pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-100.f, 0.f));
	//((CButtonUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(ChangeScene, 0, 0);
	//AddObject(pClonePanel, GROUP_TYPE::UI);

	//m_pUI = pClonePanel;

	//Camera Look ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	//Camera ȿ�� ����
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
}

//���ڰ� �ǹ̰� ���� �Լ��� ���¸� �����ָ� ��
void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}

void CScene_Tool::Exit()
{
	CCore::GetInst()->DiviedMenu();

	DeleteAll();
}

void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBUTTON))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetClientPos(vMousePos);

		int iTileX = GetTileX();
		int iTileY = GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0 ||  iTileX <= iCol
			|| vMousePos.y < 0 || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}


}

void CScene_Tool::SaveTileData()
{
	//���Ͽ��� ��ȭ����
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";//� ���ڵ� �����ϰ�, � Ȯ���ڵ� ������
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathManager::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	//Ŀ�� ������Ʈ
	FILE* pFile = nullptr;

	//���� ����������, ������ ������, ���
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");
	assert(pFile);

	//Ÿ�� ���μ��� ���� ����
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	//��� Ÿ�ϵ��� ���������� ������ ������
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		//������ ��ü�� �˾Ƽ� �ʿ��Ѱ��� �ִٸ� ����
		((CTile*)vecTile[i])->Save(pFile);
	}

	//���� ����� �ݱ�
	fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";//� ���ڵ� �����ϰ�, � Ȯ���ڵ� ������
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathManager::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = CPathManager::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}
}




// ======================
// Tile Count Window Proc
// ======================
INT_PTR CALLBACK TileCoundProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)//�Լ� ȣ�� �Ծ�
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = CSceneManager::GetInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
