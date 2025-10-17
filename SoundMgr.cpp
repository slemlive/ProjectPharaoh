
#include "DXUT.h"
#include "NameSpace.h"

CSoundMgr::CSoundMgr()
{
	m_pSoundMgr = new CSoundManager;
	m_pSoundMgr->Initialize(DXUTGetHWND(), DSSCL_NORMAL);
}

CSoundMgr::~CSoundMgr()
{

}

void CSoundMgr::DestroyAll()
{
	for each(map< string, CSound* >::const_reference mr in m_mapSound)
		delete mr.second;

	m_mapSound.clear();
	SAFE_DELETE(m_pSoundMgr);
}

CSound* CSoundMgr::CreateSound(wstring wsFile)
{
	CSound* pSound = NULL;
	if (FAILED(m_pSoundMgr->Create(&pSound, (LPWSTR)wsFile.c_str(), DSBCAPS_CTRLVOLUME)))
		return NULL;

	return pSound;
}

void CSoundMgr::Load(string sName, wstring wsFile)
{
	map< string, CSound* >::iterator mit = m_mapSound.find(sName);
	if (mit != m_mapSound.end())
		return;

	if (FAILED(m_pSoundMgr->Create(&m_mapSound[sName], (LPWSTR)wsFile.c_str(), DSBCAPS_CTRLVOLUME)))
		return;
}

void CSoundMgr::Play(string sName, bool bLoop)
{
	map< string, CSound* >::iterator mit = m_mapSound.find(sName);
	if (mit == m_mapSound.end())
		return;

	if (bLoop)
	{
		DXUT_PlaySoundLooping(mit->second);
	}
	else
		DXUT_PlaySound(mit->second);
}

void CSoundMgr::Pause(string sName)
{
	map< string, CSound* >::iterator mit = m_mapSound.find(sName);
	if (mit == m_mapSound.end())
		return;

	DXUT_StopSound(mit->second);
}

void CSoundMgr::AllStop()
{
	map< string, CSound* >::iterator mit = m_mapSound.begin();
	for (mit; mit != m_mapSound.end(); ++mit)
	{
		mit->second->Stop();
		mit->second->Reset();
	}
}