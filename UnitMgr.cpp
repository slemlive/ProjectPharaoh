
#include "DXUT.h"
#include "NameSpace.h"

CUnitMgr::CUnitMgr()
{

}

CUnitMgr::~CUnitMgr()
{

}

CUnit* CUnitMgr::CheckTargetUnit(D3DXVECTOR3* vPos)
{
	for (int i = 0; i < (int)m_vecUnit.size(); ++i)
	{
		if (D_PLAYERCTR == m_vecUnit[i])
			continue;

		if (m_vecUnit[i]->GetHp() <= 0)
			continue;

		LPD3DXMESH pClon = D_MESH->GetClonMesh(m_vecUnit[i]->GetMeshIndex());
		if (pClon == NULL)
			continue;

		D3DXVECTOR3 vLength = *vPos - *m_vecUnit[i]->GetPos();
		float fLength = D3DXVec3Length(&vLength);
		D3DXVECTOR3 vOut;
		if (CheckMeshPicking(&pClon, m_vecUnit[i]->GetWorld(), &vOut) || fLength <= m_vecUnit[i]->GetRad())
			return m_vecUnit[i];
	}

	return NULL;
}

CUnit* CUnitMgr::Alloc(EUNIT eUnit)
{
	switch (eUnit)
	{
	case EU_CAT: return new CCat;
	case EU_MUMMY: return new CMummy;
	case EU_SNAKE: return new CSnake;
	case EU_SCORPION: return new CScorpion;
	case EU_SC: return new CSC;
	case EU_BOSS: return new CBoss;
	}

	return NULL;
}

CUnit* CUnitMgr::CreateUnit(EUNIT eUnit, D3DXVECTOR3 vPos, D3DXVECTOR3 vRot)
{
	CUnit* pUnit = Alloc(eUnit);
	if (pUnit == NULL)
		return NULL;

	*pUnit->GetPos() = vPos;
	*pUnit->GetRot() = vRot;
	D3DXVECTOR3 vHpPos;
	if (eUnit == EU_CAT ||
		eUnit == EU_MUMMY ||
		eUnit == EU_SNAKE)
		vHpPos = D3DXVECTOR3(0.0f, 186.6f, 0.0f);
	else if (eUnit == EU_SC)
		vHpPos = D3DXVECTOR3(0.0f, 466.4f, 0.0f);
	else if (eUnit == EU_SCORPION)
		vHpPos = D3DXVECTOR3(0.0f, 130.6752f, 0.0f);
	else if (eUnit == EU_BOSS)
		vHpPos = D3DXVECTOR3(0.0f, 475.1384f, 0.0f);
	pUnit->SetHpPos(vHpPos);

	D_PROCESSMGR->AddGameObj(EGAMEOBJ_UNIT, pUnit);

	return pUnit;
}

void CUnitMgr::CollisionCheck()
{
	for (int i = 0; i < (int)m_vecUnit.size(); ++i)
	{
		vector< CUnit* >* vecUnit = m_vecUnit[i]->GetCollision();
		vecUnit->clear();

		for (int j = 0; j < (int)m_vecUnit.size(); ++j)
		{
			if (i == j)
				continue;

			D3DXVECTOR3 vLength = *m_vecUnit[j]->GetPos() - *m_vecUnit[i]->GetPos();
			float fLength = D3DXVec3Length(&vLength);
			float fDist = m_vecUnit[i]->GetRad();
			if (fLength < fDist)
				vecUnit->push_back(m_vecUnit[j]);
		}
	}
}