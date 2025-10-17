#pragma once

class CSoundMgr
{
private:
	CSoundManager* m_pSoundMgr;

	map< wstring, CSound* > m_mapSound;

private:
	static CSoundMgr* m_pSound;
	
public:
	CSoundMgr(void);
	virtual ~CSoundMgr(void);

	static CSoundMgr* GetSoundMgr() { if( m_pSound == NULL ) m_pSound = new CSoundMgr(); return m_pSound; }

	void Load( wstring wsName, wstring wsFile );
	void Play( wstring wsName, bool bLoop = false );
	void AllStop();
	void Pause( wstring wsName );
};

