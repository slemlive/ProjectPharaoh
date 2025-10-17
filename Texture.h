
#pragma once

struct STextureInfo
{
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXIMAGE_INFO m_TextureInfo;
	int m_iTexture;

	STextureInfo() :
		m_pTexture( NULL ),
		m_iTexture(-1)
	{

	}

	~STextureInfo()
	{
		SAFE_RELEASE(m_pTexture);
	}
};

class CTexture : public CSingleton< CTexture >
{
private:
	friend CSingleton< CTexture >;

private:
	map< string, STextureInfo* > m_mapTextureInfo;
	int m_iTexture;

protected:
	CTexture();
	virtual ~CTexture();

public:
	int Load(const string sFile);
	void DestroyAll();

	const STextureInfo* GetTextureInfo(string sFile);
	const STextureInfo* GetTextureInfo(int iTexture);

	LPDIRECT3DTEXTURE9 GetTexture(string sFile);
	LPDIRECT3DTEXTURE9 GetTexture(int iTexture);
};