
#pragma once

class CEnding : public CStage
{
protected:
	CTextureUI* pEnding;

public:
	CEnding();
	virtual ~CEnding();

	virtual void StartStage();
	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();
	virtual void EndStage();
};