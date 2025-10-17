#pragma once

class CSprite
{
private:
	static CSprite* m_pSprite;
	
	LPD3DXSPRITE m_pD3DSprite;

public:
	CSprite(void);
	virtual ~CSprite(void);

	static CSprite* GetSprite() { if( m_pSprite == NULL ) m_pSprite = new CSprite; return m_pSprite; }
	LPD3DXSPRITE GetD3DSprite() { return m_pD3DSprite; }

	void OnResetDevice();
	void OnLostDevice();

	void OnBegin();
	void OnEnd();

	void SetTransform( D3DXMATRIX* pmatTrans );
	void OnDraw( LPDIRECT3DTEXTURE9 pTexture 
		, const RECT* pRect
		, float fX
		, float fY
		, D3DXCOLOR pColor = 0xffffffff );
};

