
#pragma once

class CStage2 : public CStage
{
protected:
	CGameObj* pGround;
	bool m_bAttackButton;
	CTextureUI* pHp;
	CFontUI* pScore;
	CPortal* pPortal;

public:
	CStage2();
	virtual ~CStage2();

	virtual void StartStage();
	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();
	virtual void EndStage();
};