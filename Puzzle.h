
#pragma once

class CPuzzle : public CGameObj
{
private:
	CGameObj* m_pFruit;

	float m_fAniTime;

	int m_iKey;
	int m_iCount;

public:
	CPuzzle();
	virtual ~CPuzzle();

	int GetKey() { return m_iKey; }
	void SetKey( int iKey ) { m_iKey = iKey; }

	int GetCount() { return m_iCount; }
	void SetCount( int iCount ) { m_iCount = iCount; }

	virtual void Destroy();

	virtual void OnFrameMove( float fElapsedTime );
};