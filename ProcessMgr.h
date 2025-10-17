
#pragma once

class CProcessMgr : public CGameObjContainer,
					public CGameUIContainer,
					public CSingleton< CProcessMgr >
{
private:
	friend CSingleton< CProcessMgr >;

protected:
	CProcessMgr();
	virtual ~CProcessMgr();

private:
	void FrameMoveObj(float fElapsedTime);
	void FrameRenderObj();

	void FrameMoveUI(float fElapsedTime);
	void FrameRenderUI();

public:
	void OnFrameMove(float fElapsedTime);
	void OnFrameRender();
};