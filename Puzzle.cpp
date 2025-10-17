
#include "DXUT.h"
#include "Home.h"

CPuzzle::CPuzzle():
m_pFruit( NULL ),
m_iKey( 0 ),
m_fAniTime( 0.0f ),
m_iCount( 0 )
{
	m_bClickObj = true;
}

CPuzzle::~CPuzzle()
{
}

void CPuzzle::OnFrameMove( float fElapsedTime )
{
	CGameObj::OnFrameMove( fElapsedTime );

	if( m_wsName != L"¾ÆÀÌÅÛ" && m_wsName != L"ÆøÅº" )
	{
		if( m_pFruit == NULL )
		{
			m_pFruit = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, m_wsName, m_wsName, D3DXVECTOR2( m_vPos.x + ( m_vImgSize.x * 0.5f ), m_vPos.y + ( m_vImgSize.y * 0.5f ) ), 0, false, ERENDER_CENTER, m_iRenderTurn + 1, 0, false );
			m_pFruit->SetColor( D3DXCOLOR( 1.0f, 1.0f, 1.0f, 0.9f ) );
		}
		else
		{
			m_pFruit->SetPos( D3DXVECTOR2( m_vPos.x + ( m_vImgSize.x * 0.5f ), m_vPos.y + ( m_vImgSize.y * 0.5f ) ) );
		}
	}

	D3DXVECTOR2 vPos( D_PUZZLEMGR->GetPuzzlePos().x + ( 64 * (float)m_iKey ), D_PUZZLEMGR->GetPuzzlePos().y - ( 64 * (float)m_iCount ) );
	if( m_vPos.y < vPos.y )
		m_vPos.y += 4.0f;

	if( m_vPos.y > vPos.y )
		m_vPos.y -= 4.0f;

	if( m_vPos.x < vPos.x )
		m_vPos.x += 4.0f;

	if( m_vPos.x > vPos.x )
		m_vPos.x -= 4.0f;
}

void CPuzzle::Destroy()
{
	CGameObj::Destroy();
	if( m_pFruit != NULL )
		m_pFruit->Destroy();
}