
#include "DXUT.h"
#include "NameSpace.h"

CSC::CSC()
{
	AddState(AT_NORMAL, "SCNormal");
	AddState(AT_MOVE, "SCMove");
	AddState(AT_ATTACK, "SCAttack");
	AddState(AT_DIE, "SCDie");
	m_iDmg = 25;
	m_iHp = 150;
	m_iMaxHp = 150;
	AddAttackIndex(AT_ATTACK, 6);
	m_fSpeed = 200.0f;
	m_fRad = 300.0f;
	m_fAttackDist = 300.0f;
	m_fAttackSpeed = 5.0f;
	ChangeState(AT_NORMAL);
	m_iPoint = 2000;
}

CSC::~CSC()
{

}

void CSC::OnFrameMove(float fElapsedTime)
{
	CUnit::OnFrameMove(fElapsedTime);
}

void CSC::OnFrameRender(D3DXMATRIX* pmatLocal)
{
	CUnit::OnFrameRender(pmatLocal);
}