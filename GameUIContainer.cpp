
#include "DXUT.h"
#include "NameSpace.h"

CGameUIContainer::CGameUIContainer()
{

}

CGameUIContainer::~CGameUIContainer()
{

}

void CGameUIContainer::ClearUI()
{
	for each(map< int, list< CGameUI* > >::const_reference mr in m_mapUI)
	{
		for each(list< CGameUI* >::const_reference lr in mr.second)
			delete lr;
	}

	m_mapUI.clear();
}

void CGameUIContainer::AddGameUI(CGameUI* pGameUI)
{
	if (pGameUI == NULL)
		return;

	int iLayer = pGameUI->GetLayer();
	m_mapUI[iLayer].push_back(pGameUI);
}

CTextureUI* CGameUIContainer::CreateTextureUI(string sData, D3DXVECTOR2 vPos, D3DXVECTOR2 vLocal, float fRot, int iLayer)
{
	CTextureUI* pTextureUI = new CTextureUI;
	
	*pTextureUI->GetPos() = vPos;
	*pTextureUI->GetLocal() = vLocal;
	*pTextureUI->GetRot() = fRot;
	pTextureUI->SetLayer(iLayer);
	pTextureUI->Load(sData);

	m_mapUI[iLayer].push_back(pTextureUI);
	return pTextureUI;
}

CFontUI* CGameUIContainer::CreateFontUI(string sString, D3DXVECTOR2 vPos, int iFontSize, DWORD dwFormat, int iLayer)
{
	CFontUI* pFontUI = new CFontUI;

	pFontUI->InitFontUI("Arial", iFontSize);
	*pFontUI->GetPos() = vPos;
	pFontUI->SetFormat(dwFormat);
	pFontUI->SetLayer(iLayer);
	pFontUI->SetString(sString);

	m_mapUI[iLayer].push_back(pFontUI);
	return pFontUI;
}

void CGameUIContainer::UpdateUI()
{
	map< int, list< CGameUI* > >::iterator mit = m_mapUI.begin();
	while (mit != m_mapUI.end())
	{
		list< CGameUI* >::iterator lit = mit->second.begin();
		for (lit; lit != mit->second.end(); ++lit)
		{
			CGameUI* pGameUI = *lit;
			if (!pGameUI->IsDestroy())
			{
				continue;
			}

			SAFE_DELETE(pGameUI);
			lit = mit->second.erase(lit);
		}

		if (mit->second.empty())
			mit = m_mapUI.erase(mit);
		else
			++mit;
	}
}