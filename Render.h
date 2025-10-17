#pragma once

enum ERENDERTYPE
{
	ERENDER_LEFTUP,
	ERENDER_UP,
	ERENDER_CENTER,
	ERENDER_UNDER,
};

class CRender
{
protected:
	CGameObj* m_pGameObj;
	D3DXMATRIX m_matWorld;

	vector< int > m_vecTexture;
	int m_iCurIndex;

	float m_fTrackSpeed;
	float m_fTrackTime;

	bool m_bLoop;
	bool m_bEndAni;

protected:
	void MakeRot( D3DXMATRIX& matRot );
	void MakeTrans( D3DXMATRIX& matTrans );
	void MakeScale( D3DXMATRIX& matScale );
	void MakeLocal( D3DXMATRIX& matLocal );

public:
	CRender( CGameObj* pGameObj );
	virtual ~CRender(void);

	void Load( const SSpriteData* pData );

	int GetCurIndex() { return m_iCurIndex; }
	void SetCurIndex( int iIndex );

	bool IsEndAni() { return m_bEndAni; }
	void SetEndAni( bool bUse ) { m_bEndAni = bUse; }

	bool OnFrameMove( float fElapsedTime );
	void OnFrameRender();

	void SetAniIndex( int iIndex );

	virtual void UpdateWorld();
};

