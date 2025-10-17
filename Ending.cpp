
#include "DXUT.h"
#include "Home.h"

CEnding::CEnding():
m_pEnding( NULL ),
m_fTime( 0.0f )
{

}

CEnding::~CEnding()
{

}

void CEnding::StartStage()
{
	m_pEnding = D_GAMEOBJMGR->CreateObj( EGAMEOBJ_CLEAR, L"엔딩", L"엔딩", D3DXVECTOR2( 0, 0 ), 0, false, ERENDER_LEFTUP, 0, 0, false );
	m_pEnding->SetClickObj( true );
}

void CEnding::OnFrameMove( float fElapsedTime )
{
	D_GAMEOBJMGR->OnFrameMove( fElapsedTime );

	if( m_pEnding != NULL )
	{
		if( m_pEnding->GetRender()->IsEndAni() == true )
		{
			m_fTime += fElapsedTime;
			if( m_fTime >= 3.0f )
			{
				D_GAMESTAGEMGR->ChangeStage( ESTAGE_MAINMENU );
				return;
			}
		}

		if( m_pEnding->IsClick() == true )
		{
			D_GAMESTAGEMGR->ChangeStage( ESTAGE_MAINMENU );
			return;
		}
	}
}

void CEnding::EndStage()
{
	D_GAMEOBJMGR->DestroyAll();
}

void CEnding::OnFrameRender()
{
	D_GAMEOBJMGR->OnFrameRender();
}