
#pragma once

class CReport : public CGameStage
{
private:
	CGameObj* m_pBack;

public:
	CReport();
	virtual ~CReport();

	virtual void StartStage();
	virtual void OnFrameMove( float fElapsedTime );
	virtual void EndStage();
	virtual void OnFrameRender();
};