#include "DXUT.h"
#include "Home.h"

CSprite* CSprite::m_pSprite;

CSprite::CSprite(void):
m_pD3DSprite( NULL )
{
	m_pSprite = NULL;
}


CSprite::~CSprite(void)
{
	SAFE_DELETE( m_pD3DSprite );
}

void CSprite::OnResetDevice()
{
	D3DXCreateSprite( DXUTGetD3D9Device(), &m_pD3DSprite );
}

void CSprite::OnLostDevice()
{
	SAFE_RELEASE( m_pD3DSprite );
}

void CSprite::OnBegin()
{
	if( m_pD3DSprite == NULL )
		return ;

	m_pD3DSprite->Begin( D3DXSPRITE_ALPHABLEND );
}

void CSprite::OnEnd()
{
	if( m_pD3DSprite == NULL )
		return ;

	m_pD3DSprite->End();
}

void CSprite::SetTransform( D3DXMATRIX* pmatTrans )
{
	if( m_pD3DSprite == NULL )
		return ;

	m_pD3DSprite->SetTransform( pmatTrans );
}

void CSprite::OnDraw( LPDIRECT3DTEXTURE9 pTexture
	, const RECT* pRect
	, float fX
	, float fY
	, D3DXCOLOR pColor )
{
	D3DXVECTOR3 vPos( fX, fY, 0.0f );
	m_pD3DSprite->Draw( pTexture, pRect, NULL, &vPos, pColor );
}
