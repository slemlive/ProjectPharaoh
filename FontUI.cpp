
#include "DXUT.h"
#include "NameSpace.h"

CFontUI::CFontUI() :
m_pFont(NULL),
m_dwFormat(NULL),
m_iFontSize(0)
{

}

CFontUI::~CFontUI()
{
	SAFE_RELEASE(m_pFont);
}

void CFontUI::InitFontUI(const string sFont, int iFontSize)
{
	if (m_pFont != NULL)
		return;

	m_iFontSize = iFontSize;
	if (FAILED(D3DXCreateFontA(DXUTGetD3D9Device(),
		m_iFontSize,
		0,
		FW_BOLD,
		1,
		false,
		HANGUL_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		sFont.c_str(),
		&m_pFont)))
		return;
}

void CFontUI::DrawFont()
{
	if (m_pFont == NULL)
		return;

	D3DXMATRIX matWorld;
	D3DXMatrixTranslation(&matWorld, m_vPos.x, m_vPos.y, 0.0f);
	D_SPRITE->SetTransform(&matWorld);
	RECT rcRect = { 0, 0, -1, -1 };
	m_pFont->DrawTextA(D_SPRITE->GetD3DSprite(), m_sString.c_str(),
		-1, &rcRect, DT_NOCLIP | m_dwFormat, m_sColor);
}

void CFontUI::OnFrameMove(float fElapsedTime)
{

}

void CFontUI::OnFrameRender()
{
	DrawFont();
}