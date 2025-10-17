
#pragma once

class CScore : public CSingleton< CScore >
{
private:
	friend CSingleton< CScore >;

private:
	int m_iScore;

protected:
	CScore();
	virtual ~CScore();

public:
	void AddScore(int iScore) { m_iScore += iScore; }
	void ResetScore() { m_iScore = 0; }
	
	int GetScore() { return m_iScore; }
};