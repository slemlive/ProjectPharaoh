
#include "DXUT.h"
#include "NameSpace.h"

CParticleSystem::CParticleSystem() :
m_pVertexBuffer(NULL),
m_iTexture(-1),
m_fTrackTime(0.0f),
m_fTrackSpeed(0.0f),
m_bLoop(false),
m_fParticleLife(0.0f),
m_fParticleSpeed(0.0f),
m_fParticleMaxScl(0.0f),
m_ePState(EP_DEFAULT),
m_vScope(2500.0f, 10000.0f, 0.0f),
m_fMinScl( 1.0f )
{
	D3DXMatrixIdentity(&m_matWorld);
}

CParticleSystem::~CParticleSystem()
{
	Release();
}

void CParticleSystem::Release()
{
	SAFE_RELEASE(m_pVertexBuffer);
	list< Particle* >::iterator lit = m_lParticles.begin();
	for (lit; lit != m_lParticles.end(); ++lit)
		SAFE_DELETE(*lit);
	m_lParticles.clear();

	if (!m_quParticlePool.empty())
	{
		for (int i = 0; i < (int)m_quParticlePool.size(); ++i)
		{
			Particle* pParticle = NULL;
			pParticle = m_quParticlePool.front();
			if (pParticle != NULL)
				SAFE_DELETE(pParticle);
		}
	}
}

HRESULT CParticleSystem::InitParticleSystem(string sTexFile, float fTrackTime, float fParticleSpeed
	, float fParticleLife, float fParticleMaxScl, bool bLoop, EPState ePState)
{
	if (FAILED(DXUTGetD3D9Device()->CreateVertexBuffer(6000 * sizeof(COUSTOMVERTEX), D3DUSAGE_WRITEONLY,
		D3DFVF_COUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL)))
	{
		MessageBox(DXUTGetHWND(), L"Not Create VertexBuffer", L"Err", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	m_iTexture = D_TEXTURE->Load(sTexFile);
	if (m_iTexture == -1)
	{
		MessageBox(DXUTGetHWND(), L"Not Find Texture", L"Err", MB_ICONERROR | MB_OK);
		return E_FAIL;
	}

	m_fTrackTime = fTrackTime;
	m_fParticleLife = fParticleLife;
	m_fParticleSpeed = fParticleSpeed;
	m_fParticleMaxScl = fParticleMaxScl;
	m_bLoop = bLoop;
	m_ePState = ePState;

	return S_OK;
}

void CParticleSystem::CreateParticle()
{
	Particle* pParticle = NULL;
	if (!m_quParticlePool.empty())
		pParticle = m_quParticlePool.front();

	if (pParticle != NULL)
		m_quParticlePool.pop();
	else
		pParticle = new Particle;

	pParticle->m_vPos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	pParticle->m_vStartPos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	pParticle->m_fLife = m_fParticleLife;
	pParticle->m_fScl = m_fMinScl;
	pParticle->m_dwColor = m_sColor;
	pParticle->m_fSpeed = m_fParticleSpeed;

	float fDirX = ((float)(rand()&(int)m_vScope.x) - (m_vScope.x * 0.5f));
	float fDirY = ((rand()&(int)m_vScope.y) * 1.0f);
	float fDirZ = ((float)(rand()&(int)m_vScope.z) - (m_vScope.z * 0.5f));
	D3DXVECTOR3 vDir(fDirX, m_vScope.y, fDirZ);
	D3DXVec3Normalize(&vDir, &vDir);
	pParticle->m_vDir = vDir;

	m_lParticles.push_back(pParticle);
}

void CParticleSystem::OnFrameMove(float fElapsedTime)
{
	if (m_ePState == EP_CLEAR)
		return;

	m_fTrackSpeed += fElapsedTime;
	if (m_fTrackSpeed >= m_fTrackTime)
	{
		if (m_bLoop)
			CreateParticle();
		else
		{
			CreateParticle();
			m_ePState = EP_CLEAR;
		}

		m_fTrackSpeed = 0.0f;
	}

	std::list<Particle*>::iterator lit;
	for (lit = m_lParticles.begin(); lit != m_lParticles.end(); ++lit)
	{
		if (!UpdateParticle(fElapsedTime, *lit))
		{
			m_quParticlePool.push(*lit);
			lit = m_lParticles.erase(lit);
		}
	}
}

void CParticleSystem::OnFrameRender(D3DXMATRIX* pmatLocal)
{
	UpdateBuffer();
	Billboard();
	UpdateWorld(pmatLocal);

	DrawPrticleSystem();
}

bool CParticleSystem::UpdateParticle(float fElapsedTime, Particle* pParticle)
{
	pParticle->m_fLife -= fElapsedTime;
	if (pParticle->m_fLife <= 0.0f)
		return false;

	pParticle->m_vPos += (pParticle->m_fSpeed * fElapsedTime) * pParticle->m_vDir;
	pParticle->m_fScl = (m_fMinScl + (1 - (pParticle->m_fLife / m_fParticleLife)) * m_fParticleMaxScl);

	return true;
}

void CParticleSystem::Billboard()
{
	m_vRot.x = D_CAMERA->GetRot()->x;
}

void CParticleSystem::UpdateBuffer()
{
	COUSTOMVERTEX* pVertex;
	if (FAILED(m_pVertexBuffer->Lock(0, sizeof(COUSTOMVERTEX), (void**)&pVertex, 0)))
		return;

	int iIndex = -1;
	list<Particle*>::iterator lit;
	for (lit = m_lParticles.begin(); lit != m_lParticles.end(); ++lit)
	{
		Particle* pParticle = *lit;
		D3DXVECTOR3 vPos = pParticle->m_vPos;
		D3DXCOLOR dwColor = pParticle->m_dwColor;
		float fScl = pParticle->m_fScl;

		D3DXMATRIX matRot;
		MakeRot(matRot);

		pVertex[++iIndex] = { D3DXVECTOR3(( vPos.x - (1.0f * fScl) ), vPos.y + (1.0f * fScl), vPos.z), dwColor, D3DXVECTOR2(0.0f, 0.0f) };
		pVertex[++iIndex] = { D3DXVECTOR3(vPos.x + (1.0f * fScl), vPos.y - (1.0f * fScl), vPos.z), dwColor, D3DXVECTOR2(1.0f, 1.0f) };
		pVertex[++iIndex] = { D3DXVECTOR3(vPos.x - (1.0f * fScl), vPos.y - (1.0f * fScl), vPos.z), dwColor, D3DXVECTOR2(0.0f, 1.0f) };
		pVertex[++iIndex] = { D3DXVECTOR3(vPos.x - (1.0f * fScl), vPos.y + (1.0f * fScl), vPos.z), dwColor, D3DXVECTOR2(0.0f, 0.0f) };
		pVertex[++iIndex] = { D3DXVECTOR3(vPos.x + (1.0f * fScl), vPos.y + (1.0f * fScl), vPos.z), dwColor, D3DXVECTOR2(1.0f, 0.0f) };
		pVertex[++iIndex] = { D3DXVECTOR3(vPos.x + (1.0f * fScl), vPos.y - (1.0f * fScl), vPos.z), dwColor, D3DXVECTOR2(1.0f, 1.0f) };
	}
	m_pVertexBuffer->Unlock();
}

void CParticleSystem::DrawPrticleSystem()
{
	Begin();

	DXUTGetD3D9Device()->SetTexture(0, D_TEXTURE->GetTexture(m_iTexture));
	DXUTGetD3D9Device()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(COUSTOMVERTEX));
	DXUTGetD3D9Device()->SetFVF(D3DFVF_COUSTOMVERTEX);
	DXUTGetD3D9Device()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2 * (int)m_lParticles.size());

	End();
}

void CParticleSystem::Begin()
{
	DXUTGetD3D9Device()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DXUTGetD3D9Device()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DXUTGetD3D9Device()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, FALSE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void CParticleSystem::End()
{
	DXUTGetD3D9Device()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, TRUE);
}