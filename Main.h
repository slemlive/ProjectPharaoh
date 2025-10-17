
#pragma once

class CMain : public CStage
{
protected:
	CTextureUI* m_pPlayButton;
	CTextureUI* m_pIntroduceButton;
	CTextureUI* m_pExplayinButton;
	CTextureUI* m_pRankingButton;

public:
	CMain();
	virtual ~CMain();

	virtual void StartStage();
	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();
	virtual void EndStage();
};