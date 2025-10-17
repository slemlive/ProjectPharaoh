
#include "DXUT.h"
#include "Home.h"

CIntro::CIntro():
m_pIntro( NULL ),
m_fTime( 0.0f )
{

}

CIntro::~CIntro()
{

}

void CIntro::StartStage()
{
	m_pIntro = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"인트로", L"인트로", D3DXVECTOR2( 0, 0 ), 0, false, ERENDER_LEFTUP, 0, 0, false );
	m_pIntro->SetClickObj( true );
}

void CIntro::OnFrameMove( float fElapsedTime )
{
	D_GAMEOBJMGR->OnFrameMove( fElapsedTime );
	if( m_pIntro != NULL )
	{
		if( m_pIntro->GetRender()->IsEndAni() == true )
		{
			m_fTime += fElapsedTime;
			if( m_fTime >= 3.0f )
			{
				D_GAMESTAGEMGR->ChangeStage( ESTAGE_MAINMENU );
				return;
			}
		}

		if( m_pIntro->IsClick() == true )
		{
			D_GAMESTAGEMGR->ChangeStage( ESTAGE_MAINMENU );
			return;
		}
	}
}

void CIntro::EndStage()
{
	D_GAMEOBJMGR->DestroyAll();
}

void CIntro::OnFrameRender()
{
	D_GAMEOBJMGR->OnFrameRender();
}