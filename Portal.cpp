
#include "DXUT.h"
#include "NameSpace.h"

CPortal::CPortal():
m_fRad( 300.0f ),
m_bTrue( false )
{

}

CPortal::~CPortal()
{

}

void CPortal::OnFrameMove(float fElapsedTime)
{
	CGameObj::OnFrameMove(fElapsedTime);

	CheckStagePortal();
}

void CPortal::OnFrameRender(D3DXMATRIX* pmatLocal)
{
	CGameObj::OnFrameRender(pmatLocal);
}

void CPortal::CheckStagePortal()
{
	if (m_bTrue)
		return;

	D3DXVECTOR3 vLength = m_vPos - *D_PLAYERCTR->GetPos();
	float fLength = D3DXVec3Length(&vLength);
	if (fLength <= m_fRad)
		m_bTrue = true;
}

void CPortal::Begin()
{
	DXUTGetD3D9Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
}