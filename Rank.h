
#pragma once

class CRank : public CGameStage
{
private:
	CGameObj* m_pBack;

public:
	CRank();
	virtual ~CRank();

	virtual void StartStage();
	virtual void OnFrameMove( float fElapsedTime );
	virtual void EndStage();
	virtual void OnFrameRender();
};