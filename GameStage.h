#pragma once

class CGameStage
{
public:
	CGameStage( void );
	virtual ~CGameStage(void);

	virtual void StartStage() {}
	virtual void OnFrameMove( float fElapsedTime ) {}
	virtual void EndStage() {}
	virtual void OnFrameRender() {}
};

