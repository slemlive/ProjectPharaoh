
#include "DXUT.h"
#include "NameSpace.h"

CFileReader::CFileReader() :
m_pData(NULL),
m_iMaxFileSize(0),
m_iIndex(0),
m_bFail(true)
{

}

CFileReader::CFileReader(const string& sFile):
m_pData( NULL ),
m_iMaxFileSize( 0 ),
m_iIndex( 0 ),
m_bFail( true )
{
	open(sFile);
}

CFileReader::~CFileReader()
{
	Release();
}

void CFileReader::Release()
{
	SAFE_DELETE_ARRAY(m_pData);
	m_iMaxFileSize = 0;
	m_iIndex = 0;
	m_bFail = true;
}

void CFileReader::open(const string& sFile)
{
	fstream os(sFile);
	if (os.fail())
	{
		m_bFail = true;
		return;
	}

	os.seekg(0, fstream::end);
	m_iMaxFileSize = (int)os.tellg();
	os.seekg(0, fstream::beg);
	if (m_iMaxFileSize == 0)
	{
		os.close();
		return;
	}

	m_pData = new char[m_iMaxFileSize];
	ZeroMemory(m_pData, m_iMaxFileSize);

	os.read(m_pData, m_iMaxFileSize);
	os.close();
	
	m_bFail = false;
}

void CFileReader::Continue()
{
	while (!eof())
	{
		char cData = GetData();
		++m_iIndex;

		if (cData == '\n')
			return;
	}
}

string CFileReader::GetLine()
{
	string sCommand;
	while (!eof())
	{
		char cData = GetData();
		++m_iIndex;

		if (cData == '\n')
			return sCommand;

		sCommand.push_back(cData);
	}

	return sCommand;
}

string CFileReader::GetCommand()
{
	string sCommand;
	while (!eof())
	{
		char cData = GetData();
		++m_iIndex;

		if (cData == '\n' ||
			cData == '\t' ||
			cData == '\"' ||
			cData == '"\"' ||
			cData == ' ' ||
			cData == '	' ||
			cData == '\0')
		{
			if (sCommand.empty())
				continue;
			else
				return sCommand;
		}

		sCommand.push_back(cData);
	}

	return sCommand;
}

int CFileReader::GetInt()
{
	string sCommand = GetCommand();
	int iInt = atoi(sCommand.c_str());
	return iInt;
}

float CFileReader::GetFloat()
{
	string sCommand = GetCommand();
	float fFloat = (float)atof(sCommand.c_str());
	return fFloat;
}

double CFileReader::GetDouble()
{
	string sCommand = GetCommand();
	double dDouble = atof(sCommand.c_str());
	return dDouble;
}

long CFileReader::GetLong()
{
	string sCommand = GetCommand();
	long lLong = atol(sCommand.c_str());
	return lLong;
}

DWORD CFileReader::GetDword()
{
	string sCommand = GetCommand();
	DWORD dwDword = (DWORD)atol(sCommand.c_str());
	return dwDword;
}

bool CFileReader::GetBool()
{
	string sCommand = GetCommand();
	bool bBool = false;
	if (sCommand == "true" || sCommand == "TRUE")
		bBool = true;
	else if (sCommand == "false" || sCommand == "FALSE")
		bBool = false;

	return bBool;
}