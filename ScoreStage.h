
#pragma once

class CScoreStage : public CStage
{
private:
	CFontUI* pFont;

public:
	CScoreStage();
	virtual ~CScoreStage();

	virtual void StartStage();
	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();
	virtual void EndStage();
};