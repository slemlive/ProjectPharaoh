
#include "DXUT.h"
#include "NameSpace.h"

void Util::D3DXMatrixMakeRot(D3DXMATRIX& matRot, D3DXVECTOR3& vRot)
{
	D3DXMATRIX matRotX;
	D3DXMatrixIdentity(&matRotX);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(vRot.x));

	D3DXMATRIX matRotY;
	D3DXMatrixIdentity(&matRotY);
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(vRot.y));

	D3DXMATRIX matRotZ;
	D3DXMatrixIdentity(&matRotZ);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(vRot.z));

	D3DXMatrixIdentity(&matRot);
	matRot = matRotX * matRotY * matRotZ;
}

void Util::D3DXMatrixMakeTrans(D3DXMATRIX& matTrans, D3DXVECTOR3& vTrans)
{
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixTranslation(&matTrans, vTrans.x, vTrans.y, vTrans.z);
}

RECT Util::GetRect(CTextureUI* pTextureUI)
{
	D3DXVECTOR2 vPos = *pTextureUI->GetPos();
	D3DXVECTOR2 vLocal = *pTextureUI->GetLocal();
	D3DXVECTOR2 vImgSize = *pTextureUI->GetImgSize();

	float fLocalX = vImgSize.x * vLocal.x;
	float fLocalY = vImgSize.y * vLocal.y;

	if (vLocal.x == 0.0f)
		vLocal.x += 1.0f;
	if (vLocal.y == 0.0f)
		vLocal.y += 1.0f;

	float fWorldX = vImgSize.x * vLocal.x;
	float fWorldY = vImgSize.y * vLocal.y;

	float fMinX = vPos.x - fLocalX;
	float fMinY = vPos.y - fLocalY;
	float fMaxX = vPos.x + fWorldX;
	float fMaxY = vPos.y + fWorldY;

	RECT rcRect = { (LONG)fMinX, (LONG)fMinY, (LONG)fMaxX, (LONG)fMaxY };
	return rcRect;
}

LPRAY Util::CreateRay()
{
	LPRAY pRay = new SRay;
	ZeroMemory(pRay, sizeof(SRay));

	POINT ptCursor;
	GetCursorPos(&ptCursor);
	ScreenToClient(DXUTGetHWND(), &ptCursor);

	D3DVIEWPORT9 ViewPort;
	DXUTGetD3D9Device()->GetViewport(&ViewPort);

	float fX = (((2.0f * ptCursor.x) / ViewPort.Width) - 1.0f);
	float fY = (((-2.0f * ptCursor.y) / ViewPort.Height) + 1.0f);
	float fZ = 1.0f;

	D3DXMATRIX matProj;
	DXUTGetD3D9Device()->GetTransform(D3DTS_PROJECTION, &matProj);

	fX = fX / matProj(0, 0);
	fY = fY / matProj(1, 1);

	D3DXMATRIX matView;
	DXUTGetD3D9Device()->GetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIX matInverse;
	D3DXMatrixInverse(&matInverse, NULL, &matView);

	pRay->m_vDir = D3DXVECTOR3(fX, fY, fZ);
	pRay->m_vOri = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVec3TransformCoord(&pRay->m_vOri, &pRay->m_vOri, &matInverse);
	D3DXVec3TransformNormal(&pRay->m_vDir, &pRay->m_vDir, &matInverse);

	return pRay;
}

bool Util::CheckMeshPicking(LPD3DXMESH* ppMesh, D3DXMATRIX* pmatWorld, D3DXVECTOR3* pOut)
{
	if (ppMesh == NULL || pmatWorld == NULL || pOut == NULL)
		return false;

	float fDist = 100000.0f;
	LPD3DXMESH pMesh = *ppMesh;
	LPRAY pRay = CreateRay();
	if (pRay == NULL)
		return false;

	D3DXVECTOR3 vOri;
	D3DXVECTOR3 vDir;
	D3DXMATRIX matInverse;
	D3DXMatrixInverse(&matInverse, NULL, pmatWorld);
	D3DXVec3TransformCoord(&vOri, &pRay->m_vOri, &matInverse);
	D3DXVec3TransformNormal(&vDir, &pRay->m_vDir, &matInverse);

	SAseVertex* pVertex = NULL;
	pMesh->LockVertexBuffer(0, (void**)&pVertex);

	bool bCheck = false;
	DWORD dwFaceSize = (DWORD)pMesh->GetNumFaces();
	for (DWORD i = 0; i < dwFaceSize; ++i)
	{
		int iIndex = i * 3;
		D3DXVECTOR3 v0 = pVertex[iIndex + 0].m_vPos;
		D3DXVECTOR3 v1 = pVertex[iIndex + 1].m_vPos;
		D3DXVECTOR3 v2 = pVertex[iIndex + 2].m_vPos;

		float fThis;
		if (D3DXIntersectTri(&v0, &v1, &v2, &vOri, &vDir, NULL, NULL, &fThis))
		{
			bCheck = true;
			if (fThis <= fDist)
				fDist = fThis;
		}
	}
	*pOut = pRay->m_vOri + pRay->m_vDir * fDist;
	pMesh->UnlockVertexBuffer();
	SAFE_DELETE(pRay);
	SAFE_RELEASE(pMesh);

	return bCheck;
}