
#include "DXUT.h"
#include "NameSpace.h"

CGameObjContainer::CGameObjContainer()
{

}

CGameObjContainer::~CGameObjContainer()
{

}

void CGameObjContainer::ClearObj()
{
	for each(map< EGAMEOBJ, list< CGameObj* > >::const_reference mr in m_mapObj)
	{
		for each(list< CGameObj* >::const_reference dr in mr.second)
			delete dr;
	}

	m_mapObj.clear();
	m_mapRenderObj.clear();
}

CGameObj* CGameObjContainer::Alloc(EGAMEOBJ eObjType)
{
	switch (eObjType)
	{
	case EGAMEOBJ_GAMEOBJ: return new CGameObj;
	case EGAMEOBJ_UNIT: return new CUnit;
	case EGAMEOBJ_PORTAL: return new CPortal;
	case EGAMEOBJ_TORCH: return new CTorch;
	case EGAMEOBJ_ITEM: return new CItem;
	}

	return NULL;
}

void CGameObjContainer::AddGameObj(EGAMEOBJ eObjType, CGameObj* pObj)
{
	if (pObj == NULL)
		return;

	m_mapObj[eObjType].push_back(pObj);
}

void CGameObjContainer::AddRenderObj(CGameObj* pObj)
{
	if (pObj == NULL)
		return;

	if (pObj->IsAlpa())
		m_mapRenderObj[ER_ALPA].push_back(pObj);
	else
		m_mapRenderObj[ER_DEFAULT].push_back(pObj);
}

CGameObj* CGameObjContainer::CreateObj(EGAMEOBJ eObjType, string sData, D3DXVECTOR3 vPos, D3DXVECTOR3 vRot)
{
	CGameObj* pObj = Alloc(eObjType);
	if (pObj == NULL)
		return NULL;

	*pObj->GetPos() = vPos;
	*pObj->GetRot() = vRot;
	pObj->AddState(AT_NORMAL, sData);
	pObj->ChangeState(AT_NORMAL);

	AddGameObj(eObjType, pObj);
	return pObj;
}

void CGameObjContainer::UpdateObj()
{
	D_UNITMGR->ClearContainer();
	m_mapRenderObj.clear();
	map< EGAMEOBJ, list< CGameObj* > >::iterator mit = m_mapObj.begin();
	while (mit != m_mapObj.end())
	{
		list< CGameObj* >::iterator lit = mit->second.begin();
		for (lit = mit->second.begin(); lit != mit->second.end(); ++lit)
		{
			CGameObj* pObj = *lit;
			if (!pObj->IsDestroy())
			{
				if (pObj->IsAlpa())
					m_mapRenderObj[ER_ALPA].push_back(pObj);
				else
					m_mapRenderObj[ER_DEFAULT].push_back(pObj);

				if (mit->first == EGAMEOBJ_UNIT)
					D_UNITMGR->AddUnit((CUnit*)*lit);

				continue;
			}

			SAFE_DELETE(pObj);
			lit = mit->second.erase(lit);
		}

		if (mit->second.empty())
			mit = m_mapObj.erase(mit);
		else
			++mit;
	}
}