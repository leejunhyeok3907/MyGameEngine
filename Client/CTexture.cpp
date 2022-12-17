#include "pch.h"
#include "CTexture.h"

#include "CCore.h"

void CTexture::Load(const wstring& _strFilePath)
{
	//파일로부터 로딩한 데이터를 비트맵으로 생성
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	//비트맵과 연결할 DC
	m_dc=CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	//비트맵과 DC연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	//비트맵 정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

	assert(m_hBit);

}

void CTexture::Create(UINT _iwidth, UINT _iheight)
{
	HDC maindc = CCore::GetInst()->GetMainDC();

	m_hBit = CreateCompatibleBitmap(maindc, _iwidth, _iheight);
	m_dc = CreateCompatibleDC(maindc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hOldBit);

	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}
