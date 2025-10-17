
#include "DXUT.h"
#include "NameSpace.h"

CSprite::CSprite():
m_pD3DSprite( NULL )
{

}

CSprite::~CSprite()
{

}

void CSprite::ReleaseSprite()
{
	SAFE_RELEASE(m_pD3DSprite);
}

void CSprite::InitSprite()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &m_pD3DSprite);
}

void CSprite::Begin()
{
	assert(m_pD3DSprite);
	m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CSprite::End()
{
	assert(m_pD3DSprite);
	m_pD3DSprite->End();
}

void CSprite::SetTransform(D3DXMATRIX* pmatTrans)
{
	assert(m_pD3DSprite);
	m_pD3DSprite->SetTransform(pmatTrans);
}

void CSprite::Draw(LPDIRECT3DTEXTURE9 pTexture,
	const RECT* pRect,
	float fX, float fY,
	D3DXCOLOR pColor)
{
	assert(m_pD3DSprite);
	D3DXVECTOR3 vPos(fX, fY, 0.0f);
	m_pD3DSprite->Draw(pTexture, pRect, NULL, &vPos, pColor);
}