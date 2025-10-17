#pragma once

struct SFontData
{
	int m_iFormat;
	int m_iFontSize;
	wstring m_wsStatic;
	D3DXCOLOR m_pColor;
	D3DXVECTOR2 m_vPos;

	SFontData():
	m_iFormat( -1 ),
		m_iFontSize( 0 ),
		m_vPos( 0.0f, 0.0f )
	{
	}
};

class CGameFontMgr
{
private:
	static CGameFontMgr* m_pGameFontMgr;
	
	map< wstring, LPD3DXFONT > m_mapFont;
	map< wstring, SFontData > m_mapFontData;
	
public:
	CGameFontMgr(void);
	virtual ~CGameFontMgr(void);

	static CGameFontMgr* GetFontMgr() { if( m_pGameFontMgr == NULL ) m_pGameFontMgr = new CGameFontMgr; return m_pGameFontMgr; }
	
	void CreateFont( wstring wsName, wstring wsStr, D3DXVECTOR2 vPos, int iFontSize, int iFormat, D3DXCOLOR pColor );
	void SetPos( wstring wsName, D3DXVECTOR2 vPos );
	void SetStr( wstring wsName, wstring wsStr );
	void Destroy( wstring wsName );
	void DestroyAll();

	void OnFrameRender();
};

