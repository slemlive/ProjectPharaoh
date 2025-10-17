
#pragma once

class CSC : public CUnit
{
public:
	CSC();
	virtual ~CSC();

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender(D3DXMATRIX* pmatLocal);
};