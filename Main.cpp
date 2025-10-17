
#include "DXUT.h"
#include "NameSpace.h"

CMain::CMain():
m_pPlayButton( NULL ),
m_pIntroduceButton( NULL ),
m_pExplayinButton( NULL ),
m_pRankingButton( NULL )
{

}

CMain::~CMain()
{

}

void CMain::StartStage()
{
	D_PROCESSMGR->CreateTextureUI("MainBackGround", D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	D_PROCESSMGR->CreateTextureUI("MainLine", D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);

	m_pPlayButton = D_PROCESSMGR->CreateTextureUI("PlayButton", D3DXVECTOR2(0.0f, 720.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	m_pExplayinButton = D_PROCESSMGR->CreateTextureUI("ExplayinButton", D3DXVECTOR2(963.0f, 720.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	m_pIntroduceButton = D_PROCESSMGR->CreateTextureUI("IntroduceButton", D3DXVECTOR2(479.0f, 720.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	m_pRankingButton = D_PROCESSMGR->CreateTextureUI("RankingButton", D3DXVECTOR2(1434.0f, 720.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
}

void CMain::OnFrameMove(float fElapsedTime)
{
	if (DXUTIsKeyDown(VK_LBUTTON))
	{
		POINT ptCursor;
		GetCursorPos(&ptCursor);
		ScreenToClient(DXUTGetHWND(), &ptCursor);
		RECT rcRect = { 0, 0, 0, 0 };

		if (m_pPlayButton != NULL)
		{
			rcRect = GetRect(m_pPlayButton);
			if (PtInRect(&rcRect, ptCursor))
				return D_GAMESTAGEMGR->ChangeStage(ES_STAGE1);
		}
		
		if (m_pExplayinButton != NULL)
		{
			rcRect = GetRect(m_pExplayinButton);
			if (PtInRect(&rcRect, ptCursor))
				return D_GAMESTAGEMGR->ChangeStage(ES_EXPLAYIN);
		}
		
		if (m_pIntroduceButton != NULL)
		{
			rcRect = GetRect(m_pIntroduceButton);
			if (PtInRect(&rcRect, ptCursor))
				return D_GAMESTAGEMGR->ChangeStage(ES_INTRODUCE);
		}
		
		if (m_pRankingButton != NULL)
		{
			rcRect = GetRect(m_pRankingButton);
			if (PtInRect(&rcRect, ptCursor))
				return D_GAMESTAGEMGR->ChangeStage(ES_RANKING);
		}
	}
}

void CMain::OnFrameRender()
{
}

void CMain::EndStage()
{
	D_PROCESSMGR->ClearObj();
	D_PROCESSMGR->ClearUI();
}