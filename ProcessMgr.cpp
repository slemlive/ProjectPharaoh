
#include "DXUT.h"
#include "NameSpace.h"

CProcessMgr::CProcessMgr()
{

}

CProcessMgr::~CProcessMgr()
{

}

void CProcessMgr::FrameMoveObj(float fElapsedTime)
{
	for each(map< EGAMEOBJ, list< CGameObj* > >::const_reference mr in m_mapObj)
	{
		for each(list< CGameObj* >::const_reference lr in mr.second)
			lr->OnFrameMove(fElapsedTime);
	}
}

void CProcessMgr::FrameRenderObj()
{
	for each(map< ERENDER, list< CGameObj* > >::const_reference mr in m_mapRenderObj)
	{
		if (mr.first == ER_ALPA)
			DXUTGetD3D9Device()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		else
			DXUTGetD3D9Device()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

		for each(list< CGameObj* >::const_reference lr in mr.second)
			lr->OnFrameRender(NULL);
	}
}

void CProcessMgr::FrameMoveUI(float fElapsedTime)
{
	for each(map< int, list< CGameUI* > >::const_reference mr in m_mapUI)
	{
		for each(list< CGameUI* >::const_reference lr in mr.second)
			lr->OnFrameMove(fElapsedTime);
	}
}

void CProcessMgr::FrameRenderUI()
{
	D_SPRITE->Begin();
	for each(map< int, list< CGameUI* > >::const_reference mr in m_mapUI)
	{
		for each(list< CGameUI* >::const_reference lr in mr.second)
			lr->OnFrameRender();
	}
	D_SPRITE->End();
}

void CProcessMgr::OnFrameMove(float fElapsedTime)
{
	D_UNITMGR->CollisionCheck();

	FrameMoveUI(fElapsedTime);
	FrameMoveObj(fElapsedTime);
}

void CProcessMgr::OnFrameRender()
{
	FrameRenderObj();
	FrameRenderUI();
}