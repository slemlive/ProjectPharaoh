
#include "DXUT.h"
#include "NameSpace.h"

CBoss::CBoss()
{
	AddState(AT_NORMAL, "BossNormal");
	AddState(AT_MOVE, "BossMove");
	AddState(AT_SKILL, "BossSkill");
	AddState(AT_ATTACK, "BossAttack");
	AddState(AT_DIE, "BossDie");
	m_iDmg = 10;
	m_iHp = 300;
	m_iMaxHp = 300;
	AddAttackIndex(AT_ATTACK, 6);
	m_fSpeed = 200.0f;
	m_fRad = 100.0f;
	m_fAttackDist = 100.0f;
	m_fAttackSpeed = 1.0f;
	ChangeState(AT_NORMAL);
	m_iPoint = 5000;
}

CBoss::~CBoss()
{
}

void CBoss::OnFrameMove(float fElapsedTime)
{
	CUnit::OnFrameMove(fElapsedTime);
}

void CBoss::OnFrameRender(D3DXMATRIX* pmatLocal)
{
	CUnit::OnFrameRender(pmatLocal);
}