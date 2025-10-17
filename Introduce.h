
#pragma once

class CIntroduce : public CStage
{
protected:
	CTextureUI* pBack;

public:
	CIntroduce();
	virtual ~CIntroduce();

	virtual void StartStage();
	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();
	virtual void EndStage();
};