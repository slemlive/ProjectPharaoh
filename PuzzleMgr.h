
#pragma once

struct SPuzzleLine
{
	vector< CPuzzle* > m_vecPuzzleLine;
};

struct STargetMgr
{
	CPuzzle* m_pTarget1;
	CPuzzle* m_pTarget2;

	STargetMgr():
	m_pTarget1( NULL ),
		m_pTarget2( NULL )
	{
	}
};

class CPuzzleMgr
{
private:
	static CPuzzleMgr* m_pPuzzleMgr;

private:
	map< int, vector< CPuzzle* > > m_mapPuzzle;
	vector< SPuzzleLine > m_vecPuzzleLine;
	vector< STargetMgr > m_vecTargetMgr;
	vector< CPuzzle* > m_vecHint;

	D3DXVECTOR2 m_vPuzzlePos;

	CPuzzle* m_pTarget1;
	CPuzzle* m_pTarget2;

	int m_iWidth;
	int m_iHeight;

	float m_fTimeOut;
	float m_fHintTime;

public:
	CPuzzleMgr();
	virtual ~CPuzzleMgr();

	static CPuzzleMgr* GetPuzzleMgr() { if( m_pPuzzleMgr == NULL ) m_pPuzzleMgr = new CPuzzleMgr; return m_pPuzzleMgr; }
	void ClearPuzzle();

	CPuzzle* GetTarget() { return m_pTarget1; }
	void SetTarget( CPuzzle* pObj ) { m_pTarget1 = pObj; }

	D3DXVECTOR2 GetPuzzlePos() { return m_vPuzzlePos; }
	void SetPuzzlePos( D3DXVECTOR2 vPos ) { m_vPuzzlePos = vPos; }

	vector< SPuzzleLine > GetPuzzleLine() { return m_vecPuzzleLine; }

	float GetTImeOut() { return m_fTimeOut; }
	void SetTimeOut( float fTime ) { m_fTimeOut = fTime; }

	float GetHintTime() { return m_fHintTime; }
	void ResetHintTime() { m_fHintTime = 0.0f; }

	void CreatePuzzle( int iWidth, int iHeight, D3DXVECTOR2 vPos );
	void DestroyPuzzle();

	void OnFrameMove( float fElapsedTime );
};