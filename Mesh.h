
#pragma once

struct SMeshData
{
	LPD3DXMESH m_pMesh;
	int m_iMesh;

	SMeshData() :
		m_pMesh(NULL),
		m_iMesh(-1)
	{

	}

	~SMeshData()
	{
		SAFE_RELEASE(m_pMesh);
	}
};

struct SMeshInfo
{
	vector< SMeshData* > m_vecMeshContainer;

	vector< int > GetMeshKey()
	{
		vector< int > vecMeshKey;
		for (int i = 0; i < (int)m_vecMeshContainer.size(); ++i)
		{
			vecMeshKey.push_back(m_vecMeshContainer[i]->m_iMesh);
		}

		return vecMeshKey;
	}
};

class CMesh : public CSingleton< CMesh >
{
private:
	friend CSingleton< CMesh >;

private:
	map< string, SMeshInfo* > m_mapMeshInfo;
	int m_iMesh;

protected:
	CMesh();
	virtual ~CMesh();

public:
	vector< int > Load(const string sFile, vector< SAseMesh >& vecAseMesh);
	void DestroyAll();

	const SMeshInfo* GetMeshInfo(string sFile);
	const SMeshData* GetMeshData(int iMesh);

	LPD3DXMESH GetClonMesh(int iMesh);
	LPD3DXMESH GetMesh(int iMesh);

private:
	SMeshData* CreateMesh(SAseMesh& sAseMesh);

};