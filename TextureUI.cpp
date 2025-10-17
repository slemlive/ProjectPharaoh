
#include "DXUT.h"
#include "NameSpace.h"

CTextureUI::CTextureUI() :
m_vScl(1.0f, 1.0f),
m_vImgSize(0.0f, 0.0f),
m_vLocal(0.0f, 0.0f),
m_fRot(0.0f)
{

}

CTextureUI::~CTextureUI()
{

}

void CTextureUI::Load(const string sData)
{
	const SSpriteData* pSpriteData = D_GAMEOBJPOOL->GetSpriteData(sData);
	if (pSpriteData == NULL)
		return;

	m_vecTexture = pSpriteData->m_vecTexture;
	m_fTrackSpeed = pSpriteData->m_fTrackSpeed;
	m_bLoop = pSpriteData->m_bLoop;
	SetAniIndex(0);
}

void CTextureUI::SetAniIndex(int iIndex)
{
	m_iIndex = iIndex;
	m_fTrackTime = 0.0f;
	m_bEndAni = false;
}

void CTextureUI::OnFrameMove(float fElapsedTime)
{
	UpdateAni(fElapsedTime);
}

void CTextureUI::OnFrameRender()
{
	UpdateWorld(NULL);

	DrawTexture();
}

void CTextureUI::UpdateAni(float fElapsedTime)
{
	m_fTrackTime += fElapsedTime;
	bool bChange = m_fTrackTime >= m_fTrackSpeed;
	if (bChange)
	{
		int iIndex = m_iIndex + 1;
		if (iIndex >= (int)m_vecTexture.size())
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

void CTextureUI::UpdateWorld(D3DXMATRIX* pmatLocal)
{
	D3DXMATRIX matRot;
	MakeRot(matRot);
	
	D3DXMATRIX matTrans;
	MakeTrans(matTrans);

	D3DXMATRIX matScl;
	MakeScl(matScl);

	D3DXMATRIX matCenter;
	MakeLocal(matCenter);

	D3DXMATRIX matLocal;
	if (pmatLocal == NULL)
		D3DXMatrixIdentity(&matLocal);
	else
		matLocal = *pmatLocal;

	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld = matLocal * matCenter * matScl * matRot * matTrans;
	D_SPRITE->SetTransform(&m_matWorld);
}

void CTextureUI::DrawTexture()
{
	D_SPRITE->Draw(D_TEXTURE->GetTexture(m_vecTexture[m_iIndex]), NULL, 0.0f, 0.0f, m_sColor);
}

void CTextureUI::MakeRot(D3DXMATRIX& matRot)
{
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(m_fRot));
	matRot._13 = 0.0f;
	matRot._23 = 0.0f;
}

void CTextureUI::MakeTrans(D3DXMATRIX& matTrans)
{
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, 0.0f);
}

void CTextureUI::MakeScl(D3DXMATRIX& matScl)
{
	D3DXMatrixIdentity(&matScl);
	D3DXMatrixScaling(&matScl, m_vScl.x, m_vScl.y, 0.0f);
}

void CTextureUI::MakeLocal(D3DXMATRIX& matLocal)
{
	const STextureInfo* pTextureInfo = D_TEXTURE->GetTextureInfo(m_vecTexture[m_iIndex]);
	if (pTextureInfo == NULL)
		return;

	m_vImgSize.x = (float)pTextureInfo->m_TextureInfo.Width;
	m_vImgSize.y = (float)pTextureInfo->m_TextureInfo.Height;

	D3DXVECTOR2 vLocal;
	vLocal.x = m_vImgSize.x * m_vLocal.x;
	vLocal.y = m_vImgSize.y * m_vLocal.y;

	D3DXMatrixIdentity(&matLocal);
	D3DXMatrixTranslation(&matLocal, -vLocal.x, -vLocal.y, 0.0f);
}