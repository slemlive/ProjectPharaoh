#include "DXUT.h"
#include "Home.h"

CGameStageMgr* CGameStageMgr::m_pStageMgr;

CGameStageMgr::CGameStageMgr(void):
	m_pStage( NULL ),
	m_iStage( 0 ),
	m_iScore( 0 ),
	m_iCombo( 0 ),
	m_iBombGage( 0 ),
	m_bFever( false ),
	m_fGameTimmer( 0 ),
	m_fFeverTime( 10.0f ),
	m_fComboTime( 0.0f ),
	m_bGameStart( false ),
	m_fCountDown( 0.0f ),
	m_bClickOn( false )
{
}


CGameStageMgr::~CGameStageMgr(void)
{
}

void CGameStageMgr::ChangeStage( int iStage )
{
	if( m_pStage != NULL )
	{
		m_pStage->EndStage();
		SAFE_DELETE( m_pStageMgr->m_pStage );
	}

	switch( iStage )
	{
	case ESTAGE_INTRO:
		m_pStage = new CIntro();
		m_pStage->StartStage();
		m_iStage = ESTAGE_INTRO;
		break;

	case ESTAGE_MAINMENU:
		m_pStage = new CMainMenu();
		m_pStage->StartStage();
		m_iStage = ESTAGE_MAINMENU;
		break;

	case ESTAGE_WAY:
		m_pStage = new CWay();
		m_pStage->StartStage();
		m_iStage = ESTAGE_WAY;
		break;

	case ESTAGE_RANK:
		m_pStage = new CRank();
		m_pStage->StartStage();
		m_iStage = ESTAGE_RANK;
		break;

	case ESTAGE_REPORT:
		m_pStage = new CReport();
		m_pStage->StartStage();
		m_iStage = ESTAGE_REPORT;
		break;

	case ESTAGE_STAGE1:
		m_pStage = new CStage1();
		m_pStage->StartStage();
		m_iStage = ESTAGE_STAGE1;
		break;

	case ESTAGE_STAGE2:
		m_pStage = new CStage2();
		m_pStage->StartStage();
		m_iStage = ESTAGE_STAGE2;
		break;

	case ESTAGE_STAGE3:
		m_pStage = new CStage3();
		m_pStage->StartStage();
		m_iStage = ESTAGE_STAGE3;
		break;

	case ESTAGE_SCORE:
		m_pStage = new CScorePage();
		m_pStage->StartStage();
		m_iStage = ESTAGE_SCORE;
		break;

	case ESTAGE_ENDING:
		m_pStage = new CEnding();
		m_pStage->StartStage();
		m_iStage = ESTAGE_ENDING;
		break;
	}
}

void CGameStageMgr::OnFrameMove( float fElapsedTime )
{
	if( m_pStage != NULL )
		m_pStage->OnFrameMove( fElapsedTime );

	if( m_fGameTimmer < 0.0f )
	{
		m_fGameTimmer = 0.0f;
		if( D_PUZZLEMGR->GetPuzzleLine().empty() == true )
			m_bGameStart = false;
	}

	if( m_iCombo >= 5 )
		m_bFever = true;
	else
		m_bFever = false;

	if( m_bClickOn == true )
		m_bClickOn = false;

	if( m_fFeverTime <= 0.0f )
	{
		m_iCombo = 0;
		m_bFever = false;
		m_fFeverTime = 10.0f;
	}

	if( m_iCombo > 0 )
		m_fComboTime += fElapsedTime;
	else
		m_fComboTime = 0.0f;

	if( m_fComboTime >= 3.0f )
		m_iCombo = 0;

	GetCursorPos( &m_vMousePos );
	ScreenToClient( DXUTGetHWND(), &m_vMousePos );
}

void CGameStageMgr::OnFrameRender()
{
	if( m_pStage != NULL )
		m_pStage->OnFrameRender();
}