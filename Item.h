
#pragma once

class CItem : public CGameObj
{
public:
	CItem();
	virtual ~CItem();

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender(D3DXMATRIX* pmatLocal);
};