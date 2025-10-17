
#include "DXUT.h"
#include "NameSpace.h"

CMummy::CMummy()
{
	m_iDmg = 8;
	m_iHp = 24;
	m_iMaxHp = 24;
	AddState(AT_NORMAL, "MummyNormal");
	AddState(AT_MOVE, "MummyMove");
	AddState(AT_ATTACK, "MummyAttack");
	AddState(AT_DIE, "MummyDie");
	m_fSpeed = 250.0f;
	m_fRad = 80.0f;
	m_fAttackDist = 80.0f;
	AddAttackIndex(AT_ATTACK, 6);
	m_fAttackSpeed = 3.0f;
	ChangeState(AT_NORMAL);
	m_iPoint = 500;
}

CMummy::~CMummy()
{
	int iRand = rand() & 10;
	if (iRand >= 6)
		D_PROCESSMGR->CreateObj(EGAMEOBJ_ITEM, "SpeedItem", m_vPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	else if (iRand >= 2)
		D_PROCESSMGR->CreateObj(EGAMEOBJ_ITEM, "HpItem", m_vPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}