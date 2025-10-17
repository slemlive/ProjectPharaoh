#pragma once

class CNew : public CStage
{
public:
	virtual void StartStage();
	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();
	virtual void EndStage();
};