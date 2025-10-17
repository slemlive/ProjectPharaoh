
#pragma once

struct SAseVertex
{
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vNormal;
	D3DXVECTOR2 m_vUv;
};

struct SAseTriangle
{
	vector< SAseVertex > m_vecTriangle;
	int m_iMtlID;

	SAseTriangle() :
		m_iMtlID(-1)
	{
		m_vecTriangle.reserve(3);
	}
};

struct SAseMesh
{
	vector< SAseTriangle > m_vecMesh;
};

struct SAseMaterial
{
	D3DMATERIAL9 Mat3D;
	string sTextureFileName;
};

struct SAseData
{
	vector< SAseMesh > m_vecMeshContainer;
	vector< SAseMaterial > m_vecMaterials;
	DWORD m_dwFrameSpeed;

	SAseData() :
		m_dwFrameSpeed(0)
	{

	}
};

typedef class CAseParser
{
private:
	frstream InFile;
	string sCommand;

private:
	vector< SAseMesh > m_vecMeshContainer;
	vector< SAseMaterial > m_vecMaterials;
	DWORD m_dwFrameSpeed;

public:
	CAseParser();
	explicit CAseParser(const string& sFile);
	virtual ~CAseParser();

	void InitFile(const string& sFile);
	void Release();

	void ReadFile();
	void GetAseData(SAseData** ppAseData);

private:
	void AddMaterials();
	void AddGeomObject();
	void AddMeshInfo();
	bool CheckNodeName();

}P_ASE;