
#include "DXUT.h"
#include "Home.h"

CReport::CReport():
m_pBack( NULL )
{

}

CReport::~CReport()
{

}

void CReport::StartStage()
{
	D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"게임소개배경", L"게임소개배경", D3DXVECTOR2( 0, 0 ), 0, false, ERENDER_LEFTUP, 1, 0, false );
	m_pBack = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"뒤로가기", L"뒤로가기", D3DXVECTOR2( 1124, 654 ), 0, false, ERENDER_LEFTUP, 2, 0, false );
	m_pBack->SetClickObj( true );
}

void CReport::OnFrameMove( float fElapsedTime )
{
	D_GAMEOBJMGR->OnFrameMove( fElapsedTime );

	if( m_pBack != NULL )
	{
		if( m_pBack->IsClick() == true )
		{
			D_GAMESTAGEMGR->ChangeStage( ESTAGE_MAINMENU );
			return;
		}
	}
}

void CReport::EndStage()
{
	D_GAMEOBJMGR->DestroyAll();
}

void CReport::OnFrameRender()
{
	D_GAMEOBJMGR->OnFrameRender();
}