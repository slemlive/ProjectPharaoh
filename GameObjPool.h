
#pragma once

struct SSpriteData
{
	vector< int > m_vecTexture;
	float m_fTrackSpeed;
	bool m_bLoop;

	SSpriteData() :
		m_fTrackSpeed(0.0f),
		m_bLoop(false)
	{

	}
};

struct SModelData
{
	vector< int > m_vecMesh;
	vector< int > m_vecTexture;
	vector< D3DMATERIAL9 > m_vecMaterials;
	DWORD m_dwFrameSpeed;
	bool m_bLoop;

	SModelData() :
		m_dwFrameSpeed(0),
		m_bLoop(false)
	{

	}
};

struct SSaveData
{
	string sName;
	string sFile;
};

class CGameObjPool : public CSingleton< CGameObjPool >
{
private:
	friend CSingleton< CGameObjPool >;

private:
	map< string, SSpriteData > m_mapSpriteData;
	map< string, SModelData > m_mapModelData;

protected:
	CGameObjPool();
	virtual ~CGameObjPool();

public:
	const SSpriteData* GetSpriteData(const string sName);
	const SModelData* GetModelData(const string sName);

	void CreateMeshData(string sFile, map< string, SAseData* >& mapAseData);
	void LoadMeshToAseData(map< string, SAseData* >& mapAseData);

	void LoadSprite(string sName, string sFile, string sType, int iCount, float fTrackSpeed, bool bLoop);

	void CreateSpriteData(string sFile);
};