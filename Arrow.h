
#pragma once

class CArrow : public CGameObj
{
protected:
	float m_fSpeed;
	CUnit* m_pTarget;
	int m_iDmg;

public:
	CArrow();
	virtual ~CArrow();

	void MoveArrow(float fElapsedTime);

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender(D3DXMATRIX* pmatLocal);

public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }

	int GetDmg() { return m_iDmg; }
	void SetDmg(int iDmg) { m_iDmg = iDmg; }

	bool IsTarget() { if (m_pTarget == NULL) return false; return true; }
	void SetTarget(CUnit* pTarget) { m_pTarget = pTarget; }
};