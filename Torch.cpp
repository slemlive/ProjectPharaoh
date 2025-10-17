
#include "DXUT.h"
#include "NameSpace.h"

CTorch::CTorch() :
m_pFire(NULL)
{
	/*m_pFire = new CParticleSystem;
	m_pFire->InitParticleSystem("Texture/Fire.png", 0.1f, 30.0f, 3.0f, 50.0f, true);
	*m_pFire->GetPos() = D3DXVECTOR3(m_vPos.x, m_vPos.y, m_vPos.z + 6.0f);
	D_PROCESSMGR->AddGameObj(EGAMEOBJ_GAMEOBJ, m_pFire);*/
}

CTorch::~CTorch()
{
	if (m_pFire != NULL)
		m_pFire->Destroy();
}

void CTorch::OnFrameMove(float fElapsedTime)
{
	/*if (m_pFire == NULL)
	{
		m_pFire = new CParticleSystem;
		m_pFire->InitParticleSystem("Texture/Fire.png", 0.1f, 30.0f, 3.0f, 50.0f, true);
		*m_pFire->GetPos() = D3DXVECTOR3(m_vPos.x, m_vPos.y, m_vPos.z + 6.0f);
		D_PROCESSMGR->AddGameObj(EGAMEOBJ_GAMEOBJ, m_pFire);
	}
	else
		*m_pFire->GetPos() = D3DXVECTOR3(m_vPos.x, 0.0f, m_vPos.z + 6.0f);*/

	CGameObj::OnFrameMove(fElapsedTime);
}

void CTorch::OnFrameRender(D3DXMATRIX* pmatLocal)
{
	CGameObj::OnFrameRender(pmatLocal);
}