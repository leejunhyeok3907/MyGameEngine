#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CCamera.h"

#include "CTimeManager.h"
#include "CPathManager.h"
#include "CResourceManager.h"

void CAnimation::update()
{
	if (m_bFinish) return;

	m_fAccTime += fDT;

	//if (m_vecFrame[m_iCurFrame].fDuration < m_fAccTime)
	//{
	//	m_iCurFrame++;

	//	if (m_vecFrame.size() <= m_iCurFrame)
	//	{
	//		m_iCurFrame = -1;
	//		m_bFinish = true;

	//		return;
	//	}

	//	m_fAccTime = m_fAccTime - m_vecFrame[m_iCurFrame].fDuration;

	//	//m_fAccTime = 0.f;
	//}

	while(m_vecFrame[m_iCurFrame].fDuration <= m_fAccTime)
	{
		m_iCurFrame++;

		if (m_vecFrame.size() <= m_iCurFrame)
		{
			m_iCurFrame = -1;
			m_fAccTime = 0.f;
			m_bFinish = true;

			return;
		}

		m_fAccTime = m_fAccTime - m_vecFrame[m_iCurFrame].fDuration;
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish) return;

	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	vPos += m_vecFrame[m_iCurFrame].vOffset;//Object Position에 Offset만큼 추가 이동 위치

	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc,
		(int)(vPos.x - m_vecFrame[m_iCurFrame].vSlice.x / 2.f),
		(int)(vPos.y  - m_vecFrame[m_iCurFrame].vSlice.y / 2.f),
		(int)(m_vecFrame[m_iCurFrame].vSlice.x),
		(int)(m_vecFrame[m_iCurFrame].vSlice.y),
		m_pTex->GetDC(),
		(int)(m_vecFrame[m_iCurFrame].vLT.x),
		(int)(m_vecFrame[m_iCurFrame].vLT.y),
		(int)(m_vecFrame[m_iCurFrame].vSlice.x),
		(int)(m_vecFrame[m_iCurFrame].vSlice.y),
		RGB(255, 0, 255)
	);

}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrame Frame = {};

	for (UINT i = 0; i < _iFrameCount; i++)
	{
		Frame.fDuration = _fDuration;
		Frame.vSlice = _vSliceSize;
		Frame.vLT = _vLT + _vStep * (float)i;

		m_vecFrame.push_back(Frame);
	}
}

void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathManager::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	assert(pFile);

	//Animation의 이름을 저장 데이터 직렬화(Serialization)
	fprintf(pFile, "[Animation Name]\n");
//	SaveWString(m_strName, pFile);
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	//Animation이 사용하는 텍스쳐
	fprintf(pFile, "[Texture Name]\n");
	strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture Path]\n");
	strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	/*SaveWString(m_pTex->GetKey(), pFile);
	SaveWString(m_pTex->GetRelativePath(), pFile);*/

	//프레임 개수
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d\n", (int)m_vecFrame.size());

	for (size_t i = 0; i < m_vecFrame.size(); i++)
	{
		fprintf(pFile, "[Frame Index]\n");
		fprintf(pFile, "%d\n", (int)i);

		fprintf(pFile, "[Left Top]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrame[i].vLT.x, (int)m_vecFrame[i].vLT.y);

		fprintf(pFile, "[Slice Size]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrame[i].vSlice.x, (int)m_vecFrame[i].vSlice.y);

		fprintf(pFile, "[Offset]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrame[i].vOffset.x, (int)m_vecFrame[i].vOffset.y);

		fprintf(pFile, "[Duration]\n");
		fprintf(pFile, "%f\n", m_vecFrame[i].fDuration);

		fprintf(pFile, "\n\n");
	}

	//size_t iFrameCount = m_vecFrame.size();
	//fwrite(&iFrameCount, sizeof(size_t), 1, pFile);

	//모든 프레임 정보
	//fwrite(m_vecFrame.data(), sizeof(tAnimFrame), iFrameCount, pFile);

	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathManager::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	assert(pFile);

	//Animation의 이름을 읽어온다.
	string str;
	char szBuff[256] = {};
	fScanf(szBuff, pFile);//필드명이 읽힘
	fScanf(szBuff, pFile);
	str = szBuff;
	m_strName = wstring(str.begin(), str.end());

	fScanf(szBuff, pFile);
	fScanf(szBuff, pFile);
	str = szBuff;
	wstring strTexKey = wstring(str.begin(), str.end());

	fScanf(szBuff, pFile);
	fScanf(szBuff, pFile);
	str = szBuff;
	wstring strTexPath = wstring(str.begin(), str.end());
	m_pTex = CResourceManager::GetInst()->LoadTexture(strTexKey, strTexPath);

	fScanf(szBuff, pFile);
	int iFrameCount = 0;
	fscanf_s(pFile, "%d", &iFrameCount);

	tAnimFrame Frame = {};

	for (int i = 0; i < iFrameCount; i++)
	{
		POINT pt = {};

		while (true)
		{
			fScanf(szBuff, pFile);
			
			if (!strcmp("[Frame Index]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
			}
			else if (!strcmp("[Left Top]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				Frame.vLT = pt;
			}
			else if (!strcmp("[Slice Size]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				Frame.vSlice = pt;
			}
			else if (!strcmp("[Offset]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				Frame.vOffset = pt;
			}
			else if (!strcmp("[Duration]", szBuff))
			{
				fscanf_s(pFile, "%f", &Frame.fDuration);
				break;
			}
		}

		m_vecFrame.push_back(Frame);
	}

	fclose(pFile);
}

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrame(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}
