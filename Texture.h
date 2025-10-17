#pragma once

struct STextureInfo
{
	int m_iTexture;
	int m_iRefCount;
	wstring m_wsFile;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXIMAGE_INFO m_TextureInfo;

	STextureInfo():
	m_iTexture( -1 ),
	m_iRefCount( 0 ),
	m_pTexture( NULL )
	{
	}

	~STextureInfo()
	{
		SAFE_RELEASE( m_pTexture );
	}
};

class CTexture
{
private:
	static CTexture* m_pTexture;

private:
	int m_iTexture;

	map< int, STextureInfo* > m_mapTextureInfo;
	map< wstring, STextureInfo* > m_mapRefInfo;

	vector< int > m_vecReleaseTexture;

public:
	CTexture(void);
	virtual ~CTexture(void);

	int Load( const wstring wsFile );

	static CTexture* GetTexture() { if( m_pTexture == NULL ) m_pTexture = new CTexture; return m_pTexture; }

	const STextureInfo* GetTextureInfo( int iTexture );
	const STextureInfo* GetTextureInfo( wstring wsFile );

	LPDIRECT3DTEXTURE9 GetTexture( int iTexture );
	LPDIRECT3DTEXTURE9 GetTexture( wstring wsFile );

	void ReleaseAll();
};

