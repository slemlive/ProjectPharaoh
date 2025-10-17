
#include "DXUT.h"
#include "NameSpace.h"

CTexture::CTexture() :
m_iTexture(-1)
{

}

CTexture::~CTexture()
{

}

void CTexture::DestroyAll()
{
	for each(map< string, STextureInfo* >::const_reference mr in m_mapTextureInfo)
		delete mr.second;

	m_mapTextureInfo.clear();
	m_iTexture = 0;
}

int CTexture::Load(const string sFile)
{
	map< string, STextureInfo* >::iterator mit = m_mapTextureInfo.find(sFile);
	if (mit != m_mapTextureInfo.end())
		return mit->second->m_iTexture;

	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO TextureInfo;

	if (FAILED(D3DXCreateTextureFromFileExA(DXUTGetD3D9Device(),
		sFile.c_str(),
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		0,
		&TextureInfo,
		NULL,
		&pTexture)))
		return -1;

	++m_iTexture;

	STextureInfo* pTextureInfo = new STextureInfo;
	pTextureInfo->m_iTexture = m_iTexture;
	pTextureInfo->m_pTexture = pTexture;
	pTextureInfo->m_TextureInfo = TextureInfo;

	m_mapTextureInfo.insert(make_pair(sFile, pTextureInfo));

	return m_iTexture;
}

const STextureInfo* CTexture::GetTextureInfo(string sFile)
{
	map< string, STextureInfo* >::iterator mit = m_mapTextureInfo.find(sFile);
	if (mit == m_mapTextureInfo.end())
		return NULL;

	return mit->second;
}

const STextureInfo* CTexture::GetTextureInfo(int iTexture)
{
	map< string, STextureInfo* >::iterator mit = m_mapTextureInfo.begin();
	for (mit; mit != m_mapTextureInfo.end(); ++mit)
	{
		if (mit->second->m_iTexture == iTexture)
			return mit->second;
	}

	return NULL;
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture(int iTexture)
{
	map< string, STextureInfo* >::iterator mit = m_mapTextureInfo.begin();
	for (mit; mit != m_mapTextureInfo.end(); ++mit)
	{
		if (mit->second->m_iTexture == iTexture)
			return mit->second->m_pTexture;
	}

	return NULL;
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture(string sFile)
{
	map< string, STextureInfo* >::iterator mit = m_mapTextureInfo.find(sFile);
	if (mit == m_mapTextureInfo.end())
		return NULL;

	return mit->second->m_pTexture;
}