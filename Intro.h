
#pragma once

class CIntro : public CGameStage
{
private:
	CGameObj* m_pIntro;
	float m_fTime;

public:
	CIntro();
	virtual ~CIntro();

	virtual void StartStage();
	virtual void OnFrameMove( float fElapsedTime );
	virtual void EndStage();
	virtual void OnFrameRender();
};