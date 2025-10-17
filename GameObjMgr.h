#pragma once

enum
{
	EGAMEOBJ_CLEAR,
	EGAMEOBJ_TEST,
	EGAMEOBJ_PUZZLE,
};

class CGameObjMgr : public CGameObjContainer
{
private:
	static CGameObjMgr* m_pGameObjMgr;

private:
	void OnFrameMove( const vector< CGameObj* >& m_vecObj, float fElapsedTime );
	void OnFrameRender( const vector< CGameObj* >& m_vecObj );
	
protected:
	virtual CGameObj* Alloc( int iType );

public:
	CGameObjMgr(void);
	virtual ~CGameObjMgr(void);

	static CGameObjMgr* GetGameObjMgr() { if( m_pGameObjMgr == NULL ) m_pGameObjMgr = new CGameObjMgr; return m_pGameObjMgr; }

	void OnFrameMove( float fElapsedTime );
	void OnFrameRender();
};

