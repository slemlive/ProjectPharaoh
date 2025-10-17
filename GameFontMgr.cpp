#include "DXUT.h"
#include "Home.h"

CGameFontMgr* CGameFontMgr::m_pGameFontMgr;


CGameFontMgr::CGameFontMgr(void)
{
	m_pGameFontMgr = NULL;
}


CGameFontMgr::~CGameFontMgr(void)
{
	for each( map< wstring, LPD3DXFONT >::const_reference mr in m_mapFont )
		mr.second->Release();

	m_mapFont.clear();
	m_mapFontData.clear();
}

void CGameFontMgr::CreateFont( wstring wsName, wstring wsStr, D3DXVECTOR2 vPos, int iFontSize, int iFormat, D3DXCOLOR pColor )
{
	SFontData sFontData;
	sFontData.m_iFormat = iFormat;
	sFontData.m_pColor = pColor;
	sFontData.m_iFontSize = iFontSize;
	sFontData.m_wsStatic = wsStr;
	sFontData.m_vPos = vPos;
	
	m_mapFontData.insert( make_pair( wsName, sFontData ));

	LPD3DXFONT pFont;

	if( FAILED( D3DXCreateFont( DXUTGetD3D9Device(),
		iFontSize,
		0,
		FW_BOLD,
		1,
		FALSE,
		HANGUL_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		wsStr.c_str(),
		&pFont )))
	{
		return ;
	}

	m_mapFont.insert( make_pair( wsName, pFont ));
}

void CGameFontMgr::Destroy( wstring wsName )
{
	map< wstring, LPD3DXFONT >::iterator mitFont = m_mapFont.find( wsName );
	if( mitFont != m_mapFont.end() )
	{
		mitFont->second->Release();
		m_mapFont.erase( mitFont );
	}

	map< wstring, SFontData >::iterator mitFontData = m_mapFontData.find( wsName );
	if( mitFontData != m_mapFontData.end() )
		m_mapFontData.erase( mitFontData );
}

void CGameFontMgr::DestroyAll()
{
	map< wstring, LPD3DXFONT > ::iterator mitFont = m_mapFont.begin();
	while( mitFont != m_mapFont.end() )
	{
		mitFont->second->Release();
		++mitFont;
	}

	m_mapFont.clear();
	m_mapFontData.clear();
}

void CGameFontMgr::OnFrameRender()
{
	map< wstring, SFontData >::iterator mit = m_mapFontData.begin();
	for( mit; mit != m_mapFontData.end(); ++mit )
	{
		map< wstring, LPD3DXFONT >::iterator mitFont = m_mapFont.find( mit->first );
		if( mitFont == m_mapFont.end() )
			continue ;

		RECT rcRange = { (LONG)mit->second.m_vPos.x, (LONG)mit->second.m_vPos.y,
			(LONG)( mit->second.m_vPos.x + ( mit->second.m_iFontSize * (int)mit->second.m_wsStatic.size() )), 
			(LONG)( mit->second.m_vPos.y + mit->second.m_iFontSize ) };

		mitFont->second->DrawText( NULL, mit->second.m_wsStatic.c_str(), -1, &rcRange, mit->second.m_iFormat, mit->second.m_pColor );
	}
}

void CGameFontMgr::SetPos( wstring wsName, D3DXVECTOR2 vPos )
{
	map< wstring, SFontData >::iterator mit = m_mapFontData.find( wsName );
	if( mit == m_mapFontData.end() )
		return ;

	mit->second.m_vPos = vPos;
}

void CGameFontMgr::SetStr( wstring wsName, wstring wsStr )
{
	map< wstring, SFontData >::iterator mit = m_mapFontData.find( wsName );
	if( mit == m_mapFontData.end() )
		return;

	mit->second.m_wsStatic = wsStr;
}