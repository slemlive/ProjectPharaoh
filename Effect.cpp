
#include "DXUT.h"
#include "NameSpace.h"

CEffect::CEffect()
{

}

CEffect::~CEffect()
{

}

void CEffect::OnFrameMove(float fElapsedTime)
{
	CGameObj::OnFrameMove(fElapsedTime);
	m_vRot.x = -D_CAMERA->GetRot()->x;

	if (m_bEndAni)
	{
		m_sColor.a -= 0.1f;
		if (m_sColor.a <= 0.0f)
			return Destroy();
	}
}

void CEffect::OnFrameRender(D3DXMATRIX* pmatLocal)
{
	DXUTGetD3D9Device()->SetRenderState(D3DRS_ZENABLE, false);
	CGameObj::OnFrameRender(pmatLocal);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_ZENABLE, true);
}