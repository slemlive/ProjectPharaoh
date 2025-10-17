
#include "DXUT.h"
#include "NameSpace.h"

CStage2::CStage2():
pGround( NULL ),
m_bAttackButton( false ),
pHp( NULL ),
pPortal( NULL )
{

}

CStage2::~CStage2()
{

}

void CStage2::StartStage()
{
	*D_PLAYERCTR->GetPos() = D3DXVECTOR3(1692.6033, 0.0000, 1892.0618);
	D_PLAYERCTR->SetTargetUnit(NULL);
	D_PLAYERCTR->SetTargetPos(*D_PLAYERCTR->GetPos());
	*D_PLAYERCTR->GetRot() = D3DXVECTOR3(0.0f, 180.0f, 0.0f);
	*D_CAMERA->GetLook() = D3DXVECTOR3(1692.6033, 0.0000, 1892.0618);

	D_PROCESSMGR->CreateTextureUI("2StageMiniMap", D3DXVECTOR2(1634.0f, 800.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	D_PROCESSMGR->CreateTextureUI("HpBack", D3DXVECTOR2(166.0f, 74.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	pHp = D_PROCESSMGR->CreateTextureUI("HpBar", D3DXVECTOR2(173.0f, 81.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	D_PROCESSMGR->CreateTextureUI("PlayerUI", D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);

	D_PROCESSMGR->CreateTextureUI("RopeBar", D3DXVECTOR2(1655.0f, 10.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 1);
	D_PROCESSMGR->CreateTextureUI("TrapBar", D3DXVECTOR2(1805.0f, 10.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 1);
	D_PROCESSMGR->CreateTextureUI("ItemBack", D3DXVECTOR2(1602.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	D_PROCESSMGR->CreateTextureUI("ScoreBack", D3DXVECTOR2(1920.0f / 2.0f, 0.0f), D3DXVECTOR2(0.5f, 0.0f), 0.0f, 0);

	D_PROCESSMGR->CreateObj(EGAMEOBJ_GAMEOBJ, "2StageDeco", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pGround = D_PROCESSMGR->CreateObj(EGAMEOBJ_GAMEOBJ, "2StageGround", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D_PROCESSMGR->CreateObj(EGAMEOBJ_GAMEOBJ, "2StageWall", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	D_UNITMGR->CreateUnit(EU_SNAKE, D3DXVECTOR3(-2704.9531, 0.0000, 1825.6794), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_SNAKE, D3DXVECTOR3(-2409.7056, 0.0000, 1820.1267), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_SNAKE, D3DXVECTOR3(-2564.7307, 0.0000, 1992.0618), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_SNAKE, D3DXVECTOR3(-846.4396, 0.0000, -3085.2324), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_SNAKE, D3DXVECTOR3(4909.1104, 0.0000, -2413.9946), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_SNAKE, D3DXVECTOR3(5204.3579, 0.0000, -2419.5474), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_SNAKE, D3DXVECTOR3(5049.3330, 0.0000, -2247.6123), D3DXVECTOR3(0.0f, 90.0f, 0.0f));

	D_UNITMGR->CreateUnit(EU_CAT, D3DXVECTOR3(-1774.3033, 0.0000, 392.8938), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_CAT, D3DXVECTOR3(-1479.0558, 0.0000, 387.3411), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_CAT, D3DXVECTOR3(1825.7893, 0.0000, 559.2762), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_CAT, D3DXVECTOR3(-1108.3188, 0.0000, -2274.4783), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_CAT, D3DXVECTOR3(2121.0369, 0.0000, -2280.0310), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_CAT, D3DXVECTOR3(1966.0117, 0.0000, -2108.0959), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_CAT, D3DXVECTOR3(17.8550, 0.0000, -3090.7852), D3DXVECTOR3(0.0f, 90.0f, 0.0f));

	D_UNITMGR->CreateUnit(EU_MUMMY, D3DXVECTOR3(1095.6624, 0.0000, 545.1882), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_MUMMY, D3DXVECTOR3(800.4148, 0.0000, 550.7408), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_MUMMY, D3DXVECTOR3(940.6372, 0.0000, 717.1232), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_MUMMY, D3DXVECTOR3(-2755.2791, 0.0000, -1404.6238), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_MUMMY, D3DXVECTOR3(-2460.0315, 0.0000, -1410.1765), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_MUMMY, D3DXVECTOR3(-2615.0566, 0.0000, -1238.2415), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_MUMMY, D3DXVECTOR3(-5919.1143, 0.0000, -2179.9221), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_MUMMY, D3DXVECTOR3(-5623.8667, 0.0000, -2185.4749), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_MUMMY, D3DXVECTOR3(-5778.8916, 0.0000, -2013.5398), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_MUMMY, D3DXVECTOR3(17.8550, 0.0000, -2304.3647), D3DXVECTOR3(0.0f, 90.0f, 0.0f));

	D_UNITMGR->CreateUnit(EU_SCORPION, D3DXVECTOR3(-846.4396, 0.0000, -2298.8120), D3DXVECTOR3(0.0f, 90.0f, 0.0f));

	D_UNITMGR->CreateUnit(EU_SC, D3DXVECTOR3(-417.0909, 0.0000, -2707.0496), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_BOSS, D3DXVECTOR3(-2491.9910, 0.0000, 3930.6304), D3DXVECTOR3(0.0f, 90.0f, 0.0f));

	pPortal = (CPortal*)D_PROCESSMGR->CreateObj(EGAMEOBJ_PORTAL, "Portal2", D3DXVECTOR3(-2491.9910, 0.0f, 5139.2461), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pPortal->SetNextStage(ES_ENDING);

	pScore = D_PROCESSMGR->CreateFontUI("Test", D3DXVECTOR2(1920.0f / 2.0f, 30.0f), 50, DT_CENTER, 1);
}

void CStage2::OnFrameMove(float fElapsedTime)
{
	D_PLAYERCTR->OnFrameMove(fElapsedTime);
	D_CAMERA->CursorViewPos();

	if (D_PLAYERCTR->IsDestroy())
	{
		D_PLAYERCTR->InitPlayerInfo();
		return D_GAMESTAGEMGR->ChangeStage(ES_MAIN);
	}

	if (pPortal != NULL)
	{
		D3DLIGHT9* pLight = D_GAMESTAGEMGR->GetLight();
		if (pPortal->IsTrue())
		{
			if (pLight->Diffuse.r >= 0.0f)
				return D_GAMESTAGEMGR->ClearLight();
			else
				return D_GAMESTAGEMGR->ChangeStage(ES_ENDING);
		}
		else
		{
			if (pLight->Diffuse.r < 1.0f)
				return D_GAMESTAGEMGR->StartLight();
		}
	}

	if (pHp != NULL)
	{
		float fHp = (float)(D_PLAYERCTR->GetHp());
		float fMaxHp = (float)(D_PLAYERCTR->GetMaxHp());
		float fScl = fHp / fMaxHp;
		float fSclX = pHp->GetScl()->x;
		if (fScl <= fSclX)
			pHp->GetScl()->x -= 0.5f * fElapsedTime;
		else
			pHp->GetScl()->x += 0.5f * fElapsedTime;
	}

	if (pScore != NULL)
	{
		stringstream os;
		os << D_SCORE->GetScore();
		pScore->SetString(os.str());
	}

	*D_CAMERA->GetLook() = *D_PLAYERCTR->GetPos();

	if (DXUTWasKeyPressed('A'))
		m_bAttackButton = true;

	if (DXUTIsKeyDown(VK_RBUTTON) || (m_bAttackButton && DXUTIsKeyDown(VK_LBUTTON)))
	{
		m_bAttackButton = false;
		if (pGround == NULL)
			return;

		D3DXVECTOR3 vPos(0.0f, 0.0f, 0.0f);
		LPD3DXMESH pClon = D_MESH->GetClonMesh(pGround->GetMeshIndex());
		if (CheckMeshPicking(&pClon, pGround->GetWorld(), &vPos))
		{
			CUnit* pTarget = D_UNITMGR->CheckTargetUnit(&vPos);
			D_PLAYERCTR->SetTargetUnit(pTarget);
			D_PLAYERCTR->SetTargetPos(vPos);
		}
	}
}

void CStage2::OnFrameRender()
{
	D_PROCESSMGR->AddRenderObj(D_PLAYERCTR);
}

void CStage2::EndStage()
{
	D_PROCESSMGR->ClearObj();
	D_PROCESSMGR->ClearUI();
}