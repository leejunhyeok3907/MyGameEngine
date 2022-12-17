#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
private:
    HDC         m_dc;
    HBITMAP     m_hBit;
    BITMAP      m_bitInfo;

public:
    void Load(const wstring& _strFilePath);
    void Create(UINT _iwidth, UINT _iheight);

    UINT GetWidth() { return m_bitInfo.bmWidth; }
    UINT GetHeight() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_dc; }


private:
    CTexture();
    virtual ~CTexture();

    friend class CResourceManager;
};


