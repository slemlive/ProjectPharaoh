
#pragma once

class CSoundMgr : public CSingleton< CSoundMgr >
{
private:
	friend CSingleton< CSoundMgr >;

private:
	CSoundManager* m_pSoundMgr;
	map< string, CSound* > m_mapSound;

protected:
	CSoundMgr();
	virtual ~CSoundMgr();

public:
	CSound* CreateSound(wstring wsFile);

	void Load(string sName, wstring wsFile);
	void Play(string sName, bool bLoop = false);
	void Pause(string sName);
	void AllStop();

	void DestroyAll();
};