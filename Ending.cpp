
#include "DXUT.h"
#include "NameSpace.h"

CEnding::CEnding():
pEnding( NULL )
{

}

CEnding::~CEnding()
{

}

void CEnding::StartStage()
{
	pEnding = D_PROCESSMGR->CreateTextureUI("Ending", D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
}

void CEnding::OnFrameMove(float fElapsedTime)
{
	if (pEnding != NULL)
	{
		if (pEnding->IsEndAni())
			return D_GAMESTAGEMGR->ChangeStage(ES_SCORE);
	}
}

void CEnding::OnFrameRender()
{

}

void CEnding::EndStage()
{
	D_PROCESSMGR->ClearObj();
	D_PROCESSMGR->ClearUI();
}