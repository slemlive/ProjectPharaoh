
#pragma once

class CLoading : public CStage
{
protected:
	thread* m_thLoadingThread;
	map< string, SAseData* > m_mapAseData;
	bool m_bClear;

public:
	CLoading();
	virtual ~CLoading();
	
	virtual void StartStage();
	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();
	virtual void EndStage();
};