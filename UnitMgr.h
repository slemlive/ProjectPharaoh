
#pragma once

enum EUNIT
{
	EU_SNAKE,
	EU_CAT,
	EU_SCORPION,
	EU_MUMMY,
	EU_SC,
	EU_BOSS,
};

class CUnitMgr : public CSingleton< CUnitMgr >
{
private:
	friend CSingleton< CUnitMgr >;

private:
	vector< CUnit* > m_vecUnit;

protected:
	CUnitMgr();
	virtual ~CUnitMgr();

	CUnit* Alloc(EUNIT eUnit);

public:
	CUnit* CheckTargetUnit(D3DXVECTOR3* vPos);
	void ClearContainer() { m_vecUnit.clear(); };
	void AddUnit(CUnit* pUnit)
	{
		if (pUnit == NULL)
			return;

		if (pUnit->IsDestroy() ||
			pUnit->GetHp() <= 0)
			return;

		m_vecUnit.push_back(pUnit);
	};

	void CollisionCheck();


public:
	CUnit* CreateUnit(EUNIT eUnit, D3DXVECTOR3 vPos, D3DXVECTOR3 vRot);
};