
#include "DXUT.h"
#include "Home.h"

CRank::CRank():
m_pBack( NULL )
{

}

CRank::~CRank()
{

}

void CRank::StartStage()
{
	D_GAMEOBJPOOL->LoadRank();

	D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"랭킹배경", L"랭킹배경", D3DXVECTOR2( 0, 0 ), 0, false, ERENDER_LEFTUP, 1, 0, false );
	m_pBack = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"뒤로가기", L"뒤로가기", D3DXVECTOR2( 1124, 654 ), 0, false, ERENDER_LEFTUP, 2, 0, false );
	m_pBack->SetClickObj( true );

	vector< int > vecRank = D_GAMEOBJPOOL->GetRank();
	for( int i = 0; i < (int)vecRank.size(); ++i )
	{
		wstringstream osRank;
		osRank << i + 1 << L"Rank";
		wstringstream osScore;
		osScore << vecRank[i];
		D_FONT->CreateFont( osRank.str(), osScore.str(), D3DXVECTOR2( 500, 40 + ( (float)i * 140 ) ), 60, 0, D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
	}
}

void CRank::OnFrameMove( float fElapsedTime )
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

void CRank::EndStage()
{
	D_FONT->DestroyAll();
	D_GAMEOBJMGR->DestroyAll();
}

void CRank::OnFrameRender()
{
	D_GAMEOBJMGR->OnFrameRender();
}