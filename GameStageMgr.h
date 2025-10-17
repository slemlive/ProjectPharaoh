
#pragma once

#define D_LIGHTSPEED 0.01f;

enum ESTAGE
{
	ES_NEW,
	ES_LOADING,
	ES_INTRO,
	ES_MAIN,
	ES_INTRODUCE,
	ES_EXPLAYIN,
	ES_RANKING,
	ES_STAGE1,
	ES_STAGE2,
	ES_ENDING,
	ES_SCORE,
};

class CGameStageMgr : public CSingleton< CGameStageMgr >
{
private:
	friend CSingleton< CGameStageMgr >;

private:
	CStage* m_pStage;
	ESTAGE m_eStage;
	bool m_bChange;

	string m_sString;
	bool m_bKey;

	D3DLIGHT9 m_sLight;

protected:
	CGameStageMgr();
	virtual ~CGameStageMgr();

	CStage* Alloc(ESTAGE eStage);

public:
	void ChangeStage(ESTAGE eStage);
	void UpdateStage();
	void UpdateCheat();

	bool IsKey() { return m_bKey; }
	void SetKey(bool bKey) { m_bKey = bKey; }

	string GetString() { return m_sString; }
	void AddString(char chChar) { m_sString.push_back(chChar); }
	void ClearString() { m_sString.clear(); }
	void BackString() { if(!m_sString.empty()) m_sString.pop_back(); }

	D3DLIGHT9* GetLight() { return &m_sLight; }
	void ClearLight();
	void StartLight();

	void OnFrameMove(float fElapsedTime);
	void OnFrameRender();
};