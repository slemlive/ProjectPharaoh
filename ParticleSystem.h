
#pragma once

#define D3DFVF_COUSTOMVERTEX D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1

enum EPState
{
	EP_DEFAULT,
	EP_RUN,
	EP_PAUSE,
	EP_CLEAR,
};

struct COUSTOMVERTEX
{
	D3DXVECTOR3 vPos;
	DWORD dwColor;
	D3DXVECTOR2 vUv;
};

struct Particle
{
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vDir;
	float m_fScl;
	float m_fSpeed;
	D3DXCOLOR m_dwColor;

	float m_fLife;

	D3DXVECTOR3 m_vStartPos;
};


typedef class CParticleSystem : public CGameObj
{
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	D3DXMATRIX m_matWorld;

	queue<Particle*> m_quParticlePool;
	list<Particle*> m_lParticles;
	int m_iTexture;

protected:
	D3DXVECTOR3 m_vScope;
	EPState m_ePState;

	float m_fTrackTime;
	float m_fTrackSpeed;

	float m_fParticleSpeed;
	float m_fParticleLife;
	float m_fParticleMaxScl;
	float m_fMinScl;

	bool m_bLoop;

public:
	CParticleSystem();
	virtual ~CParticleSystem();

	D3DXVECTOR3* GetPos() { return &m_vPos; }

	HRESULT InitParticleSystem(string sTexFile, float fTrackTime, float fParticleSpeed
		, float fParticleLife, float fParticleMaxScl, bool bLoop = false, EPState ePState = EP_RUN);

	void CreateParticle();

	bool UpdateParticle(float fElapsedTime, Particle* pParticle);
	void UpdateBuffer();

	void Billboard();

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender(D3DXMATRIX* pmatLocal);

	virtual void Begin();
	virtual void End();

	void DrawPrticleSystem();
	virtual bool IsAlpa() { return true; }

	void Release();

}PSYSTEM;