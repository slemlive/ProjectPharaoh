
#include "DXUT.h"
#include "NameSpace.h"

CPlayer::CPlayer():
m_bBow( false ),
m_iRopeCount( 0 ),
m_iTrapCount( 0 ),
m_bRope(false)
{
	AddState(AT_NORMAL, "PlayerNormal");
	AddState(AT_MOVE, "PlayerMove");
	AddState(AT_ATTACK, "PlayerAttack");
	AddState(AT_DIE, "PlayerDie");
	ChangeState(AT_NORMAL);
	AddAttackIndex(AT_ATTACK, 12);

	InitPlayerInfo();
}

CPlayer::~CPlayer()
{

}

void CPlayer::OnFrameMove(float fElapsedTime)
{
	CUnit::OnFrameMove(fElapsedTime);
}

void CPlayer::OnFrameRender(D3DXMATRIX* pmatLocal)
{
	CUnit::OnFrameRender(pmatLocal);
}

void CPlayer::InitPlayerInfo()
{
	m_iDmg = 10;
	m_fAttackDist = 100.0f;
	m_fAttackSpeed = 0.5f;
	m_fRad = 100.0f;
	m_fSpeed = 500.0f;
	m_iHp = 100;
	m_iMaxHp = 100;
	SetTargetPos(m_vPos);
	SetTargetUnit(NULL);
	m_bDestroy = false;
	m_sColor.a = 1.0f;
}

void CPlayer::ChangeAttack()
{
	if (m_bBow)
	{
		m_fAttackDist = 500.0f;
		return AddState(AT_ATTACK, "PlayerBow");
	}
	else
	{
		m_fAttackDist = 100.0f;
		return AddState(AT_ATTACK, "PlayerAttack");
	}
}