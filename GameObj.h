
#pragma once

enum ESTATE
{
	AT_NORMAL,
	AT_MOVE,
	AT_ATTACK,
	AT_SKILL,
	AT_DIE,
};

class CGameObj
{
protected:
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vRot;
	D3DXVECTOR3 m_vScl;

	map< ESTATE, string > m_mapState;
	ESTATE m_eState;

	D3DXCOLOR m_sColor;
	bool m_bDestroy;

protected:
	D3DXMATRIX m_matWorld;

	vector< int > m_vecMeshContainer;
	vector< int > m_vecTexture;
	vector< D3DMATERIAL9 > m_vecMaterials;
	DWORD m_dwFrameSpeed;
	bool m_bLoop;

	DWORD m_dwTrackTime;
	int m_iIndex;

	bool m_bEndAni;

public:
	CGameObj();
	virtual ~CGameObj();

	void AddState(ESTATE eState, string sName);
	void ChangeState(ESTATE eState);

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender(D3DXMATRIX* pmatLocal);

public:
	D3DXVECTOR3* GetPos() { return &m_vPos; }
	D3DXVECTOR3* GetRot() { return &m_vRot; }
	D3DXVECTOR3* GetScl() { return &m_vScl; }

	D3DXMATRIX* GetWorld() { return &m_matWorld; }

	bool IsEndAni() { return m_bEndAni; }
	int GetAniIndex() { return m_iIndex; }

	ESTATE GetState() { return m_eState; }
	D3DXCOLOR* GetColor() { return &m_sColor; }

	virtual bool IsAlpa() { if (m_sColor.a >= 1.0f) return false; return true; }
	
	int GetMeshIndex() { return m_vecMeshContainer[m_iIndex]; }

	bool IsDestroy() { return m_bDestroy; }
	virtual void Destroy() { m_bDestroy = true; }
	void SetDestroy(bool bUse) { m_bDestroy = bUse; }

protected:
	void DrawObject();
	void UpdateWorld(D3DXMATRIX* pmatLocal);
	void UpdateAni(float fElapsedTime);

	virtual void Begin();
	virtual void End();

	void SetAniIndex(int iIndex);

protected:
	void MakeRot(D3DXMATRIX& matRot);
	void MakeTrans(D3DXMATRIX& matTrans);
	void MakeScale(D3DXMATRIX& matScale);
};