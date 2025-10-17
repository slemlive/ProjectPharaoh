
#pragma once

class CUnit : public CGameObj
{
protected:
	CGameObj* m_pHp;
	D3DXVECTOR3 m_vHpPos;

	CUnit* m_pTarget;
	D3DXVECTOR3 m_vTargetPos;
	float m_fSpeed;

	map< ESTATE, int > m_mapAttackIndex;
	bool m_bAttackCheck;

	int m_iHp;
	int m_iMaxHp;

	int m_iDmg;
	int m_iPoint;

	float m_fAttackTime;
	float m_fAttackSpeed;

	float m_fAttackDist;
	float m_fRad;

	bool m_bGodMode;

	float m_fHoldTime;
	float m_fHoldSpeed;
	bool m_bHold;

	vector< CUnit* > m_vecCollision;

public:
	CUnit();
	virtual ~CUnit();

	virtual void UpdateState();
	virtual void UpdateTarget();

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender(D3DXMATRIX* pmatLocal);

public:
	void SetTargetPos(D3DXVECTOR3 vPos);
	void SetTargetUnit(CUnit* pTarget);

	vector< CUnit* >* GetCollision() { return &m_vecCollision; }

	int GetDmg() { return m_iDmg; }
	void SetDmg(int iDmg) { m_iDmg = iDmg; }
	void OnDmg(int iDmg);

	int GetHp() { return m_iHp; }
	void SetHp(int iHp) { m_iHp = iHp; }

	void SetPoint(int iPoint) { m_iPoint = iPoint; }
	int GetPoint() { return m_iPoint; }
	
	int GetMaxHp() { return m_iMaxHp; }
	void SetMaxHp(int iMaxHp) { m_iMaxHp = iMaxHp; }

	void SetAttackSpeed(float fAttackSpeed) { m_fAttackSpeed = fAttackSpeed; }

	float GetAttackDist() { return m_fAttackDist; }
	void SetAttackDist(float fDist) { m_fAttackDist = fDist; }

	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }

	float GetRad() { return m_fRad; }
	void SetRad(float fRad) { m_fRad = fRad; }

	void SetHpPos(D3DXVECTOR3 vPos) { m_vHpPos = vPos; }

	bool IsGodMode() { return m_bGodMode; }
	void SetGodMode(bool bGod) { m_bGodMode = bGod; }
	void SetHold(bool bHold) { m_bHold = bHold; }

	void AddAttackIndex(ESTATE eState, int iIndex);
	void UpdateHold(float fElapsedTime);

protected:
	virtual void OnNormal();
	virtual void OnMove();
	virtual void OnAttack();
	virtual void OnDie();

	virtual void UpdateAI();
	virtual void UpdateCollisionCheck();
};