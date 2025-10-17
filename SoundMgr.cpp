#include "DXUT.h"
#include "Home.h"

CSoundMgr* CSoundMgr::m_pSound;

CSoundMgr::CSoundMgr(void)
{
	m_pSound = NULL;
	m_pSoundMgr = new CSoundManager();
	m_pSoundMgr->Initialize( DXUTGetHWND(), DSSCL_NORMAL );
}


CSoundMgr::~CSoundMgr(void)
{
	map< wstring, CSound* >::iterator mit = m_mapSound.begin();
	for( mit; mit != m_mapSound.end(); ++mit )
		SAFE_DELETE( mit->second );
}

void CSoundMgr::Load( wstring wsName, wstring wsFile )
{
	map< wstring, CSound* >::iterator mit = m_mapSound.find( wsName );
	if( mit != m_mapSound.end() )
		return ;

	m_pSoundMgr->Create( &m_mapSound[wsName], (LPWSTR)wsFile.c_str(), DSBCAPS_CTRLVOLUME );
}

void CSoundMgr::Play( wstring wsName, bool bLoop )
{
	map< wstring, CSound* >::iterator mit = m_mapSound.find( wsName );
	if( mit != m_mapSound.end() )
	{
		if( bLoop )
		{
			DXUT_PlaySoundLooping( m_mapSound[wsName] );
		}
		else
		{
			DXUT_PlaySound( m_mapSound[wsName] );
		}
	}
}

void CSoundMgr::AllStop()
{
	map< wstring, CSound* >::iterator mit = m_mapSound.begin();
	while( mit != m_mapSound.end() )
	{
		mit->second->Stop();
		mit->second->Reset();
		++mit;
	}
}

void CSoundMgr::Pause( wstring wsName )
{
	DXUT_StopSound( m_mapSound[wsName] );
}