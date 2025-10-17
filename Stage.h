
#pragma once

class CStage
{
public:
	CStage() {}
	virtual ~CStage() {}

	virtual void StartStage() {}
	virtual void OnFrameMove(float fElapsedTime) {}
	virtual void OnFrameRender() {}
	virtual void EndStage() {}
};