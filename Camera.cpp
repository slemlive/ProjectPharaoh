#include "DXUT.h"
#include "Home.h"

CCamera* CCamera::m_pCamera;

CCamera::CCamera(void):
m_iWidth( 0 ),
	m_iHeight( 0 ),
	m_fSpeed( 300.0f ),
	m_bFixed( false )
{
	m_pCamera = NULL;
}


CCamera::~CCamera(void)
{
}

void CCamera::InitSize( int iWidth, int iHeight )
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;

	m_vPos.x = m_iWidth * 0.5f;
	m_vPos.y = m_iHeight* 0.5f;
}

void CCamera::OnFrameMove( float fElapsedTime )
{
}

void CCamera::GetTransform( D3DXMATRIX* pmatTrans )
{
	pmatTrans->_41 = m_iWidth * 0.5f - m_vPos.x;
	pmatTrans->_42 = m_iHeight * 0.5f - m_vPos.y;
}