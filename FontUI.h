
#pragma once

class CFontUI : public CGameUI
{
protected:
	LPD3DXFONT m_pFont;

	DWORD m_dwFormat;
	int m_iFontSize;

	string m_sString;

public:
	CFontUI();
	virtual ~CFontUI();

	void InitFontUI(const string sFont, int iFontSize);

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnFrameRender();

	void DrawFont();

public:
	void SetFontSize(int iFontSize) { m_iFontSize = iFontSize; }
	void SetFormat(DWORD dwFormat) { m_dwFormat = dwFormat; }
	void SetString(string sString) { m_sString = sString; }
};