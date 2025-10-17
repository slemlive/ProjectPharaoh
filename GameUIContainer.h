
#pragma once

class CGameUIContainer
{
protected:
	map< int, list< CGameUI* > > m_mapUI;

protected:
	CGameUIContainer();
	virtual ~CGameUIContainer();

public:
	void AddGameUI(CGameUI* pGameUI);

	CTextureUI* CreateTextureUI(string sData, D3DXVECTOR2 vPos, D3DXVECTOR2 vLocal, float fRot, int iLayer);
	CFontUI* CreateFontUI(string sString, D3DXVECTOR2 vPos, int iFontSize, DWORD dwFormat, int iLayer);

	void UpdateUI();
	void ClearUI();
};