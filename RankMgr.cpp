
#include "DXUT.h"
#include "NameSpace.h"

CRankMgr::CRankMgr()
{

}

CRankMgr::~CRankMgr()
{

}

void CRankMgr::Load(const string sFile)
{
	frstream InFile(sFile);
	if (InFile.fail())
		return;

	SScoreData sScoreData;
	string sCommand;
	while (!InFile.eof())
	{
		InFile >> sCommand;

		if (sCommand == "Rank:")
		{
			string sName;
			int iRank, iScore;
			ZeroMemory(&sScoreData, sizeof(SScoreData));

			InFile >> iRank >> sName >> iScore;
			sScoreData.iScore = iScore;
			sScoreData.sName = sName;

			m_vecRank.push_back(sScoreData);
		}
	}

	m_sFile = sFile;
}

void CRankMgr::UpdateRank()
{
	for (int i = 0; i < (int)m_vecRank.size(); ++i)
	{
		for (int j = 0; j < (int)m_vecRank.size(); ++j)
		{
			if (i == j)
				continue;

			if (m_vecRank[i].iScore > m_vecRank[j].iScore)
			{
				SScoreData sTemp = m_vecRank[i];
				m_vecRank[i] = m_vecRank[j];
				m_vecRank[j] = sTemp;
			}
		}
	}
}

void CRankMgr::AddScoreData(string sName, int iScore)
{
	SScoreData sScoreData;
	sScoreData.iScore = iScore;
	sScoreData.sName = sName;
	m_vecRank.push_back(sScoreData);
}

void CRankMgr::Write()
{
	ofstream InFile(m_sFile);
	if (InFile.fail())
		return;

	InFile.clear();
	for (int i = 0; i < (int)4; ++i)
	{
		SScoreData& sScoreData = m_vecRank[i];
		InFile << "Rank:\t" << i + 1 << "\t" << sScoreData.sName << "\t" << sScoreData.iScore << endl;
	}
}

const SScoreData* CRankMgr::GetScoreData(int iRank)
{
	if ((int)m_vecRank.size() - 1 < iRank)
		return NULL;

	return &m_vecRank[iRank];
}