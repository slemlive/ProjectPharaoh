
#include "DXUT.h"
#include "NameSpace.h"

CMesh::CMesh() :
m_iMesh(-1)
{

}

CMesh::~CMesh()
{

}

void CMesh::DestroyAll()
{
	for each(map< string, SMeshInfo* >::const_reference mr in m_mapMeshInfo)
	{
		for each(vector< SMeshData* >::const_reference vr in mr.second->m_vecMeshContainer)
			delete vr;
	}

	m_mapMeshInfo.clear();
	m_iMesh = 0;
}

vector< int > CMesh::Load(const string sFile, vector< SAseMesh >& vecAseMesh)
{
	map< string, SMeshInfo* >::iterator mit = m_mapMeshInfo.find(sFile);
	if (mit != m_mapMeshInfo.end())
		return mit->second->GetMeshKey();

	vector< SMeshData* > vecMeshContainer;
	for (int i = 0; i < (int)vecAseMesh.size(); ++i)
	{
		vecMeshContainer.push_back(CreateMesh(vecAseMesh[i]));
	}

	SMeshInfo* pMeshInfo = new SMeshInfo;
	pMeshInfo->m_vecMeshContainer = vecMeshContainer;

	m_mapMeshInfo.insert(make_pair(sFile, pMeshInfo));

	return pMeshInfo->GetMeshKey();
}

SMeshData* CMesh::CreateMesh(SAseMesh& sAseMesh)
{
	vector< SAseTriangle >& vecMesh = sAseMesh.m_vecMesh;

	DWORD dwFaceSize = (DWORD)(vecMesh.size());
	DWORD dwVertexSize = (DWORD)(vecMesh.size() * 3);

	LPD3DXMESH pMesh;
	if (FAILED(D3DXCreateMeshFVF(dwFaceSize, dwVertexSize,
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1,
		DXUTGetD3D9Device(),
		&pMesh)))
		return NULL;

	SAseVertex* pVertex;
	pMesh->LockVertexBuffer(0, (void**)&pVertex);
	for (int i = 0; i < (int)vecMesh.size(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int iIndex = (i * 3) + j;
			pVertex[iIndex] = vecMesh[i].m_vecTriangle[j];
		}
	}
	pMesh->UnlockVertexBuffer();

	DWORD* pIndex;
	pMesh->LockIndexBuffer(0, (void**)&pIndex);
	for (int i = 0; i < (int)dwVertexSize; ++i)
		pIndex[i] = i;
	pMesh->UnlockIndexBuffer();

	DWORD* pSubset;
	pMesh->LockAttributeBuffer(0, &pSubset);
	for (int i = 0; i < (int)dwFaceSize; ++i)
	{
		pSubset[i] = vecMesh[i].m_iMtlID;
	}
	pMesh->UnlockAttributeBuffer();

	DWORD* dwAdj = new DWORD[dwVertexSize];
	pMesh->GenerateAdjacency(0.0f, dwAdj);

	pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE, dwAdj, NULL, NULL, NULL);
	SAFE_DELETE_ARRAY(dwAdj);

	++m_iMesh;

	SMeshData* pMeshData = new SMeshData;
	pMeshData->m_iMesh = m_iMesh;
	pMeshData->m_pMesh = pMesh;

	return pMeshData;
}

const SMeshInfo* CMesh::GetMeshInfo(string sFile)
{
	map< string, SMeshInfo* >::iterator mit = m_mapMeshInfo.find(sFile);
	if (mit == m_mapMeshInfo.end())
		return NULL;

	return mit->second;
}

const SMeshData* CMesh::GetMeshData(int iMesh)
{
	map< string, SMeshInfo* >::iterator mit = m_mapMeshInfo.begin();
	for (mit; mit != m_mapMeshInfo.end(); ++mit)
	{
		for (int i = 0; i < (int)mit->second->m_vecMeshContainer.size(); ++i)
		{
			if (iMesh == mit->second->m_vecMeshContainer[i]->m_iMesh)
				return mit->second->m_vecMeshContainer[i];
		}
	}

	return NULL;
}

LPD3DXMESH CMesh::GetClonMesh(int iMesh)
{
	LPD3DXMESH pMesh = GetMeshData(iMesh)->m_pMesh;
	if (pMesh == NULL)
		return NULL;

	LPD3DXMESH pClonMesh;
	if (FAILED(pMesh->CloneMeshFVF(D3DXMESH_MANAGED,
		pMesh->GetFVF(), DXUTGetD3D9Device(),
		&pClonMesh)))
		return NULL;

	return pClonMesh;
}

LPD3DXMESH CMesh::GetMesh(int iMesh)
{
	const SMeshData* pMeshData = GetMeshData(iMesh);
	if (pMeshData == NULL)
		return NULL;

	return pMeshData->m_pMesh;
}