
#include "DXUT.h"
#include "Home.h"

CMainMenu::CMainMenu():
m_pStart( NULL ),
m_pReport( NULL ),
m_pWay( NULL ),
m_pRank( NULL )
{

}

CMainMenu::~CMainMenu()
{

}

void CMainMenu::StartStage()
{
	D_GAMEOBJPOOL->LoadSprite( L"���۹��", L"Texture/UI/MainMenu/��� (", L").jpg", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"�����ϱ�", L"Texture/UI/MainMenu/�����ϱ� (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"���ӼҰ�", L"Texture/UI/MainMenu/���ӼҰ� (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"���ӹ��", L"Texture/UI/MainMenu/���ӹ�� (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"�������", L"Texture/UI/MainMenu/������� (", L").png", 1, 1.0f, true );

	D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"���۹��", L"���۹��", D3DXVECTOR2( 0, 0 ), 0, false, ERENDER_LEFTUP, 0, 0, false );

	m_pStart = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"�����ϱ�", L"�����ϱ�", D3DXVECTOR2( 500, 270 ), 0, false, ERENDER_LEFTUP, 1, 0, false );
	m_pStart->SetClickObj( true );

	m_pReport = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"���ӼҰ�", L"���ӼҰ�", D3DXVECTOR2( 500, 381 ), 0, false, ERENDER_LEFTUP, 1, 0, false );
	m_pReport->SetClickObj( true );

	m_pWay = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"���ӹ��", L"���ӹ��", D3DXVECTOR2( 500, 491 ), 0, false, ERENDER_LEFTUP, 1, 0, false );
	m_pWay->SetClickObj( true );

	m_pRank = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"�������", L"�������", D3DXVECTOR2( 500, 601 ), 0, false, ERENDER_LEFTUP, 1, 0, false );
	m_pRank->SetClickObj( true );
}

void CMainMenu::OnFrameMove( float fElapsedTime )
{
	D_GAMEOBJMGR->OnFrameMove( fElapsedTime );

	if( m_pStart != NULL )
	{
		if( m_pStart->IsClick() == true )
		{
			D_GAMESTAGEMGR->ChangeStage( ESTAGE_STAGE1 );
			return;
		}
	}

	if( m_pReport != NULL )
	{
		if( m_pReport->IsClick() == true )
		{
			D_GAMESTAGEMGR->ChangeStage( ESTAGE_REPORT );
			return;
		}
	}

	if( m_pWay != NULL )
	{
		if( m_pWay->IsClick() == true )
		{
			D_GAMESTAGEMGR->ChangeStage( ESTAGE_WAY );
			return;
		}
	}

	if( m_pRank != NULL )
	{
		if( m_pRank->IsClick() == true )
		{
			D_GAMESTAGEMGR->ChangeStage( ESTAGE_RANK );
			return;
		}
	}
}

void CMainMenu::EndStage()
{
	D_GAMEOBJMGR->DestroyAll();
}

void CMainMenu::OnFrameRender()
{
	D_GAMEOBJMGR->OnFrameRender();
}