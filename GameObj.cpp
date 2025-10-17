
#include "DXUT.h"
#include "NameSpace.h"

CGameObj::CGameObj() :
m_vPos(0.0f, 0.0f, 0.0f),
m_vRot(0.0f, 0.0f, 0.0f),
m_vScl(1.0f, 1.0f, 1.0f),
m_sColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
m_bLoop(false),
m_dwTrackTime( 0 ),
m_dwFrameSpeed( 0 ),
m_iIndex( 0 ),
m_bEndAni( true ),
m_bDestroy( false )
{

}

CGameObj::~CGameObj()
{

}

void CGameObj::AddState(ESTATE eState, string sName)
{
	map< ESTATE, string >::iterator mit = m_mapState.find(eState);
	if (mit != m_mapState.end())
	{
		if (mit->second == sName)
			return;
		else
			m_mapState.erase(mit);
	}

	m_mapState.insert(make_pair(eState, sName));
}

void CGameObj::ChangeState(ESTATE eState)
{
	map< ESTATE, string >::iterator mit = m_mapState.find(eState);
	if (mit == m_mapState.end())
		return;

	const SModelData* pModelData = D_GAMEOBJPOOL->GetModelData(mit->second);
	if (pModelData == NULL)
		return;

	m_eState = eState;

	m_vecMeshContainer = pModelData->m_vecMesh;
	m_vecTexture = pModelData->m_vecTexture;
	m_vecMaterials = pModelData->m_vecMaterials;
	m_dwFrameSpeed = pModelData->m_dwFrameSpeed;
	m_bLoop = pModelData->m_bLoop;
	SetAniIndex(0);
}

void CGameObj::OnFrameMove(float fElapsedTime)
{
	UpdateAni(fElapsedTime);
}

void CGameObj::OnFrameRender(D3DXMATRIX* pmatLocal)
{
	UpdateWorld(pmatLocal);

	Begin();
	DrawObject();
	End();
}

void CGameObj::UpdateWorld(D3DXMATRIX* pmatLocal)
{
	D3DXMATRIX matRot;
	MakeRot(matRot);

	D3DXMATRIX matTrans;
	MakeTrans(matTrans);

	D3DXMATRIX matScale;
	MakeScale(matScale);

	D3DXMATRIX matLocal;
	if (pmatLocal == NULL)
		D3DXMatrixIdentity(&matLocal);
	else
		matLocal = *pmatLocal;

	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld = matLocal * matScale * matRot * matTrans;
	DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &m_matWorld);
}

void CGameObj::MakeRot(D3DXMATRIX& matRot)
{
	D3DXMATRIX matRotX;
	D3DXMatrixIdentity(&matRotX);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_vRot.x));

	D3DXMATRIX matRotY;
	D3DXMatrixIdentity(&matRotY);
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_vRot.y));

	D3DXMATRIX matRotZ;
	D3DXMatrixIdentity(&matRotZ);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_vRot.z));

	D3DXMatrixIdentity(&matRot);
	matRot = matRotX * matRotY * matRotZ;
}

void CGameObj::MakeTrans(D3DXMATRIX& matTrans)
{
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);
}

void CGameObj::MakeScale(D3DXMATRIX& matScale)
{
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixScaling(&matScale, m_vScl.x, m_vScl.y, m_vScl.z);
}

void CGameObj::DrawObject()
{
	if (m_vecMeshContainer.empty())
		return;

	if (!m_vecMaterials.empty())
	{
		for (int i = 0; i < (int)m_vecMaterials.size(); ++i)
		{
			m_vecMaterials[i].Diffuse = m_sColor;
			DXUTGetD3D9Device()->SetMaterial(&m_vecMaterials[i]);
			if (i < (int)m_vecTexture.size())
				DXUTGetD3D9Device()->SetTexture(0, D_TEXTURE->GetTexture(m_vecTexture[i]));
			D_MESH->GetMesh(m_vecMeshContainer[m_iIndex])->DrawSubset(i);
		}
	}
	else
		D_MESH->GetMesh(m_vecMeshContainer[m_iIndex])->DrawSubset(0);
}

void CGameObj::Begin()
{
	DXUTGetD3D9Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
}

void CGameObj::End()
{

}

void CGameObj::UpdateAni(float fElapsedTime)
{
	bool bChange = m_dwTrackTime <= GetTickCount();
	if (bChange)
	{
		int iIndex = m_iIndex + 1;
		if (iIndex >= (int)m_vecMeshContainer.size())
		{
			if (m_bLoop)
				SetAniIndex(0);
			else
			{
				m_bEndAni = true;
				return;
			}
		}
		else
			SetAniIndex(iIndex);
	}
}

void CGameObj::SetAniIndex(int iIndex)
{
	m_iIndex = iIndex;
	m_dwTrackTime = GetTickCount() + m_dwFrameSpeed;
	m_bEndAni = false;
}