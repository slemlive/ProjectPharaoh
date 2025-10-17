
#pragma once

enum EGAMEOBJ
{
	EGAMEOBJ_GAMEOBJ,
	EGAMEOBJ_UNIT,
	EGAMEOBJ_PORTAL,
	EGAMEOBJ_TORCH,
	EGAMEOBJ_ITEM,
};

enum ERENDER
{
	ER_DEFAULT,
	ER_ALPA,
};

class CGameObjContainer
{
protected:
	map< EGAMEOBJ, list< CGameObj* > > m_mapObj;
	map< ERENDER, list< CGameObj* > > m_mapRenderObj;

protected:
	CGameObjContainer();
	virtual ~CGameObjContainer();

public:
	CGameObj* Alloc(EGAMEOBJ eObjType);

	void AddGameObj(EGAMEOBJ eObjType, CGameObj* pObj);
	void AddRenderObj(CGameObj* pObj);
	CGameObj* CreateObj(EGAMEOBJ eObjType, string sData, D3DXVECTOR3 vPos, D3DXVECTOR3 vRot);

	void ClearObj();
	void UpdateObj();

	list< CGameObj* > GetObjList(EGAMEOBJ eObjType) { return m_mapObj[eObjType]; }
};