
#include "DXUT.h"
#include "NameSpace.h"

CIntro::CIntro():
pIntro( NULL )
{

}

CIntro::~CIntro()
{

}

void CIntro::StartStage()
{
	pIntro = D_PROCESSMGR->CreateTextureUI("Intro", D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	*pIntro->GetScl() = D3DXVECTOR2(7.5f, 7.5f);
}

void CIntro::OnFrameMove(float fElapsedTime)
{
	if (pIntro != NULL)
	{
		if (pIntro->IsEndAni())
			return D_GAMESTAGEMGR->ChangeStage(ES_MAIN);
	}
}

void CIntro::OnFrameRender()
{

}

void CIntro::EndStage()
{
	D_PROCESSMGR->ClearUI();
}