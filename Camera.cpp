
#include "DXUT.h"
#include "NameSpace.h"

CCamera::CCamera() :
m_vLook(0.0f, 0.0f, 0.0f),
m_vAt(0.0f, 0.0f, 0.0f),
m_vLocal(0.0f, 0.0f, 0.0f),
m_vRot(0.0f, 0.0f, 0.0f),
m_fWidth(0.0f),
m_fHeight(0.0f)
{

}

CCamera::~CCamera()
{

}

void CCamera::SetFovProjection()
{
	D3DVIEWPORT9 vp;
	DXUTGetD3D9Device()->GetViewport(&vp);
	
	m_fWidth = (float)vp.Width;
	m_fHeight = (float)vp.Height;

	float fAsp = m_fWidth / m_fHeight;
	float fFov = D3DX_PI / 4.0f;
	D3DXMATRIX matProj;
	D3DXMatrixIdentity(&matProj);

	D3DXMatrixPerspectiveFovLH(&matProj, fFov, fAsp, 1.0f, 100000.0f);
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CCamera::UpdateView()
{
	D3DXMATRIX matLook;
	D3DXMatrixMakeTrans(matLook, (m_vLook * -1.0f));

	D3DXMATRIX matAt;
	D3DXMatrixMakeRot(matAt, (m_vAt * -1.0f));

	D3DXMATRIX matLocal;
	D3DXMatrixMakeTrans(matLocal, (m_vLocal * -1.0f));

	D3DXMATRIX matRot;
	D3DXMatrixMakeRot(matRot, (m_vRot * -1.0f));

	D3DXMatrixIdentity(&m_matView);
	m_matView = matLook * matAt * matLocal * matRot;
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &m_matView);
}

void CCamera::CursorViewPos()
{
	float fElapsedTime = DXUTGetElapsedTime();

	POINT ptCursor;
	GetCursorPos(&ptCursor);
	ScreenToClient(DXUTGetHWND(), &ptCursor);

	if (ptCursor.x <= 0.0f)
		m_vLook.x -= 1000.0f * fElapsedTime;
	else if (ptCursor.x >= m_fWidth - 1.0f)
		m_vLook.x += 1000.0f * fElapsedTime;

	if (ptCursor.y <= 0.0f)
		m_vLook.z += 1000.0f * fElapsedTime;
	else if (ptCursor.y >= m_fHeight - 1.0f)
		m_vLook.z -= 1000.0f * fElapsedTime;
}