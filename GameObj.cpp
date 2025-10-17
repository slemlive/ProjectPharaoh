#include "DXUT.h"
#include "Home.h"


CGameObj::CGameObj(void):
	m_vPos( 0.0f, 0.0f ),
	m_vScl( 1.0f, 1.0f ),
	m_vImgSize( 1.0f, 0.0f ),
	m_fAngle( 0.0f ),
	m_iRenderTurn( 0 ),
	m_iRenderType( 0 ),
	m_iState( -1 ),
	m_bClickObj( false ),
	m_bClick( false ),
	m_bDestroy( false ),
	m_bCamera( false ),
	m_iRadius( 0 ),
	m_bCollisionCheck( false )
{
	m_pColor = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
}


CGameObj::~CGameObj(void)
{
}

void CGameObj::AddRenderState( int iState, wstring wsRenderName )
{
	map< int, CRender* >::iterator mit = m_mapRender.find( iState );
	if( mit != m_mapRender.end() )
	{
		SAFE_DELETE( mit->second );
		m_mapRender.erase( mit );
	}

	CRender* pRender = new CRender( this );
	SSpriteData* pData =  D_GAMEOBJPOOL->GetSpriteData( wsRenderName );
	if( pData == NULL )
		return ;

	pRender->Load( pData );

	m_mapRender.insert( make_pair( iState, pRender )); 
}

void CGameObj::OnFrameMove( float fElapsedTime )
{
	map< int, CRender* >::iterator mit = m_mapRender.find( m_iState );
	if( mit == m_mapRender.end() )
		return ;

	mit->second->OnFrameMove( fElapsedTime );
}

void CGameObj::OnFrameRender()
{
	map< int, CRender* >::iterator mit = m_mapRender.find( m_iState );
	if( mit == m_mapRender.end() )
		return ;

	mit->second->OnFrameRender();
}