
#pragma once

class CSprite : public CSingleton< CSprite >
{
private:
	friend CSingleton< CSprite >;

private:
	LPD3DXSPRITE m_pD3DSprite;

protected:
	CSprite();
	virtual ~CSprite();

public:
	LPD3DXSPRITE GetD3DSprite() { return m_pD3DSprite; }

	void InitSprite();
	void ReleaseSprite();

	void Begin();
	void End();

	void SetTransform(D3DXMATRIX* pmatTrans);
	void Draw(LPDIRECT3DTEXTURE9 pTexture,
		const RECT* pRect,
		float fX,
		float fY,
		D3DXCOLOR pColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
};