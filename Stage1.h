
#pragma once

class CStage1 : public CGameStage
{
private:
	CGameObj* m_pBack;
	CGameObj* m_pTimmer;
	CGameObj* m_pBomb;
	CGameObj* m_pCombo;

	CGameObj* m_pReady;
	CGameObj* m_pEnd;

	CGameObj* m_pEndMenu;
	CGameObj* m_pReStart;
	CGameObj* m_pExit;

	float m_fEndTime;
	float m_fStartTime;

public:
	CStage1();
	virtual ~CStage1();

	virtual void StartStage();
	virtual void OnFrameMove( float fElapsedTime );
	virtual void EndStage();
	virtual void OnFrameRender();
};