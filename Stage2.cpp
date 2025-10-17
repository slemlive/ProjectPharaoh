
#include "dxut.h"
#include "Home.h"

CStage2::CStage2():
m_pBack( NULL ),
m_pTimmer( NULL ),
m_pBomb( NULL ),
m_pCombo( NULL ),
m_pReady( NULL ),
m_fStartTime( 0.0f ),
m_fEndTime( 0.0f ),
m_pEnd( NULL ),
m_pEndMenu( NULL ),
m_pReStart( NULL ),
m_pExit( NULL )
{

}

CStage2::~CStage2()
{
}

void CStage2::StartStage()
{
	D_PUZZLEMGR->ResetHintTime();
	D_GAMESTAGEMGR->SetBombGage( 0 );
	D_GAMESTAGEMGR->ResetCombo();

	D_GAMESTAGEMGR->SetGameTimmer( 120.0f );

	m_pReady = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"스타트", L"레디", D3DXVECTOR2( 640, 360 ), 0, false, ERENDER_CENTER, 10, 0, false );

	m_pBack = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"배경", L"배경", D3DXVECTOR2( 0, 0 ), 0, false, ERENDER_LEFTUP, 0, 0, false );
	m_pBack->AddRenderState( AT_FEVER, L"피버" );
	D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"2스테이지", L"2스테이지", D3DXVECTOR2( 392, 116 ), 0, false, ERENDER_LEFTUP, 1, 0, false );

	D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"타이머배경", L"타이머배경", D3DXVECTOR2( 350, 664 ), 0, false, ERENDER_LEFTUP, 1, 0, false );
	m_pTimmer = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"타이머게이지", L"타이머게이지", D3DXVECTOR2( 354, 667 ), 0, false, ERENDER_LEFTUP, 2, 0, false );
	
	D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"폭탄배경", L"폭탄배경", D3DXVECTOR2( 435, 33 ), 0, false, ERENDER_LEFTUP, 1, 0, false );
	m_pBomb = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"폭탄게이지", L"폭탄게이지", D3DXVECTOR2( 438, 36 ), 0, false, ERENDER_LEFTUP, 2, 0, false );
	
	m_pCombo = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"콤보", L"1콤보", D3DXVECTOR2( 977, 200 ), 0, false, ERENDER_LEFTUP, 1, 0, false );

	D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"폭탄아이콘", L"폭탄아이콘", D3DXVECTOR2( 355, 0 ), 0, false, ERENDER_LEFTUP, 1, 0, false );
	D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"점수판", L"점수판", D3DXVECTOR2( 948, 17 ), 0, false, ERENDER_LEFTUP, 2, 0, false );
	D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"피버타임시간", L"피버타임시간", D3DXVECTOR2( 103, 33 ), 0, false, ERENDER_LEFTUP, 1, 0, false );

	D_FONT->CreateFont( L"Score", L"Score : 0", D3DXVECTOR2( 988, 40 ), 30, 0, D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f ) );
	D_FONT->CreateFont( L"FeverTime", L" 0 : 00", D3DXVECTOR2( 118, 105 ), 30, 0, D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f ) );

	D_PUZZLEMGR->CreatePuzzle( 7, 7, D3DXVECTOR2( 350, 585 ) );
}

void CStage2::OnFrameMove( float fElapsedTime )
{
	if( D_PUZZLEMGR->GetTImeOut() >= 10.0f )
	{
		D_GAMESTAGEMGR->SetGameStart( false );

		D_GAMESTAGEMGR->AddCountDown( fElapsedTime );
		if( D_GAMESTAGEMGR->GetCountDown() >= 10.0f )
		{
			D_GAMESTAGEMGR->ChangeStage( ESTAGE_MAINMENU );
			return;
		}

		if( m_pEndMenu == NULL )
			m_pEndMenu = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"끝나셨습니다", L"끝나셨습니다", D3DXVECTOR2( 357, 161 ), 0, false, ERENDER_LEFTUP, 10, 0, false );

		if( m_pExit == NULL )
		{
			m_pExit = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"끝내기", L"끝내기", D3DXVECTOR2( 528, 436 ), 0, false, ERENDER_LEFTUP, 10, 0, false );
			m_pExit->SetClickObj( true );
		}
		else
		{
			if( m_pExit->IsClick() == true )
			{
				D_PUZZLEMGR->SetTimeOut( 0.0f );
				D_GAMESTAGEMGR->ChangeStage( ESTAGE_MAINMENU );
				return;
			}
		}

		if( m_pReStart == NULL )
		{
			m_pReStart = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"이어하기", L"이어하기", D3DXVECTOR2( 528, 328 ), 0, false, ERENDER_LEFTUP, 10, 0, false );
			m_pReStart->SetClickObj( true );
		}
		else
		{
			if( m_pReStart->IsClick() == true )
			{
				m_pEndMenu->Destroy();
				m_pExit->Destroy();
				m_pReStart->Destroy();
				m_pEndMenu = NULL;
				m_pExit = NULL;
				m_pReStart = NULL;
				D_PUZZLEMGR->SetTimeOut( 0.0f );
				return;
			}
		}
	}
	else
	{
		if( D_GAMESTAGEMGR->IsGameStart() == true )
		{
			D_GAMESTAGEMGR->SubGameTimmer( fElapsedTime );
		}
	}

	if( D_GAMESTAGEMGR->GetGameTimmer() <= 0.0f )
	{
		if( m_pEnd == NULL )
			m_pEnd = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"타임오버", L"타임오버", D3DXVECTOR2( 334, -445 ), 0, false, ERENDER_LEFTUP, 10, 0, false );
		else
		{
			if( m_pEnd->GetPos()->y < 0.0f )
				m_pEnd->SetPos( D3DXVECTOR2( m_pEnd->GetPos()->x, m_pEnd->GetPos()->y + 5.0f ) );
			else
			{
				m_fEndTime += fElapsedTime;
				if( m_fEndTime >= 2.0f )
				{
					D_GAMESTAGEMGR->ChangeStage( ESTAGE_STAGE3 );
					return;
				}
			}
		}
	}
	else
	{
		if( m_pReady != NULL )
		{
			m_fStartTime += fElapsedTime;
			D_GAMESTAGEMGR->SetGameStart( false );
		}
		else
			D_GAMESTAGEMGR->SetGameStart( true );
	}

	if( m_fStartTime >= 1.0f )
		m_pReady->AddRenderState( AT_NORMAL, L"스타트" );
	
	if( m_fStartTime >= 1.3f )
	{
		m_pReady->Destroy();
		m_pReady = NULL;
		m_fStartTime = 0.0f;
	}

	if( m_pBack != NULL )
	{
		if( D_GAMESTAGEMGR->IsFever() == true )
			m_pBack->SetState( AT_FEVER );
		else
			m_pBack->SetState( AT_NORMAL );
	}

	if( m_pTimmer != NULL )
	{
		m_pTimmer->SetScl( D3DXVECTOR2( ( 1.0f / 120 ) * D_GAMESTAGEMGR->GetGameTimmer(), 1.0f ) );
	}

	if( m_pBomb != NULL )
	{
		m_pBomb->SetScl( D3DXVECTOR2( ( 1.0f / 5000 ) * D_GAMESTAGEMGR->GetBombGage(), 1.0f ) );
	}

	if( m_pCombo != NULL )
	{
		wstringstream Combo;
		Combo << D_GAMESTAGEMGR->GetCombo() << L"콤보";
		if( m_pCombo->GetName() != Combo.str() )
		{
			if( D_GAMESTAGEMGR->GetCombo() == 0 )
				m_pCombo->AddRenderState( AT_NORMAL, L"" );
			else if( D_GAMESTAGEMGR->GetCombo() == 1 )
				m_pCombo->AddRenderState( AT_NORMAL, L"1콤보" );
			else if( D_GAMESTAGEMGR->GetCombo() == 2 )
				m_pCombo->AddRenderState( AT_NORMAL, L"2콤보" );
			else if( D_GAMESTAGEMGR->GetCombo() == 3 )
				m_pCombo->AddRenderState( AT_NORMAL, L"3콤보" );
			else if( D_GAMESTAGEMGR->GetCombo() == 4 )
				m_pCombo->AddRenderState( AT_NORMAL, L"4콤보" );
			else if( D_GAMESTAGEMGR->GetCombo() >= 5 )
				m_pCombo->AddRenderState( AT_NORMAL, L"피버콤보" );

			m_pCombo->SetName( Combo.str() );
		}
	}

	wstringstream os;
	os << L"Score : " << D_GAMESTAGEMGR->GetScore();
	D_FONT->SetStr( L"Score", os.str() );

	wstringstream Combo;
	Combo << L"Combo : " << D_GAMESTAGEMGR->GetCombo();
	D_FONT->SetStr( L"Combo", Combo.str() );

	if( D_GAMESTAGEMGR->IsFever() == true )
	{
		int iTime = (int)D_GAMESTAGEMGR->GetFeverTime();
		float fTime = D_GAMESTAGEMGR->GetFeverTime();
		float fTime2 = ( fTime - iTime ) * 100;
		int iTime2 = (int)fTime2;

		wstringstream Time;
		Time << iTime << L" : " << iTime2;
		D_FONT->SetStr( L"FeverTime", Time.str() );

		D_GAMESTAGEMGR->SubFeverTime( fElapsedTime );
	}
	else
	{
		D_GAMESTAGEMGR->ResetFeverTime();
		D_FONT->SetStr( L"FeverTime", L" 0 : 00 " );
	}

	D_GAMEOBJMGR->OnFrameMove( fElapsedTime );
}

void CStage2::OnFrameRender()
{
	D_GAMEOBJMGR->OnFrameRender();
}

void CStage2::EndStage()
{
	D_FONT->DestroyAll();
	D_PUZZLEMGR->ClearPuzzle();
	D_GAMEOBJMGR->DestroyAll();
}