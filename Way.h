
#pragma once

class CWay : public CGameStage
{
private:
	CGameObj* m_pBack;

public:
	CWay();
	virtual ~CWay();

	virtual void StartStage();
	virtual void OnFrameMove( float fElapsedTime );
	virtual void EndStage();
	virtual void OnFrameRender();
};