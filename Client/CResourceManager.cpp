#include "pch.h"
#include "CResourceManager.h"

#include "CPathManager.h"
#include "CTexture.h"
#include "CSound.h"
#include "CResource.h"

CResourceManager::CResourceManager()
{

}

CResourceManager::~CResourceManager()
{
	Safe_Delete_Map(m_mapTex);
	Safe_Delete_Map(m_mapSound);
}

CTexture* CResourceManager::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);

	if (nullptr == pTex)
	{
		pTex = new CTexture;

		wstring strFilePath = CPathManager::GetInst()->GetContentPath();
		strFilePath += _strRelativePath;

		pTex->Load(strFilePath);
		pTex->SetKey(_strKey);
		pTex->SetRelativePath(_strRelativePath);

		m_mapTex.insert(make_pair(_strKey, pTex));
	}

	return pTex;
}

CTexture* CResourceManager::CreateTexture(const wstring& _strKey, UINT _iwidth, UINT _iheight)
{
	CTexture* pTex = FindTexture(_strKey);

	if (nullptr == pTex)
	{
		pTex = new CTexture;
		pTex->Create(_iwidth, _iheight);
		pTex->SetKey(_strKey);

		m_mapTex.insert(make_pair(_strKey, pTex));
	}

	return pTex;
}

CTexture* CResourceManager::FindTexture(const wstring& _strKey)
{
	map<wstring, CResource*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())//찾지 못했다
	{
		return nullptr;
	}

	return (CTexture*)iter->second;
}

CSound* CResourceManager::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	CSound* pSound = FindSound(_strKey);

	if (nullptr == pSound)
	{
		pSound = new CSound;

		wstring strFilePath = CPathManager::GetInst()->GetContentPath();
		strFilePath += _strRelativePath;

		pSound->Load(strFilePath.c_str());
		pSound->SetKey(_strKey);
		pSound->SetRelativePath(_strRelativePath);

		m_mapSound.insert(make_pair(_strKey, pSound));
	}

	return pSound;
}

CSound* CResourceManager::FindSound(const wstring& _strKey)
{
	map<wstring, CResource*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())//찾지 못했다
	{
		return nullptr;
	}

	return (CSound*)iter->second;
}
