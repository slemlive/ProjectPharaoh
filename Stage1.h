
#pragma once

class CStage1 : public CStage
{
protected:
	CGameObj* pMap;
	bool m_bAttackButton;
	CTextureUI* pHp;
	CFontUI* pScore;
	CParticleSystem* pSys;
	CFontUI* pMsg;
	CPortal* pPortal;
	CSC* pBoss;

public:
	CStage1();
	virtual ~CStage1();

	virtual void StartStage();
	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();
	virtual void EndStage();
};