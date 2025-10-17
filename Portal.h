
#pragma once

#include "Stage.h"
#include "GameStageMgr.h"

class CPortal : public CGameObj
{
protected:
	ESTAGE m_eNextStage;
	float m_fRad;

	bool m_bTrue;

public:
	CPortal();
	virtual ~CPortal();

	void CheckStagePortal();

	virtual void Begin();

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender(D3DXMATRIX* pmatLocal);

public:
	void SetNextStage(ESTAGE eStage) { m_eNextStage = eStage; }

	virtual bool IsAlpa() { return true; }
	void SetRad(float fRad) { m_fRad = fRad; }

	bool IsTrue() { return m_bTrue; }
	void SetTrue(bool bTrue) { m_bTrue = bTrue; }
};