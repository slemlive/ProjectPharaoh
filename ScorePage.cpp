
#include "DXUT.h"
#include "Home.h"

CScorePage::CScorePage():
m_pBack( NULL )
{

}

CScorePage::~CScorePage()
{

}

void CScorePage::StartStage()
{
	D_GAMEOBJPOOL->LoadRank();

	D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"배경", L"배경", D3DXVECTOR2( 0, 0 ), 0, false, ERENDER_LEFTUP, 0, 0, false );
	D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"스코어", L"스코어", D3DXVECTOR2( 640, 360 ), 0, false, ERENDER_CENTER, 1, 0, false );

	m_pBack = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"뒤로가기", L"뒤로가기", D3DXVECTOR2( 1124, 654 ), 0, false, ERENDER_LEFTUP, 2, 0, false );
	m_pBack->SetClickObj( true );

	vector< int > vecRank = D_GAMEOBJPOOL->GetRank();
	vecRank.push_back( D_GAMESTAGEMGR->GetScore() );

	for( int i = 0; i < (int)vecRank.size(); ++i )
	{
		for( int j = 0; j < (int)vecRank.size()-1; ++j )
		{
			if( vecRank[j] < vecRank[j+1] )
			{
				int iTemp = vecRank[j];
				vecRank[j] = vecRank[j+1];
				vecRank[j+1] = iTemp;
			}
		}
	}

	if( (int)vecRank.size() > 5 )
	{
		for( int i = 0; i < (int)vecRank.size(); ++i )
		{
			if( i > 5 )
				vecRank.erase( vecRank.begin() + i );
		}
	}

	D_GAMEOBJPOOL->SetRank( vecRank );

	wstringstream osMyScore;
	osMyScore << L"내점수 : " << D_GAMESTAGEMGR->GetScore();
	D_FONT->CreateFont( L"MyScore", osMyScore.str(), D3DXVECTOR2( 435, 59 ), 50, 0, D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f ) );

	for( int i = 0; i < (int)vecRank.size(); ++i )
	{
		wstringstream osRank;
		osRank << i + 1 << L"Rank";
		wstringstream osScore;
		osScore << vecRank[i];
		D_FONT->CreateFont( osRank.str(), osScore.str(), D3DXVECTOR2( 513, 213 + ( (float)i * 107 ) ), 30, 0, D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
	}

	D_GAMEOBJPOOL->SaveRank();
}

void CScorePage::OnFrameMove( float fElapsedTime )
{
	D_GAMEOBJMGR->OnFrameMove( fElapsedTime );

	if( m_pBack != NULL )
	{
		if( m_pBack->IsClick() == true )
		{
			D_GAMESTAGEMGR->ChangeStage( ESTAGE_ENDING );
			return;
		}
	}
}

void CScorePage::EndStage()
{
	D_FONT->DestroyAll();
	D_GAMEOBJMGR->DestroyAll();
}

void CScorePage::OnFrameRender()
{
	D_GAMEOBJMGR->OnFrameRender();
}