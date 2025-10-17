
#include "DXUT.h"
#include "NameSpace.h"

CExplayin::CExplayin():
pBack( NULL )
{

}

CExplayin::~CExplayin()
{

}

void CExplayin::StartStage()
{
	D_PROCESSMGR->CreateTextureUI("Explayin", D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	pBack = D_PROCESSMGR->CreateTextureUI("BackButton", D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
}

void CExplayin::OnFrameMove(float fElaspedTime)
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

void CExplayin::OnFrameRender()
{

}

void CExplayin::EndStage()
{
	D_PROCESSMGR->ClearObj();
	D_PROCESSMGR->ClearUI();
}