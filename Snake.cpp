
#include "DXUT.h"
#include "NameSpace.h"

CSnake::CSnake()
{
	AddState(AT_NORMAL, "SnakeNormal");
	AddState(AT_MOVE, "SnakeMove");
	AddState(AT_ATTACK, "SnakeAttack");
	AddState(AT_DIE, "SnakeDie");
	m_iDmg = 5;
	m_iHp = 20;
	m_iMaxHp = 20;
	AddAttackIndex(AT_ATTACK, 6);
	m_fSpeed = 200.0f;
	m_fRad = 200.0f;
	m_fAttackDist = 300.0f;
	m_fAttackSpeed = 3.0f;
	ChangeState(AT_NORMAL);
	m_iPoint = 300;
}

CSnake::~CSnake()
{
	int iRand = rand() & 10;
	if (iRand >= 5)
		D_PROCESSMGR->CreateObj(EGAMEOBJ_ITEM, "ShieldItem", m_vPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}