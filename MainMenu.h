
#pragma once

class CMainMenu : public CGameStage
{
private:
	CGameObj* m_pStart;
	CGameObj* m_pReport;
	CGameObj* m_pWay;
	CGameObj* m_pRank;

public:
	CMainMenu();
	virtual ~CMainMenu();

	virtual void StartStage();
	virtual void OnFrameMove( float fElapsedTime );
	virtual void EndStage();
	virtual void OnFrameRender();
};