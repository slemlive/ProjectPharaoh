#pragma once

class CGameObj;

class CGameObjContainer
{
private:
	vector< CGameObj* > m_vecObj;

protected:
	map< int, vector< CGameObj* >> m_mapObj;
	map< int, vector< CGameObj* >> m_mapReserveObj;

	map< int, vector< CGameObj* >> m_mapRenderObj;

	void PostProcess();
	virtual CGameObj* Alloc( int iType ) { return NULL; }
	
public:
	CGameObjContainer(void);
	virtual ~CGameObjContainer(void);

	void DestroyAll();

	void CollisionCheck();
	void ClickCheck();
	CGameObj* CreateObj( int iType, wstring wsName, wstring wsRenderName, D3DXVECTOR2 vPos, float fAngle , bool bCamera, int iRenderType, int iRenderTurn, int iRadius, bool bCollisionCheck );
};

