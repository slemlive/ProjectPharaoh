
#pragma once

typedef class CFileReader
{
private:
	char* m_pData;
	int m_iMaxFileSize;
	int m_iIndex;

	bool m_bFail;

public:
	CFileReader();
	explicit CFileReader(const string& sFile);
	virtual ~CFileReader();

	void open(const string& sFile);
	void Release();

	void Continue();
	string GetLine();

	bool fail() { return m_bFail; }
	bool eof() { if (m_iMaxFileSize <= m_iIndex) return true; return false; }

private:
	string GetCommand();
	int GetInt();
	float GetFloat();
	double GetDouble();
	long GetLong();
	DWORD GetDword();
	bool GetBool();

	char GetData() { return m_pData[m_iIndex]; }

public:
	CFileReader& operator>> (string& sCommand) { sCommand = GetCommand(); return *this; }
	CFileReader& operator>> (int& iInt) { iInt = GetInt(); return *this; }
	CFileReader& operator>> (float& fFloat) { fFloat = GetFloat(); return *this; }
	CFileReader& operator>> (double& dDouble) { dDouble = GetDouble(); return *this; }
	CFileReader& operator>> (long& lLong) { lLong = GetLong(); return *this; }
	CFileReader& operator>> (DWORD& dwDword) { dwDword = GetDword(); return *this; }
	CFileReader& operator>> (bool& bBool) { bBool = GetBool(); return *this; }

}frstream;