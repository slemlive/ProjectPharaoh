
#include "DXUT.h"
#include "NameSpace.h"

CGameUI::CGameUI():
m_vPos( 0.0f, 0.0f ),
m_iLayer( 0 ),
m_sColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
m_bDestroy( false )
{

}

CGameUI::~CGameUI()
{

}