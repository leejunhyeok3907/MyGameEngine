#pragma once

class CObject;

class CComponent
{
private:
	CObject* m_pOwner;

public:
	virtual void update();
	virtual void render();

	CObject* GetOwner() { return m_pOwner; }

public:
	CComponent() = delete;
	CComponent(COMPONENT_TYPE _comp);

	virtual ~CComponent();


};

