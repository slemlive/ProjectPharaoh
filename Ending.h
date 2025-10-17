
#pragma once

class CEnding : public CGameStage
{
private:
	CGameObj* m_pEnding;
	float m_fTime;

public:
	CEnding();
	virtual ~CEnding();

	virtual void StartStage();
	virtual void OnFrameMove( float fElapsedTime );
	virtual void EndStage();
	virtual void OnFrameRender();
};