#pragma once

struct SSpriteData
{
	wstring m_wsName;
	int m_iImgCount;
	vector< int > m_vecTexture;

	bool m_bLoop;

	float m_fTrackSpeed;

	SSpriteData():
		m_iImgCount( 0 ),
		m_bLoop( false ),
		m_fTrackSpeed( 0.0f )
	{
	}
};


class CGameObjPool
{
private:
	static CGameObjPool* m_pGameObjPool;

	map< wstring, SSpriteData > m_mapSpriteData;
	vector< int > m_vecRank;

public:
	CGameObjPool(void);
	virtual ~CGameObjPool(void);

	static CGameObjPool* GetGameObjPool() { if( m_pGameObjPool == NULL ) m_pGameObjPool = new CGameObjPool; return m_pGameObjPool; }

	void LoadRank();
	void SaveRank();
	vector< int > GetRank() { return m_vecRank; }
	void SetRank( vector< int > vecRank ) { m_vecRank = vecRank; }
	void LoadSprite( wstring wsSpriteName, wstring wsFile, wstring wsFileType, int iImgCount, float fTrackSpeed, bool bLoop );
	SSpriteData* GetSpriteData( wstring wsName );
};

 