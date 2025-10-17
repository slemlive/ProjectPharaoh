
#include "DXUT.h"
#include "NameSpace.h"

CStage1::CStage1():
pMap( NULL ),
m_bAttackButton( false ),
pHp( NULL ),
pSys( NULL ),
pMsg( NULL ),
pPortal( NULL ),
pBoss( NULL )
{

}

CStage1::~CStage1()
{

}

void CStage1::StartStage()
{
	D3DLIGHT9* pLight = D_GAMESTAGEMGR->GetLight();
	pLight->Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pLight->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D_SCORE->ResetScore();
	*D_CAMERA->GetLocal() = D3DXVECTOR3(0.0f, 1500.0f, -1400.0f);
	*D_CAMERA->GetRot() = D3DXVECTOR3(45.0f, 0.0f, 0.0f);

	D_SOUNDMGR->Load("Test", L"Sound/Test.wav");
	D_SOUNDMGR->Play("Test", true);

	*D_PLAYERCTR->GetPos() = D3DXVECTOR3(2598.1467, 0.0000, 2682.9639);
	*D_PLAYERCTR->GetRot() = D3DXVECTOR3(0.0f, 180.0f, 0.0f);
	D_PLAYERCTR->InitPlayerInfo();
	D_PLAYERCTR->ChangeState(AT_NORMAL);

	D_PROCESSMGR->CreateTextureUI("MiniMap", D3DXVECTOR2(1634.0f, 800.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	D_PROCESSMGR->CreateTextureUI("HpBack", D3DXVECTOR2(166.0f, 74.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	pHp = D_PROCESSMGR->CreateTextureUI("HpBar", D3DXVECTOR2(173.0f, 81.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	D_PROCESSMGR->CreateTextureUI("PlayerUI", D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	pHp->GetScl()->x = 0.0f;

	D_PROCESSMGR->CreateTextureUI("RopeBar", D3DXVECTOR2(1655.0f, 10.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 1);
	D_PROCESSMGR->CreateTextureUI("TrapBar", D3DXVECTOR2(1805.0f, 10.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 1);
	D_PROCESSMGR->CreateTextureUI("ItemBack", D3DXVECTOR2(1602.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	D_PROCESSMGR->CreateTextureUI("ScoreBack", D3DXVECTOR2(1920.0f / 2.0f, 0.0f), D3DXVECTOR2(0.5f, 0.0f), 0.0f, 0);

	D_PROCESSMGR->CreateObj(EGAMEOBJ_GAMEOBJ, "1StageDeco", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pMap = D_PROCESSMGR->CreateObj(EGAMEOBJ_GAMEOBJ, "1StageGround", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D_PROCESSMGR->CreateObj(EGAMEOBJ_GAMEOBJ, "1StageWall", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	D_PROCESSMGR->CreateObj(EGAMEOBJ_TORCH, "Torch", D3DXVECTOR3(55.9305, 367.8338, -1873.9690), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D_PROCESSMGR->CreateObj(EGAMEOBJ_TORCH, "Torch", D3DXVECTOR3(55.9305f, 367.8338f, -3285.4211f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D_PROCESSMGR->CreateObj(EGAMEOBJ_TORCH, "Torch", D3DXVECTOR3(2022.1764f, 286.5848, -1297.9414f), D3DXVECTOR3(0.0f, -90.0f, 0.0f));
	D_PROCESSMGR->CreateObj(EGAMEOBJ_TORCH, "Torch", D3DXVECTOR3(426.3733, 367.8338, -962.2684), D3DXVECTOR3(0.0f, 180.0f, 0.0f));
	D_PROCESSMGR->CreateObj(EGAMEOBJ_TORCH, "Torch", D3DXVECTOR3(426.3733, 176.5623, 1852.3497), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D_PROCESSMGR->CreateObj(EGAMEOBJ_TORCH, "Torch", D3DXVECTOR3(3238.1909, 176.5623, 887.3826), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_PROCESSMGR->CreateObj(EGAMEOBJ_TORCH, "Torch", D3DXVECTOR3(-3176.1509, 176.5623, 887.3826), D3DXVECTOR3(0.0f, -90.0f, 0.0f));
	D_PROCESSMGR->CreateObj(EGAMEOBJ_TORCH, "Torch", D3DXVECTOR3(-314.3334, 176.5623, 1852.3499), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D_PROCESSMGR->CreateObj(EGAMEOBJ_TORCH, "Torch", D3DXVECTOR3(-314.3334, 367.8338, -962.2684), D3DXVECTOR3(0.0f, 180.0f, 0.0f));
	D_PROCESSMGR->CreateObj(EGAMEOBJ_TORCH, "Torch", D3DXVECTOR3(-1910.1365, 286.5848, -1297.9413), D3DXVECTOR3(0.0f, 90.0f, 0.0f));


	D_UNITMGR->CreateUnit(EU_SNAKE, D3DXVECTOR3(861.9882, 0.0000, 392.8938), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_SNAKE, D3DXVECTOR3(1002.2106, 0.0000, 559.2762), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_SNAKE, D3DXVECTOR3(-1108.3188, 0.0000, 392.8938), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_SNAKE, D3DXVECTOR3(-813.0713, 0.0000, 387.3411), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_SNAKE, D3DXVECTOR3(-987.6489, 0.0000, 559.2762), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_SNAKE, D3DXVECTOR3(1157.2358, 0.0000, 387.3411), D3DXVECTOR3(0.0f, 90.0f, 0.0f));

	D_UNITMGR->CreateUnit(EU_CAT, D3DXVECTOR3(-119.1958, 0.0000, -2497.9849), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_CAT, D3DXVECTOR3(176.0518, 0.0000, -2503.5376), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_CAT, D3DXVECTOR3(21.0266, 0.0000, -2331.6025), D3DXVECTOR3(0.0f, 90.0f, 0.0f));

	D_UNITMGR->CreateUnit(EU_MUMMY, D3DXVECTOR3(2507.8777, 0.0000, -1404.6238), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_MUMMY, D3DXVECTOR3(2803.1252, 0.0000, -1410.1765), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_MUMMY, D3DXVECTOR3(2648.1001, 0.0000, -1238.2415), D3DXVECTOR3(0.0f, 90.0f, 0.0f));

	D_UNITMGR->CreateUnit(EU_SCORPION, D3DXVECTOR3(-2568.6638, 0.0000, -1404.6238), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_SCORPION, D3DXVECTOR3(-2273.4163, 0.0000, -1410.1765), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	D_UNITMGR->CreateUnit(EU_SCORPION, D3DXVECTOR3(-2428.4414, 0.0000, -1238.2415), D3DXVECTOR3(0.0f, 90.0f, 0.0f));

	pBoss = (CSC*)D_UNITMGR->CreateUnit(EU_SC, D3DXVECTOR3(-2377.2395, 0.0000, 1992.0618), D3DXVECTOR3(0.0f, 180.0f, 0.0f));

	pPortal = (CPortal*)D_PROCESSMGR->CreateObj(EGAMEOBJ_PORTAL, "Portal2", D3DXVECTOR3(-2400.0f, 0.0000, 3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pPortal->SetNextStage(ES_STAGE2);

	pScore = D_PROCESSMGR->CreateFontUI("", D3DXVECTOR2(1920.0f / 2.0f, 30.0f), 50, DT_CENTER, 1);

	pSys = new CParticleSystem;
	pSys->InitParticleSystem("Texture/Fire.png", 0.2f, 20.0f, 3.0f, 50.0f, true);
	*pSys->GetPos() = D3DXVECTOR3(55.9305, 380.8338, -2000.9690);
	D_PROCESSMGR->AddGameObj(EGAMEOBJ_GAMEOBJ, pSys);
}

void CStage1::OnFrameMove(float fElapsedTime)
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
		if (pPortal->IsTrue())
		{
			D3DLIGHT9* pLight = D_GAMESTAGEMGR->GetLight();
			if (pLight->Diffuse.r >= 0.0f)
				return D_GAMESTAGEMGR->ClearLight();
			else
				return D_GAMESTAGEMGR->ChangeStage(ES_STAGE2);
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
		if (pMap == NULL)
			return;

		D3DXVECTOR3 vPos(0.0f, 0.0f, 0.0f);
		LPD3DXMESH pClon = D_MESH->GetClonMesh(pMap->GetMeshIndex());
		if (CheckMeshPicking(&pClon, pMap->GetWorld(), &vPos) && pClon != NULL)
		{
			CUnit* pTarget = D_UNITMGR->CheckTargetUnit(&vPos);
			if (pTarget != NULL)
				vPos = *pTarget->GetPos();

			D_PLAYERCTR->SetTargetUnit(pTarget);
			D_PLAYERCTR->SetTargetPos(vPos);
		}
	}
}

void CStage1::OnFrameRender()
{
	D_PROCESSMGR->AddRenderObj(D_PLAYERCTR);
}

void CStage1::EndStage()
{
	D_PROCESSMGR->ClearObj();
	D_PROCESSMGR->ClearUI();
}