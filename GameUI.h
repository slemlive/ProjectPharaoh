
#pragma once

class CGameUI
{
protected:
	D3DXVECTOR2 m_vPos;
	int m_iLayer;
	D3DXCOLOR m_sColor;

	bool m_bDestroy;

public:
	CGameUI();
	virtual ~CGameUI();

	virtual void OnFrameMove(float fElapsedTime) = 0;
	virtual void OnFrameRender() = 0;

public:

	D3DXVECTOR2* GetPos() { return &m_vPos; }
	
	int GetLayer() { return m_iLayer; }
	void SetLayer(int iLayer) { m_iLayer = iLayer; }

	D3DXCOLOR GetColor() { return m_sColor; }
	void SetColor(D3DXCOLOR sColor) { m_sColor = sColor; }

	bool IsDestroy() { return m_bDestroy; }
	virtual void Destroy() { m_bDestroy = true; }
};