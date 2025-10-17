
#pragma once

class CTextureUI : public CGameUI
{
protected:
	D3DXVECTOR2 m_vScl;
	D3DXVECTOR2 m_vImgSize;
	D3DXVECTOR2 m_vLocal;
	float m_fRot;

protected:
	D3DXMATRIX m_matWorld;

	vector< int > m_vecTexture;
	int m_iIndex;

	float m_fTrackTime;
	float m_fTrackSpeed;

	bool m_bLoop;
	bool m_bEndAni;

private:
	void MakeRot(D3DXMATRIX& matRot);
	void MakeTrans(D3DXMATRIX& matTrans);
	void MakeScl(D3DXMATRIX& matScl);
	void MakeLocal(D3DXMATRIX& matLocal);

public:
	CTextureUI();
	virtual ~CTextureUI();

	void Load(const string sData);

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();

protected:
	void UpdateAni(float fElapsedTime);
	void UpdateWorld(D3DXMATRIX* pmatLocal);
	void DrawTexture();

	void SetAniIndex(int iIndex);

public:
	D3DXVECTOR2* GetScl() { return &m_vScl; }
	D3DXVECTOR2* GetLocal() { return &m_vLocal; }
	D3DXVECTOR2* GetImgSize() { return &m_vImgSize; }

	float* GetRot() { return &m_fRot; }
	bool IsEndAni() { return m_bEndAni; }
};