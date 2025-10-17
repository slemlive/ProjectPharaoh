
#include "DXUT.h"
#include "NameSpace.h"

CCat::CCat()
{
	m_iDmg = 3;
	m_iHp = 15;
	m_iMaxHp = 15;
	AddState(AT_NORMAL, "CatNormal");
	AddState(AT_MOVE, "CatMove");
	AddState(AT_ATTACK, "CatAttack");
	AddState(AT_DIE, "CatDie");
	m_fSpeed = 230.0f;
	m_fRad = 100.0f;
	m_fAttackDist = 100.0f;
	AddAttackIndex(AT_ATTACK, 6);
	m_fAttackSpeed = 2.0f;
	ChangeState(AT_NORMAL);
	m_iPoint = 250;
}

CCat::~CCat()
{
	int iRand = rand() & 10;
	if (iRand >= 5)
		D_PROCESSMGR->CreateObj(EGAMEOBJ_ITEM, "BowItem", m_vPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}