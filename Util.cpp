#include "DXUT.h"
#include "Home.h"

float CUtil::CalcDist( CGameObj* pObj1, CGameObj* pObj2 )
{
	D3DXVECTOR2 vLen = *pObj2->GetPos()  - *pObj1->GetPos();
	
	return D3DXVec2Length( &vLen );
}

float CUtil::CalcDist( CGameObj* pObj, const D3DXVECTOR2* pPos )
{
	D3DXVECTOR2 vLen = *pObj->GetPos() - *pPos;
	return D3DXVec2Length( &vLen );
}  

float CUtil::CalcDist( const D3DXVECTOR2* pPos1, const D3DXVECTOR2* pPos2 )
{
	D3DXVECTOR2 vLen = *pPos1 - *pPos2;
	return D3DXVec2Length( &vLen );
}