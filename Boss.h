
#pragma once

class CBoss : public CUnit
{
public:
	CBoss();
	virtual ~CBoss();

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender(D3DXMATRIX* pmatLocal);
};