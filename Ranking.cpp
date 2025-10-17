
#include "DXUT.h"
#include "NameSpace.h"

CRanking::CRanking():
pBack( NULL )
{

}

CRanking::~CRanking()
{

}

void CRanking::StartStage()
{
	D_PROCESSMGR->CreateTextureUI("Ranking", D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	pBack = D_PROCESSMGR->CreateTextureUI("BackButton", D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);

	D_RANKING->UpdateRank();
	for (int i = 0; i < 4; ++i)
	{
		string sName = "-";
		char cScore[256] = "-";
		const SScoreData* pScoreData = D_RANKING->GetScoreData(i);
		if (pScoreData != NULL)
		{
			sName = pScoreData->sName;
			itoa(pScoreData->iScore, cScore, 10);
		}

		D_PROCESSMGR->CreateFontUI(sName, D3DXVECTOR2(515.0f, 305.0f + (i * 215.0f)), 60, DT_LEFT, 1);
		D_PROCESSMGR->CreateFontUI(cScore, D3DXVECTOR2(1197.0f, 305.0f + (i * 215.0f)), 60, DT_LEFT, 1);
	}

	D_RANKING->Write();
}

void CRanking::OnFrameMove(float fElapsedTime)
{
	if (DXUTIsKeyDown(VK_LBUTTON))
	{
		if (pBack != NULL)
		{
			POINT ptCursor;
			GetCursorPos(&ptCursor);
			ScreenToClient(DXUTGetHWND(), &ptCursor);
			RECT rcRect = { 0, 0, 0, 0 };

			rcRect = GetRect(pBack);
			if (PtInRect(&rcRect, ptCursor))
				return D_GAMESTAGEMGR->ChangeStage(ES_MAIN);
		}
	}
}

void CRanking::OnFrameRender()
{

}

void CRanking::EndStage()
{
	D_PROCESSMGR->ClearObj();
	D_PROCESSMGR->ClearUI();
}