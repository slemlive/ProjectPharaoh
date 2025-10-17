#include "DXUT.h"
#include "Home.h"

CTexture* CTexture::m_pTexture;

CTexture::CTexture(void):
m_iTexture( -1 )
{ 
	m_pTexture = NULL;
}


CTexture::~CTexture(void)
{
	ReleaseAll();
	m_pTexture = NULL;
}

int CTexture::Load( const wstring wsFile )
{
	map< wstring, STextureInfo* >::iterator mit = m_mapRefInfo.find( wsFile );
	if( mit != m_mapRefInfo.end() )
	{
		++mit->second->m_iRefCount;

		return mit->second->m_iTexture;
	}

	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO TextureInfo ;

	if( D3DXCreateTextureFromFileEx( DXUTGetD3D9Device()
		, wsFile.c_str()
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1
		, 0
		, D3DFMT_A8R8G8B8
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE
		, D3DX_FILTER_NONE
		, 0
		, &TextureInfo
		, NULL
		, &pTexture ) != S_OK  )
		return -1;

	++m_iTexture;

	STextureInfo* pTextureInfo = new STextureInfo;
	pTextureInfo->m_iTexture = m_iTexture;
	pTextureInfo->m_wsFile = wsFile;
	pTextureInfo->m_pTexture = pTexture;
	pTextureInfo->m_TextureInfo = TextureInfo;

	m_mapTextureInfo.insert( make_pair( m_iTexture, pTextureInfo ));
	m_mapRefInfo.insert( make_pair( wsFile, pTextureInfo ));

	return m_iTexture;
}

const STextureInfo* CTexture::GetTextureInfo( int iTexture )
{
	map< int, STextureInfo* >::iterator mit = m_mapTextureInfo.find( iTexture );
	if( mit == m_mapTextureInfo.end() )
		return NULL;

	return mit->second;
}

const STextureInfo* CTexture::GetTextureInfo( wstring wsFile )
{
	map< wstring, STextureInfo* >::iterator mit = m_mapRefInfo.find( wsFile );
	if( mit == m_mapRefInfo.end() )
		return NULL;

	return mit->second;
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture( int iTexture )
{
	map< int, STextureInfo* >::iterator mit = m_mapTextureInfo.find( iTexture );
	if( mit == m_mapTextureInfo.end() )
		return NULL;

	return mit->second->m_pTexture;
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture( wstring wsFile )
{
	map< wstring, STextureInfo* >::iterator mit = m_mapRefInfo.find( wsFile );
	if( mit == m_mapRefInfo.end() )
		return NULL;

	return mit->second->m_pTexture;
}

void CTexture::ReleaseAll()
{
	map< int, STextureInfo* >::iterator mit = m_mapTextureInfo.begin();
	while( mit != m_mapTextureInfo.end() )
	{
		SAFE_DELETE( mit->second );

		++mit;
	}
	
	m_mapTextureInfo.clear();
	m_mapRefInfo.clear();
}