
#include "DXUT.h"
#include "NameSpace.h"

CGameStageMgr::CGameStageMgr() :
m_pStage(NULL),
m_bChange(false),
m_bKey( false )
{
	ZeroMemory(&m_sLight, sizeof(D3DLIGHT9));
}

CGameStageMgr::~CGameStageMgr()
{
	SAFE_DELETE(m_pStage);
}

void CGameStageMgr::ChangeStage(ESTAGE eStage)
{
	m_eStage = eStage;
	m_bChange = true;
}

void CGameStageMgr::UpdateStage()
{
	if (m_bChange == false)
		return;

	if (m_pStage != NULL)
	{
		m_pStage->EndStage();
		SAFE_DELETE(m_pStage);
	}

	m_pStage = Alloc(m_eStage);
	m_pStage->StartStage();
	m_bChange = false;
}

CStage* CGameStageMgr::Alloc(ESTAGE eStage)
{
	switch (eStage)
	{
	case ES_NEW: return new CNew;
	case ES_MAIN: return new CMain;
	case ES_INTRODUCE: return new CIntroduce;
	case ES_EXPLAYIN: return new CExplayin;
	case ES_RANKING: return new CRanking;
	case ES_INTRO: return new CIntro;
	case ES_LOADING: return new CLoading;
	case ES_STAGE1: return new CStage1;
	case ES_STAGE2: return new CStage2;
	case ES_ENDING: return new CEnding;
	case ES_SCORE: return new CScoreStage;
	}

	return NULL;
}

void CGameStageMgr::OnFrameMove(float fElapsedTime)
{
	if (m_pStage != NULL)
	{
		m_pStage->OnFrameMove(fElapsedTime);
		D_PROCESSMGR->OnFrameMove(fElapsedTime);
	}

	UpdateCheat();
	UpdateStage();
}

void CGameStageMgr::UpdateCheat()
{
	if (m_eStage == ES_LOADING)
		return;

	if (DXUTWasKeyPressed(VK_F1))
		return D_GAMESTAGEMGR->ChangeStage(ES_MAIN);

	if (DXUTWasKeyPressed(VK_F2))
		return D_GAMESTAGEMGR->ChangeStage(ES_STAGE1);

	if (DXUTWasKeyPressed(VK_F3))
		return D_GAMESTAGEMGR->ChangeStage(ES_STAGE2);

	if (DXUTWasKeyPressed(VK_F5))
		return D_GAMESTAGEMGR->ChangeStage(ES_ENDING);

	if (DXUTWasKeyPressed(VK_F4))
		return D_GAMESTAGEMGR->ChangeStage(ES_INTRO);

	if (DXUTWasKeyPressed(VK_F6))
	{
		if (D_PLAYERCTR->IsGodMode() == false)
		{
			D_PLAYERCTR->SetGodMode(true);
			return D_PLAYERCTR->SetHp(D_PLAYERCTR->GetMaxHp());
		}
		else
			D_PLAYERCTR->SetGodMode(false);
	}

	if (DXUTWasKeyPressed(VK_F7))
	{
		if (D_PLAYERCTR->IsBow() == false)
			D_PLAYERCTR->SetBow(true);
		else
			D_PLAYERCTR->SetBow(false);
		return D_PLAYERCTR->ChangeAttack();
	}
}

void CGameStageMgr::OnFrameRender()
{
	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, TRUE);
	DXUTGetD3D9Device()->SetLight(0, &m_sLight);
	DXUTGetD3D9Device()->LightEnable(0, TRUE);

	if (m_pStage != NULL)
	{
		D_PROCESSMGR->UpdateObj();
		D_PROCESSMGR->UpdateUI();

		m_pStage->OnFrameRender();
		D_PROCESSMGR->OnFrameRender();
	}
}

void CGameStageMgr::ClearLight()
{
	m_sLight.Ambient.r -= 0.01f;
	m_sLight.Ambient.g -= 0.01f;
	m_sLight.Ambient.b -= 0.01f;

	m_sLight.Diffuse.r -= 0.01f;
	m_sLight.Diffuse.g -= 0.01f;
	m_sLight.Diffuse.b -= 0.01f;
}

void CGameStageMgr::StartLight()
{
	m_sLight.Ambient.r += 0.01f;
	m_sLight.Ambient.g += 0.01f;
	m_sLight.Ambient.b += 0.01f;

	m_sLight.Diffuse.r += 0.01f;
	m_sLight.Diffuse.g += 0.01f;
	m_sLight.Diffuse.b += 0.01f;
}