#pragma once

enum ESTATE
{
	AT_NORMAL,
	AT_ANI,
	AT_FEVER,
	AT_CLICK,
	AT_HINT,
	AT_DIE,
};

class CRender;

class CGameObj
{
protected:
	D3DXVECTOR2 m_vPos;
	D3DXVECTOR2 m_vScl;
	D3DXVECTOR2 m_vImgSize;

	map< int, CRender* > m_mapRender;
	wstring m_wsName;
	
	D3DXCOLOR m_pColor;

	RECT m_rcRect;

	vector< CGameObj* > m_vecCollisionObj;
	bool m_bCollisionCheck;
	
	float m_fAngle;

	int m_iRenderTurn;
	int m_iRenderType;

	int m_iState;
	int m_iRadius;

	bool m_bClickObj;
	bool m_bClick;

	bool m_bDestroy;
	bool m_bCamera;

public:
	CGameObj(void);
	virtual ~CGameObj(void);

	CRender* GetRender()
	{ 
		map< int, CRender* >::iterator mit = m_mapRender.find( m_iState );
		if( mit == m_mapRender.end() )
			return  NULL;

		return mit->second;
	}

	void AddRenderState( int iState, wstring wsRenderName );
	
	void AddCollisionObj( CGameObj* pCollisionObj ){ m_vecCollisionObj.push_back( pCollisionObj ); }
	void ClearCollisionObj() { m_vecCollisionObj.clear(); }

	const D3DXVECTOR2* GetPos() { return &m_vPos; }
	void SetPos( D3DXVECTOR2 vPos ) { m_vPos = vPos; }

	const D3DXVECTOR2* GetScl() { return &m_vScl; }
	void SetScl( D3DXVECTOR2 vScl ) { m_vScl = vScl; }

	const D3DXVECTOR2* GetImgSize() { return &m_vImgSize; }
	void SetImgSize( D3DXVECTOR2 vImgSize ) { m_vImgSize = vImgSize; }

	RECT GetRect() { return m_rcRect; }
	void SetRect( RECT rcRect ) { m_rcRect = rcRect; }

	int GetRadius() { return m_iRadius; }
	void SetRadius( int iRadius ) { m_iRadius = iRadius; } 

	float GetAngle() { return m_fAngle; }
	void SetAngle( float fAngle ) { m_fAngle = fAngle; }

	int GetState() { return m_iState; }
	void SetState( int iState ) { m_iState = iState; }
	
	int GetRenderTurn() { return m_iRenderTurn; }
	void SetRenderTurn( int iRenderTurn ) { m_iRenderTurn = iRenderTurn; }

	int GetRenderType() { return m_iRenderType; }
	void SetRenderType( int iRenderType ) { m_iRenderType = iRenderType ; }

	wstring GetName() { return m_wsName; }
	void SetName( wstring wsName ) { m_wsName = wsName; }

	bool IsClickObj() { return m_bClickObj; }
	void SetClickObj( bool bUse ) { m_bClickObj = bUse; }

	bool IsClick() { return m_bClick; }
	void SetClick( bool bUse ) { m_bClick = bUse; }

	bool IsCamera() { return m_bCamera; }
	void SetCamera( bool bCamera ) { m_bCamera = bCamera; }

	bool IsCollisionCheck() { return m_bCollisionCheck; } 
	void SetCollisionCheck( bool bCollisionCheck ) { m_bCollisionCheck = bCollisionCheck; }

	bool IsDestroy() { return m_bDestroy; }
	void SetDestroy( bool bDestroy ) { m_bDestroy = bDestroy; }
	virtual void Destroy() { m_bDestroy = true; }

	D3DXCOLOR GetColor() { return m_pColor; }
	void SetColor( D3DXCOLOR pColor ) { m_pColor = pColor; }

public:
	virtual void OnFrameMove( float fElapsedTime );
	virtual void OnFrameRender();


};
