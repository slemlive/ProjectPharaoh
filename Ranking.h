
#pragma once

class CRanking : public CStage
{
protected:
	CTextureUI* pBack;

public:
	CRanking();
	virtual ~CRanking();

	virtual void StartStage();
	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();
	virtual void EndStage();
};