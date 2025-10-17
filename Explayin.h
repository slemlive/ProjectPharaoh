
#pragma once

class CExplayin : public CStage
{
protected:
	CTextureUI* pBack;

public:
	CExplayin();
	virtual ~CExplayin();

	virtual void StartStage();
	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();
	virtual void EndStage();
};