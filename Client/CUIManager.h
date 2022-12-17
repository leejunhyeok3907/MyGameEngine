#pragma once
class CUI;

class CUIManager
{
	SINGLE(CUIManager);
private:
	CUI* m_pFocusedUI;//포커싱된 UI


public:
	void update();

	//새 UI가 생성됬을때 포커싱 전환
	void SetTargetedUI(CUI* _pUI);

private:
	//부모 UI내에서 실제로 타겟팅된 UI를 찾아서 반환하는 함수
	CUI* GetTargetedUI(CUI* _pParentUI);

	CUI* GetFocusedUI();
};

