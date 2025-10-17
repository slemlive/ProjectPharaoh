
#pragma once

class CPlayer : public CUnit,
				public CSingleton< CPlayer >
{
private:
	friend CSingleton< CPlayer >;

protected:
	bool m_bBow;

	int m_iRopeCount;
	int m_iTrapCount;

	bool m_bRope;

protected:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender(D3DXMATRIX* pmatLocal);

	void InitPlayerInfo();

public:
	void AddRopeCount(int iCount) { if (m_iRopeCount >= 5) return; m_iRopeCount += iCount; }
	void AddTrapCount(int iCount) { if (m_iTrapCount >= 5) return; m_iTrapCount += iCount; }

	bool IsRope() { return m_bRope; }
	void SetRope(bool bUse) { m_bRope = bUse; }

	bool IsBow() { return m_bBow; }
	void SetBow(bool bBow) { m_bBow = bBow; }
	void ChangeAttack();
};