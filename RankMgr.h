
#pragma once

struct SScoreData
{
	string sName;
	int iScore;
};

class CRankMgr : public CSingleton< CRankMgr >
{
private:
	friend CSingleton< CRankMgr >;

private:
	vector< SScoreData > m_vecRank;
	string m_sFile;

protected:
	CRankMgr();
	virtual ~CRankMgr();

public:
	void Load(const string sFile);
	void Write();

	void AddScoreData(string sName, int iScore);
	void UpdateRank();

	const SScoreData* GetScoreData(int iRank);
};