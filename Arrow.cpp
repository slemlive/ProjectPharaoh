
#include "DXUT.h"
#include "NameSpace.h"

CArrow::CArrow():
m_fSpeed( 0.0f ),
m_pTarget( NULL ),
m_iDmg( 0 )
{

}

CArrow::~CArrow()
{

}

void CArrow::MoveArrow(float fElapsedTime)
{
	if (m_bDestroy)
		return;

	D3DXVECTOR3* vTargetPos = m_pTarget->GetPos();
	m_vRot.y = D3DXToDegree(atan2(vTargetPos->x - m_vPos.x, vTargetPos->z - m_vPos.z));
	D3DXVECTOR3 vLength = *vTargetPos - m_vPos;
	D3DXVECTOR3 vDir = *vTargetPos - m_vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	float fLength = D3DXVec3Length(&vLength);
	float fSpeed = m_fSpeed * fElapsedTime;
	if (fLength > m_pTarget->GetRad())
		m_vPos += vDir * fSpeed;
	else
	{
		m_pTarget->OnDmg(m_iDmg);
		return Destroy();
	}
}

void CArrow::OnFrameMove(float fElapsedTime)
{
	CGameObj::OnFrameMove(fElapsedTime);
	MoveArrow(fElapsedTime);
}

void CArrow::OnFrameRender(D3DXMATRIX* pmatLocal)
{
	CGameObj::OnFrameRender(pmatLocal);
}