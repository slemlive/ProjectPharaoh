
#include "DXUT.h"
#include "NameSpace.h"

CPathfind::CPathfind():
m_ppBluck( NULL ),
m_iWidth( 0 ),
m_iHeight( 0 )
{

}

CPathfind::~CPathfind()
{

}

void CPathfind::Load(const string sFile)
{
	BITMAPFILEHEADER* fileheader;
	BITMAPINFOHEADER* infoheader;
	RGBQUAD* rgb;

	ofstream os("Text.txt");
	FILE* InFile = fopen(sFile.c_str(), "rb");
	if (!InFile)
		return;

	fseek(InFile, 0, SEEK_END);
	int iSize = ftell(InFile);
	fseek(InFile, 0, SEEK_SET);

	char* pBuffer = new char[iSize];
	fread(pBuffer, iSize, 1, InFile);
	fclose(InFile);

	fileheader = (BITMAPFILEHEADER*)pBuffer;
	infoheader = (BITMAPINFOHEADER*)(pBuffer + sizeof(BITMAPFILEHEADER));
	rgb = (RGBQUAD*)(pBuffer + sizeof(RGBQUAD) * 256);

	m_iWidth = infoheader->biWidth;
	m_iHeight = infoheader->biHeight;

	char* pImage = pBuffer + fileheader->bfOffBits;
	DWORD dwPitch = ((infoheader->biBitCount >> 3) * infoheader->biWidth + 3) & ~3;
	m_ppBluck = new LPBLUCK[infoheader->biHeight];
	for (LONG y = 0; y < infoheader->biHeight; ++y)
	{
		m_ppBluck[y] = new SBluck[infoheader->biWidth];
		for (LONG x = 0; x < infoheader->biWidth; ++x)
		{
			DWORD idx = ((infoheader->biHeight - 1 - y) * dwPitch + x);
			BYTE sPixel = rgb[pImage[idx]].rgbBlue + rgb[pImage[idx]].rgbGreen + rgb[pImage[idx]].rgbRed;
			if (sPixel == 0)
				m_ppBluck[y][x].m_eBluck = EBS_OPEN;
			else
				m_ppBluck[y][x].m_eBluck = EBS_CLOSE;
		}
	}
	SAFE_DELETE_ARRAY(pBuffer);
}

LPBLUCK CPathfind::GetBluck(int x, int y)
{
	return &m_ppBluck[y][x];
}

int CPathfind::GetIndex(float fIndex)
{
	return (int)(fIndex / 10);
}

bool CPathfind::CheckBluck(D3DXVECTOR3& vStart, D3DXVECTOR3& vEnd)
{
	int iStartX = GetIndex(vStart.x);
	int iStartY = GetIndex(vStart.y);
	int iEndX = GetIndex(vEnd.x);
	int iEndY = GetIndex(vEnd.y);

	LPBLUCK pBluck = GetBluck(iStartX, iStartY);
	LPBLUCK pBluck2 = GetBluck(iEndX, iEndY);
	if (pBluck == pBluck2)
		return true;

	return false;
}

void CPathfind::Pathfind(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd)
{
	if (CheckBluck(vStart, vEnd))
		return;

	int iStartX = GetIndex(vStart.x);
	int iStartY = GetIndex(vStart.y);
	int iEndX = GetIndex(vEnd.x);
	int iEndY = GetIndex(vEnd.y);

	vector< D3DXVECTOR3 > vList;
	for (int y = iStartY - 1; y < iStartY + 2; ++y)
	{
		if (y < 0 || y > m_iWidth)
			continue;

		for (int x = iStartX - 1; x < iStartX + 2; ++x)
		{
			if (x < 0 || x > m_iHeight)
				continue;

			if (y == iStartY && x == iStartX)
				continue;

			vList.push_back(GetNodePos(x, y));
		}
	}
}

D3DXVECTOR3 CPathfind::GetNodePos(int x, int y)
{
	return D3DXVECTOR3((float)x, 0.0f, (float)y);
}