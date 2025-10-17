
#include "DXUT.h"
#include "NameSpace.h"

CScorpion::CScorpion()
{
	AddState(AT_NORMAL, "ScorpionNormal");
	AddState(AT_MOVE, "ScorpionMove");
	AddState(AT_ATTACK, "ScorpionAttack");
	AddState(AT_DIE, "ScorpionDie");
	m_iDmg = 10;
	m_iHp = 5;
	m_iMaxHp = 5;
	AddAttackIndex(AT_ATTACK, 6);
	m_fSpeed = 180.0f;
	m_fRad = 100.0f;
	m_fAttackDist = 100.0f;
	m_fAttackSpeed = 1.0f;
	ChangeState(AT_NORMAL);
	m_iPoint = 150;
}

CScorpion::~CScorpion()
{
	int iRand = rand() & 10;
	if (iRand >= 5)
		D_PROCESSMGR->CreateObj(EGAMEOBJ_ITEM, "RopeItem", m_vPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}