#pragma once
class CUI;

class CUIManager
{
	SINGLE(CUIManager);
private:
	CUI* m_pFocusedUI;//��Ŀ�̵� UI


public:
	void update();

	//�� UI�� ���������� ��Ŀ�� ��ȯ
	void SetTargetedUI(CUI* _pUI);

private:
	//�θ� UI������ ������ Ÿ���õ� UI�� ã�Ƽ� ��ȯ�ϴ� �Լ�
	CUI* GetTargetedUI(CUI* _pParentUI);

	CUI* GetFocusedUI();
};

