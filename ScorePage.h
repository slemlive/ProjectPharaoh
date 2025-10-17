
#pragma once

class CScorePage : public CGameStage
{
private:
	CGameObj* m_pBack;

public:
	CScorePage();
	virtual ~CScorePage();

	virtual void StartStage();
	virtual void OnFrameMove( float fElapsedTime );
	virtual void EndStage();
	virtual void OnFrameRender();
};