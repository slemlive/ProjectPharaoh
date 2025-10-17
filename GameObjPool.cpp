#include "DXUT.h"
#include "Home.h"

CGameObjPool* CGameObjPool::m_pGameObjPool;

CGameObjPool::CGameObjPool(void)
{
	m_pGameObjPool = NULL;
}


CGameObjPool::~CGameObjPool(void)
{
}

void CGameObjPool::LoadRank()
{
	for( int i = 1; ; ++i )
	{
		wstringstream osScore;
		osScore << i;
		int iScore = GetPrivateProfileInt( L"Rank", osScore.str().c_str(), -1, L"Data/Data.ini" );

		if( iScore == -1 )
			break;

		m_vecRank.push_back( iScore );
	}
}

void CGameObjPool::SaveRank()
{
	for( int i = 0; i < (int)m_vecRank.size(); ++i )
	{
		wstringstream osRank;
		osRank << i + 1;

		wstringstream osScore;
		osScore << m_vecRank[i];

		WritePrivateProfileString( L"Rank", osRank.str().c_str(), osScore.str().c_str(), L"Data/Data.ini" );
	}
}

void CGameObjPool::LoadSprite( wstring wsSpriteName, wstring wsFile, wstring wsFileType, int iImgCount, float fTrackSpeed, bool bLoop )
{
	SSpriteData sSpriteData;
	sSpriteData.m_wsName = wsSpriteName;
	sSpriteData.m_iImgCount = iImgCount;
	sSpriteData.m_bLoop = bLoop;
	sSpriteData.m_fTrackSpeed = fTrackSpeed;

	for( int i = 0; i < iImgCount; ++i )
	{
		wstringstream os;
		os << wsFile << i << wsFileType;

		sSpriteData.m_vecTexture.push_back( D_TEXTURE->Load( os.str().c_str() ) );
	}

	m_mapSpriteData.insert( make_pair( wsSpriteName, sSpriteData ));
}

SSpriteData* CGameObjPool::GetSpriteData( wstring wsName )
{
	map< wstring, SSpriteData >::iterator mit = m_mapSpriteData.find( wsName );
	if( mit == m_mapSpriteData.end() )
		return NULL;

	return &mit->second;
}