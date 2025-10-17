#pragma once

class CCamera
{
private:
	static CCamera* m_pCamera;

private:
	D3DXVECTOR2 m_vPos;
	CGameObj* m_pGameObj;

	int m_iWidth;
	int m_iHeight;

	float m_fSpeed;
	bool m_bFixed;

public:
	CCamera(void);
	virtual ~CCamera(void);

	static CCamera* GetCamera() { if( m_pCamera == NULL ) m_pCamera = new CCamera; return m_pCamera; }

	D3DXVECTOR2 GetPos() { return m_vPos; }
	void SetPos( D3DXVECTOR2 vPos ) { m_vPos = vPos; }

	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }

	void InitSize( int iWIdth, int iHeight );

	bool IsFixed() { return m_bFixed; }
	void SetFixed( bool bFixed ) { m_bFixed = bFixed; }

	void GetTransform( D3DXMATRIX* pmatTrans );
	
	void OnFrameMove( float fElapsedTime );
};

