#pragma once

class CResource;
class CTexture;
class CSound;

class CResourceManager
{
	SINGLE(CResourceManager)

private:
	map<wstring, CResource*> m_mapTex;
	map<wstring, CResource*> m_mapSound;


public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* CreateTexture(const wstring& _strKey, UINT _iwidth, UINT _iheight);
	CTexture* FindTexture(const wstring& _strKey);

public:
	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
	CSound* FindSound(const wstring& _strKey);
};

