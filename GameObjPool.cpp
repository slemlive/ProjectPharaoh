
#include "DXUT.h"
#include "NameSpace.h"

CGameObjPool::CGameObjPool()
{

}

CGameObjPool::~CGameObjPool()
{

}

void CGameObjPool::CreateSpriteData(string sFile)
{
	frstream InFile(sFile);
	if (InFile.fail())
		return;

	SSpriteData sSpriteData;
	ZeroMemory(&sSpriteData, sizeof(SSpriteData));
	string sName;

	string sCommand;
	while (!InFile.eof())
	{
		InFile >> sCommand;

		if (sCommand == "<Sprite>")
			ZeroMemory(&sSpriteData, sizeof(SSpriteData));
		else if (sCommand == "Name:")
			InFile >> sName;
		else if (sCommand == "Speed:")
		{
			float fSpeed;
			InFile >> fSpeed;
			sSpriteData.m_fTrackSpeed = fSpeed;
		}
		else if (sCommand == "Loop:")
		{
			InFile >> sCommand;
			if (sCommand == "true")
				sSpriteData.m_bLoop = true;
			else
				sSpriteData.m_bLoop = false;
		}
		else if (sCommand == "{")
		{
			while (!InFile.eof())
			{
				string sFile = InFile.GetLine();
				if (sFile == "}")
					break;

				sSpriteData.m_vecTexture.push_back(D_TEXTURE->Load(sFile));
			}
		}
		else if (sCommand == "<End>")
			m_mapSpriteData.insert(make_pair(sName, sSpriteData));
	}
}

void CGameObjPool::CreateMeshData(string sFile, map< string, SAseData* >& mapAseData)
{
	frstream InFile(sFile);
	if (InFile.fail())
		return;

	SModelData sModelData;
	ZeroMemory(&sModelData, sizeof(SModelData));

	vector< SSaveData > vecSaveData;
	SSaveData sSaveData;

	string sCommand;
	while (!InFile.eof())
	{
		InFile >> sCommand;
		
		if (sCommand == "<Mesh>")
			ZeroMemory(&sModelData, sizeof(SModelData));
		else if (sCommand == "Name:")
			InFile >> sSaveData.sName;
		else if (sCommand == "Loop:")
		{
			bool bLoop;
			InFile >> bLoop;
			sModelData.m_bLoop = bLoop;
		}
		else if (sCommand == "File:")
		{
			string sFile;
			InFile >> sFile;
			sSaveData.sFile = sFile;
		}
		else if (sCommand == "<End>")
		{
			vecSaveData.push_back(sSaveData);
			m_mapModelData.insert(make_pair(sSaveData.sName, sModelData));
		}
	}

	omp_set_num_threads(4);
#pragma omp parallel for
	for (int i = 0; i < (int)vecSaveData.size(); ++i)
	{
		P_ASE Ase(vecSaveData[i].sFile);
		SAseData* pAseData = NULL;
		Ase.GetAseData(&pAseData);
		if (pAseData == NULL)
			continue;

		mapAseData.insert(make_pair(vecSaveData[i].sName, pAseData));
	}
}

void CGameObjPool::LoadMeshToAseData(map< string, SAseData* >& mapAseData)
{
	map< string, SAseData* >::iterator mit = mapAseData.begin();
	for (mit; mit != mapAseData.end(); ++mit)
	{
		m_mapModelData[mit->first].m_dwFrameSpeed = mit->second->m_dwFrameSpeed;
		m_mapModelData[mit->first].m_vecMesh = D_MESH->Load(mit->first, mit->second->m_vecMeshContainer);
		for (int i = 0; i < (int)mit->second->m_vecMaterials.size(); ++i)
		{
			m_mapModelData[mit->first].m_vecMaterials.push_back(mit->second->m_vecMaterials[i].Mat3D);
			if ((int)mit->second->m_vecMaterials[i].sTextureFileName.length() > 0)
				m_mapModelData[mit->first].m_vecTexture.push_back(D_TEXTURE->Load(mit->second->m_vecMaterials[i].sTextureFileName));
		}
		SAFE_DELETE(mit->second);
	}
}

const SSpriteData* CGameObjPool::GetSpriteData(const string sName)
{
	map< string, SSpriteData >::iterator mit = m_mapSpriteData.find(sName);
	if (mit == m_mapSpriteData.end())
		return NULL;

	return &mit->second;
}

const SModelData* CGameObjPool::GetModelData(const string sName)
{
	map< string, SModelData >::iterator mit = m_mapModelData.find(sName);
	if (mit == m_mapModelData.end())
		return NULL;

	return &mit->second;
}

void CGameObjPool::LoadSprite(string sName, string sFile, string sType, int iCount, float fTrackSpeed, bool bLoop)
{
	map< string, SSpriteData >::iterator mit = m_mapSpriteData.find(sName);
	if (mit != m_mapSpriteData.end())
		return;

	vector< int > vecTexture;
	for (int i = 0; i < iCount; ++i)
	{
		stringstream os;
		os << sFile << i << sType;
		vecTexture.push_back(D_TEXTURE->Load(os.str()));
	}

	SSpriteData sSpriteData;
	sSpriteData.m_bLoop = bLoop;
	sSpriteData.m_fTrackSpeed = fTrackSpeed;
	sSpriteData.m_vecTexture = vecTexture;

	m_mapSpriteData.insert(make_pair(sName, sSpriteData));
}