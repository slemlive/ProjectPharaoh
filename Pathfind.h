
#pragma once

enum EBLUCK
{
	EBS_OPEN,
	EBS_CLOSE,
};

typedef struct SBluck
{
	EBLUCK m_eBluck;
}*LPBLUCK;

class CPathfind : public CSingleton< CPathfind >
{
private:
	friend CSingleton< CPathfind >;

private:
	LPBLUCK* m_ppBluck;

	int m_iWidth;
	int m_iHeight;

protected:
	CPathfind();
	virtual ~CPathfind();

public:
	void Load(const string sFile);
	LPBLUCK GetBluck(int x, int y);
	int GetIndex(float fIndex);
	D3DXVECTOR3 GetNodePos(int x, int y);
	bool CheckBluck(D3DXVECTOR3& vStart, D3DXVECTOR3& vEnd);

	void Pathfind(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd);
};