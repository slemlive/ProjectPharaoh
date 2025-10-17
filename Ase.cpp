
#include "DXUT.h"
#include "NameSpace.h"

CAseParser::CAseParser():
m_dwFrameSpeed( 0 )
{

}

CAseParser::CAseParser(const string& sFile):
InFile( sFile ),
m_dwFrameSpeed( 0 )
{
	ReadFile();
}

CAseParser::~CAseParser()
{
	Release();
}

void CAseParser::Release()
{
	InFile.Release();
	m_vecMaterials.clear();
	m_vecMeshContainer.clear();
	m_dwFrameSpeed = 0;
}

void CAseParser::ReadFile()
{
	while (!InFile.eof())
	{
		InFile >> sCommand;

		if (sCommand == "*MATERIAL")
			AddMaterials();
		else if (sCommand == "*GEOMOBJECT")
			AddGeomObject();
		else if (sCommand == "*SCENE_FRAMESPEED")
			InFile >> m_dwFrameSpeed;
	}
}

void CAseParser::InitFile(const string& sFile)
{
	InFile.open(sFile);
	if (InFile.fail())
		return;
}

void CAseParser::AddMaterials()
{
	SAseMaterial sMaterial;
	ZeroMemory(&sMaterial, sizeof(SAseMaterial));

	while (!InFile.eof())
	{
		InFile >> sCommand;

		if (sCommand == "*MATERIAL_AMBIENT")
		{
			float r, g, b;
			InFile >> r >> g >> b;
			sMaterial.Mat3D.Ambient = D3DXCOLOR(r, g, b, 1.0f);
		}
		else if (sCommand == "*MATERIAL_DIFFUSE")
		{
			float r, g, b;
			InFile >> r >> g >> b;
			sMaterial.Mat3D.Diffuse = D3DXCOLOR(r, g, b, 1.0f);
		}
		else if (sCommand == "*MATERIAL_SPECULAR")
		{
			float r, g, b;
			InFile >> r >> g >> b;
			sMaterial.Mat3D.Specular = D3DXCOLOR(r, g, b, 1.0f);
		}
		else if (sCommand == "*BITMAP")
		{
			string sTextureFileName = InFile.GetLine();
			sTextureFileName.erase(sTextureFileName.begin());
			sTextureFileName.pop_back();
			sMaterial.sTextureFileName = sTextureFileName;

			m_vecMaterials.push_back(sMaterial);
			return;
		}
		else if (sCommand == "*MATERIAL_XP_TYPE")
		{
			InFile.Continue();
			InFile >> sCommand;

			if (sCommand != "*MAP_DIFFUSE")
			{
				m_vecMaterials.push_back(sMaterial);
				return;
			}
		}
		else if (sCommand == "*NUMSUBMTLS")
		{
			int iCount;
			InFile >> iCount;

			for (int i = 0; i < iCount; ++i)
			{
				AddMaterials();
			}
			return;
		}
	}
}

void CAseParser::AddGeomObject()
{
	while (!InFile.eof())
	{
		InFile >> sCommand;

		if (sCommand == "*NODE_NAME")
		{
			if (!CheckNodeName())
				return;
		}
		else if (sCommand == "*MESH")
			AddMeshInfo();
		else if (sCommand == "*MESH_ANIMATION")
			m_vecMeshContainer.clear();
	}
}

bool CAseParser::CheckNodeName()
{
	string sName;
	InFile >> sName;

	int iLength = (int)sName.length();
	for (int i = 0; i < iLength; ++i)
	{
		if (sName == "Bip" || sName == "Bone")
			return false;

		sName.pop_back();
	}

	return true;
}

void CAseParser::AddMeshInfo()
{
	SAseMesh sMesh;
	ZeroMemory(&sMesh, sizeof(SAseMesh));

	vector< D3DXVECTOR3 > vecPos;
	vector< D3DXVECTOR2 > vecUv;

	while (!InFile.eof())
	{
		InFile >> sCommand;

		if (sCommand == "*MESH_NUMVERTEX")
		{
			int iCount;
			InFile >> iCount;
			vecPos.reserve(iCount);
		}
		else if (sCommand == "*MESH_NUMFACES")
		{
			int iCount;
			InFile >> iCount;
			sMesh.m_vecMesh.reserve(iCount);
		}
		else if (sCommand == "*MESH_VERTEX")
		{
			int iCount;
			float x, y, z;
			InFile >> iCount >> x >> y >> z;

			vecPos.push_back(D3DXVECTOR3(x, z, -y));
		}
		else if (sCommand == "*MESH_FACE")
		{
			SAseTriangle sTriangle;
			int iCount, iFace, iMtlID;
			InFile >> iCount;

			for (int i = 0; i < 3; ++i)
			{
				SAseVertex sVertex;
				ZeroMemory(&sVertex, sizeof(SAseVertex));

				InFile >> sCommand >> iFace;

				sVertex.m_vPos = vecPos[iFace];
				sTriangle.m_vecTriangle.push_back(sVertex);
			}

			while (sCommand != "*MESH_MTLID")
			{
				InFile >> sCommand;
				if (sCommand == "*MESH_MTLID")
				{
					InFile >> iMtlID;
					if (m_vecMaterials.size() <= 1)
						iMtlID = 0;
					sTriangle.m_iMtlID = iMtlID;
				}
			}

			sMesh.m_vecMesh.push_back(sTriangle);
		}
		else if (sCommand == "*MESH_NUMTVERTEX")
		{
			int iCount;
			InFile >> iCount;
			vecUv.reserve(iCount);
		}
		else if (sCommand == "*MESH_TVERT")
		{
			int iCount;
			float u, v;
			InFile >> iCount >> u >> v;

			vecUv.push_back(D3DXVECTOR2(u, -v));
		}
		else if (sCommand == "*MESH_TFACE")
		{
			int iCount, iFace;
			InFile >> iCount;

			for (int i = 0; i < 3; ++i)
			{
				InFile >> iFace;
				sMesh.m_vecMesh[iCount].m_vecTriangle[i].m_vUv = vecUv[iFace];
			}
		}
		else if (sCommand == "*MESH_FACENORMAL")
		{
			int iCount, iFace;
			float x, y, z;
			InFile >> iCount;
			InFile.Continue();

			for (int i = 0; i < 3; ++i)
			{
				InFile >> sCommand >> iFace >> x >> y >> z;
				sMesh.m_vecMesh[iCount].m_vecTriangle[i].m_vNormal = D3DXVECTOR3(x, z, -y);
			}

			if (iCount == (int)sMesh.m_vecMesh.size() - 1)
			{
				m_vecMeshContainer.push_back(sMesh);
				return;
			}
		}
	}
}

void CAseParser::GetAseData(SAseData** ppAseData)
{
	if (InFile.fail())
	{
		*ppAseData = NULL;
		return;
	}

	SAseData* pAseData = new SAseData;
	pAseData->m_dwFrameSpeed = m_dwFrameSpeed;
	pAseData->m_vecMaterials = m_vecMaterials;
	pAseData->m_vecMeshContainer = m_vecMeshContainer;

	*ppAseData = pAseData;
}