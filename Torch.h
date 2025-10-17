
#pragma once

class CTorch : public CGameObj
{
protected:
	PSYSTEM* m_pFire;

public:
	CTorch();
	virtual ~CTorch();

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender(D3DXMATRIX* pmatLocal);
};