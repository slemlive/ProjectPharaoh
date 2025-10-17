#pragma once

class CGameObj;

namespace CUtil
{
	float CalcDist( CGameObj* pObj1, CGameObj* pObj2 );
	float CalcDist( CGameObj* pObj, const D3DXVECTOR2* vPos );
	float CalcDist( const D3DXVECTOR2* pPos1, const D3DXVECTOR2* pPos2 );
}