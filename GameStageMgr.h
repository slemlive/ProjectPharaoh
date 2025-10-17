#pragma once

class CGameStage;

enum ESTAGE
{
	ESTAGE_INTRO,
	ESTAGE_MAINMENU,
	ESTAGE_WAY,
	ESTAGE_RANK,
	ESTAGE_REPORT,
	ESTAGE_STAGE1,
	ESTAGE_STAGE2,
	ESTAGE_STAGE3,
	ESTAGE_SCORE,
	ESTAGE_ENDING,
};

class CGameStageMgr
{
private:
	static CGameStageMgr* m_pStageMgr;
	CGameStage* m_pStage;
	
	int m_iScore;
	int m_iCombo;
	float m_fComboTime;

	int m_iBombGage;

	int m_iStage;

	POINT m_vMousePos;
	bool m_bClickOn;

	bool m_bFever;
	bool m_bGameStart;

	float m_fFeverTime;
	float m_fGameTimmer;

	float m_fCountDown;

public:
	CGameStageMgr(void);
	virtual ~CGameStageMgr(void); 

	static CGameStageMgr* GetStageMgr() { if( m_pStageMgr == NULL ) m_pStageMgr = new CGameStageMgr; return m_pStageMgr; }

	int GetScore() { return m_iScore; }
	void AddScore( int iScore ) { m_iScore += iScore; }
	void ResetScore() { m_iScore = 0; }

	int GetCombo() { return m_iCombo; }
	void AddCombo() { m_iCombo += 1; m_fComboTime = 0.0f; }
	void ResetCombo() { m_iCombo = 0; }

	POINT GetMousePos() { return m_vMousePos; }
	void SetMousePos( POINT vMousePos ) { m_vMousePos = vMousePos; }

	float GetGameTimmer() { return m_fGameTimmer; }
	void SetGameTimmer( float fNum ) { m_fGameTimmer = fNum; }
	void SubGameTimmer( float fNum ) { m_fGameTimmer -= fNum; }

	bool IsClickOn() { return m_bClickOn; }
	void SetClickOn( bool bUse ) { m_bClickOn = bUse; }

	bool IsGameStart() { return m_bGameStart; }
	void SetGameStart( bool bUse ) { m_bGameStart = bUse; }

	int GetBombGage() { return m_iBombGage; }
	void SetBombGage( int iGage ) { m_iBombGage = iGage; }
	void AddBombGage( int iGage ) { m_iBombGage += iGage; }
	void SubBombGage( int iGage ) { m_iBombGage -= iGage; }

	float GetCountDown() { return m_fCountDown; }
	void ResetCountDown() { m_fCountDown = 0.0f; }
	void AddCountDown( float fAdd ) { m_fCountDown += fAdd; }

	float GetFeverTime() { return m_fFeverTime; }
	void SetFeverTime( float fTime ) { m_fFeverTime = fTime; }
	void ResetFeverTime() { m_fFeverTime = 10.0f; }
	void SubFeverTime( float fTime ) { m_fFeverTime -= fTime; }

	bool IsFever() { return m_bFever; }
	void SetFever( bool bUse ) { m_bFever = bUse; }

	void ChangeStage( int iStage );
	void OnFrameMove( float fElapsedTime );
	void OnFrameRender();
};

