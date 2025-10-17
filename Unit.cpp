
#include "DXUT.h"
#include "NameSpace.h"

CUnit::CUnit():
m_fSpeed( 0.0f ),
m_vTargetPos( 0.0f, 0.0f, 0.0f ),
m_iHp( 0 ),
m_iMaxHp( 0 ),
m_iDmg( 0 ),
m_bAttackCheck( false ),
m_pTarget( NULL ),
m_fAttackTime( 0.0f ),
m_fAttackSpeed( 0.0f ),
m_fAttackDist( 0.0f ),
m_iPoint( 0 ),
m_fRad( 0.0f ),
m_pHp( NULL ),
m_bGodMode( false ),
m_bHold( false ),
m_fHoldSpeed( 0.0f ),
m_fHoldTime( 0.0f )
{

}

CUnit::~CUnit()
{
}

void CUnit::UpdateState()
{
	switch (m_eState)
	{
	case AT_NORMAL: return OnNormal();
	case AT_MOVE: return OnMove();
	case AT_ATTACK: return OnAttack();
	case AT_DIE: return OnDie();
	}
}

void CUnit::OnFrameMove(float fElapsedTime)
{
	if (m_fAttackTime < m_fAttackSpeed)
		m_fAttackTime += fElapsedTime;
	UpdateTarget();

	UpdateState();

	UpdateAni(fElapsedTime);
	UpdateAI();
	UpdateCollisionCheck();

	if (this == D_PLAYERCTR)
		return;

	if (m_pHp == NULL)
		m_pHp = D_PROCESSMGR->CreateObj(EGAMEOBJ_GAMEOBJ, "MiniHp", m_vPos + m_vHpPos, D3DXVECTOR3(0.0f, 180.0f, 0.0f));
	else
	{
		if (m_bDestroy)
			m_pHp->Destroy();

		m_pHp->GetRot()->x = -D_CAMERA->GetRot()->x;
		*m_pHp->GetPos() = m_vPos + m_vHpPos;
		
		float fHp = (float)m_iHp;
		float fMaxHp = (float)m_iMaxHp;
		float fScl = fHp / fMaxHp;
		if (fScl <= m_pHp->GetScl()->x)
			m_pHp->GetScl()->x -= 1.0f * fElapsedTime;
		else
			m_pHp->GetScl()->x += 1.0f * fElapsedTime;
	}
}

void CUnit::OnFrameRender(D3DXMATRIX* pmatLocal)
{
	UpdateWorld(pmatLocal);

	Begin();
	DrawObject();
	End();
}

void CUnit::OnNormal()
{
	if (m_pTarget != NULL)
	{
		SetTargetPos(*m_pTarget->GetPos());
		if (m_fAttackTime >= m_fAttackSpeed)
			return ChangeState(AT_ATTACK);
	}
}

void CUnit::OnMove()
{
	if (m_bHold == true)
		return;

	if (m_pTarget != NULL)
		SetTargetPos(*m_pTarget->GetPos());

	float fElapsedTime = DXUTGetElapsedTime();
	float fSpeed = m_fSpeed * fElapsedTime;

	D3DXVECTOR3 vLength = m_vTargetPos - m_vPos;
	float fLength = D3DXVec3Length(&vLength);
	if (fLength <= fSpeed)
	{
		if (m_pTarget == NULL)
		{
			if (m_fAttackTime < m_fAttackSpeed)
				return ChangeState(AT_NORMAL);
			else
				return ChangeState(AT_ATTACK);
		}
		else
			return ChangeState(AT_NORMAL);
	}

	D3DXVECTOR3 vDir = m_vTargetPos - m_vPos;
	D3DXVec3Normalize(&vDir, &vDir);

	m_vPos += vDir * fSpeed;
}

void CUnit::SetTargetPos(D3DXVECTOR3 vPos)
{
	if (vPos == m_vPos)
	{
		m_vTargetPos = vPos;
		return;
	}

	m_vRot.y = D3DXToDegree(atan2(vPos.x - m_vPos.x, vPos.z - m_vPos.z));

	D3DXVECTOR3 vLength = vPos - m_vPos;
	float fLength = D3DXVec3Length(&vLength);
	if (m_pTarget != NULL)
	{
		float fDist = m_pTarget->GetRad() + m_fAttackDist;
		if (fDist >= fLength)
		{
			m_vTargetPos = m_vPos;
			return;
		}
	}
	else
	{
		if (fLength <= m_fRad)
		{
			m_vTargetPos = m_vPos;
			return;
		}
	}

	m_vTargetPos = vPos;
	if (m_eState != AT_MOVE)
	{
		m_bAttackCheck = false;
		return ChangeState(AT_MOVE);
	}
}

void CUnit::SetTargetUnit(CUnit* pTarget)
{
	m_pTarget = pTarget;
	if (pTarget == NULL)
		return SetTargetPos(m_vPos);

	if (pTarget->GetHp() <= 0)
		m_pTarget = NULL;
}

void CUnit::UpdateTarget()
{
	if (m_pTarget == NULL)
		return;

	if (m_pTarget->GetHp() <= 0)
		return SetTargetUnit(NULL);
}

void CUnit::OnAttack()
{
	if (m_pTarget == NULL)
		return ChangeState(AT_NORMAL);

	int iIndex = m_mapAttackIndex[AT_ATTACK];
	if (m_bAttackCheck == false)
	{
		if (m_iIndex == iIndex)
		{
			if (this == D_PLAYERCTR)
			{
				if (D_PLAYERCTR->IsBow())
				{
					CArrow* pArrow = new CArrow;
					pArrow->AddState(AT_NORMAL, "Arrow");
					pArrow->ChangeState(AT_NORMAL);
					*pArrow->GetPos() = m_vPos;
					pArrow->SetDmg(m_iDmg);
					pArrow->SetSpeed(1000.0f);
					pArrow->SetTarget(m_pTarget);
					D_PROCESSMGR->AddGameObj(EGAMEOBJ_GAMEOBJ, pArrow);
				}
				else
					m_pTarget->OnDmg(m_iDmg);
			}
			else
			{
				if (!m_pTarget->IsGodMode())
				{
					if (m_pTarget == D_PLAYERCTR)
					{
						if (D_PLAYERCTR->IsBow())
						{
							D_PLAYERCTR->SetBow(false);
							D_PLAYERCTR->ChangeAttack();
						}
					}
					m_pTarget->OnDmg(m_iDmg);
				}
			}

			m_bAttackCheck = true;
			if (m_pTarget->GetHp() <= 0)
				m_pTarget = NULL;
		}
	}

	if (m_bEndAni)
	{
		m_fAttackTime = 0.0f;
		m_bAttackCheck = false;
		return ChangeState(AT_NORMAL);
	}
}

void CUnit::OnDie()
{
	if (m_bEndAni == false)
		return;

	if (m_sColor.a <= 0.0f)
	{
		if (IsDestroy() == false)
		{
			Destroy();
			return D_SCORE->AddScore(m_iPoint);
		}
	}
	else
		m_sColor.a -= 1.0f * DXUTGetElapsedTime();
}

void CUnit::OnDmg(int iDmg)
{
	CEffect* pEffect = new CEffect;
	pEffect->AddState(AT_NORMAL, "HitEffect");
	pEffect->ChangeState(AT_NORMAL);
	*pEffect->GetPos() = m_vPos;
	*pEffect->GetRot() = D3DXVECTOR3(0.0f, 180.0f, 0.0f);
	D_PROCESSMGR->AddGameObj(EGAMEOBJ_GAMEOBJ, pEffect);

	m_iHp -= iDmg;
	if (m_iHp <= 0)
	{
		m_iHp = 0;
		return ChangeState(AT_DIE);
	}
}

void CUnit::AddAttackIndex(ESTATE eState, int iIndex)
{
	map< ESTATE, int >::iterator mit = m_mapAttackIndex.find(eState);
	if (mit != m_mapAttackIndex.end())
		mit = m_mapAttackIndex.erase(mit);

	m_mapAttackIndex.insert(make_pair(eState, iIndex));
}

void CUnit::UpdateAI()
{
	if (this == D_PLAYERCTR || m_iHp <= 0 || m_eState == AT_ATTACK || D_PLAYERCTR->GetHp() <= 0)
		return;

	D3DXVECTOR3 vLength = *D_PLAYERCTR->GetPos() - m_vPos;
	float fLength = D3DXVec3Length(&vLength);
	if (fLength <= 1000.0f)
	{
		SetTargetUnit(D_PLAYERCTR);
		SetTargetPos(*D_PLAYERCTR->GetPos());
	}
	else
	{
		SetTargetUnit(NULL);
		SetTargetPos(m_vPos);
	}
}

void CUnit::UpdateCollisionCheck()
{
	if (m_eState == AT_ATTACK ||
		m_eState == AT_DIE)
		return;

	for (int i = 0; i < (int)m_vecCollision.size(); ++i)
	{
		if (m_vecCollision[i]->IsDestroy())
			continue;

		D3DXVECTOR3 vDir = *m_vecCollision[i]->GetPos() - m_vPos;
		vDir.y = 0.0f;
		D3DXVec3Normalize(&vDir, &vDir);
		m_vPos -= vDir * ((m_fSpeed * DXUTGetElapsedTime()));
	}
}

void CUnit::UpdateHold(float fElapsedTime)
{
	if (m_bHold == false)
		return;

	m_fHoldTime += fElapsedTime;
	if (m_fHoldTime >= m_fHoldSpeed)
	{
		m_fHoldTime = 0.0f;
		m_bHold = false;
	}
}