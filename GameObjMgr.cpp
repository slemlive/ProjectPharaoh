#include "DXUT.h"
#include "Home.h"


CGameObjMgr* CGameObjMgr::m_pGameObjMgr;

CGameObjMgr::CGameObjMgr(void)
{
	m_pGameObjMgr = NULL;
}


CGameObjMgr::~CGameObjMgr(void)
{
}

CGameObj* CGameObjMgr::Alloc( int iType )
{
	switch( iType )
	{
	case EGAMEOBJ_CLEAR : return new CGameObj;
	case EGAMEOBJ_PUZZLE : return new CPuzzle;
	}

	return NULL;
}

void CGameObjMgr::OnFrameMove( float fElapsedTime )
{	
	PostProcess();
	CollisionCheck();
	ClickCheck();

	for each( map< int, vector< CGameObj* >>::const_reference mr in m_mapObj )
	{
		OnFrameMove( mr.second, fElapsedTime );
	}
}

void CGameObjMgr::OnFrameRender()
{
	for( int i = 0; i <= 10; ++i )
	{
		map< int, vector< CGameObj* >>::const_iterator mit = m_mapRenderObj.find( i );
		if( mit != m_mapRenderObj.end() )
		{
			D_SPRITE->OnBegin();
			OnFrameRender( mit->second );
			D_SPRITE->OnEnd();
		}
	}
}

void CGameObjMgr::OnFrameMove( const vector< CGameObj* >& vecObj, float fElapsedTime )
{
	for each( vector< CGameObj* >::const_reference vr in vecObj )
	{
		vr->OnFrameMove( fElapsedTime );
	}
}

void CGameObjMgr::OnFrameRender( const vector< CGameObj* >& vecObj )
{
	for each( vector< CGameObj* >::const_reference vr in vecObj )
	{
		vr->OnFrameRender();
	}
}