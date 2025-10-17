
#pragma once

class CEffect : public CGameObj
{
public:
	CEffect();
	virtual ~CEffect();

	virtual bool IsAlpa() { return true; }

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender(D3DXMATRIX* pmatLocal);
};