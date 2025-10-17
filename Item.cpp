
#include "DXUT.h"
#include "NameSpace.h"

CItem::CItem()
{

}

CItem::~CItem()
{
	D_SCORE->AddScore(100);
}

void CItem::OnFrameMove(float fElapsedTime)
{
	CGameObj::OnFrameMove(fElapsedTime);

	D3DXVECTOR3 vLength = *D_PLAYERCTR->GetPos() - m_vPos;
	float fLength = D3DXVec3Length(&vLength);
	if (fLength <= 100.0f)
	{
		string sName = m_mapState.begin()->second;
		if (sName == "BowItem")
		{
			D_PLAYERCTR->SetBow(true);
			D_PLAYERCTR->ChangeAttack();
		}
		else if (sName == "SpeedItem")
			D_PLAYERCTR->SetSpeed(D_PLAYERCTR->GetSpeed() + 10.0f);
		else if (sName == "HpItem")
		{
			D_PLAYERCTR->SetMaxHp(D_PLAYERCTR->GetMaxHp() + 10);
			D_PLAYERCTR->SetHp(D_PLAYERCTR->GetMaxHp());
		}
		else if (sName == "TrapItem")
			D_PLAYERCTR->AddTrapCount(1);
		else if (sName == "RopeItem")
			D_PLAYERCTR->AddRopeCount(1);
		else if (sName == "ShieldItem")
		{

		}

		return Destroy();
	}
}

void CItem::OnFrameRender(D3DXMATRIX* pmatLocal)
{
	CGameObj::OnFrameRender(pmatLocal);
}