
#pragma once

class CIntro : public CStage
{
private:
	CTextureUI* pIntro;

public:
	CIntro();
	virtual ~CIntro();

	virtual void StartStage();
	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();
	virtual void EndStage();
};