#include "DXUT.h"
#include "Home.h"


CGameObjContainer::CGameObjContainer(void)
{
}


CGameObjContainer::~CGameObjContainer(void)
{
	DestroyAll();
}

void CGameObjContainer::DestroyAll()
{
	for each( map< int, vector< CGameObj* >>::const_reference mr in m_mapObj )
	{
		for each( vector< CGameObj* >::const_reference vr in mr.second )
			delete vr;
	}

	m_mapObj.clear();
	m_mapRenderObj.clear();
	m_mapReserveObj.clear();
}

CGameObj* CGameObjContainer::CreateObj( int iType, wstring wsName, wstring wsRenderName, D3DXVECTOR2 vPos, float fAngle , bool bCamera, int iRenderType, int iRenderTurn, int iRadius, bool bCollisionCheck )
{
	CGameObj* pObj = Alloc( iType );
	if( pObj == NULL )
		return NULL;

	pObj->SetName( wsName );
	pObj->SetCamera( bCamera );
	pObj->SetState( AT_NORMAL );
	pObj->SetRenderType( iRenderType );
	pObj->SetRenderTurn( iRenderTurn );
	pObj->SetAngle( fAngle );
	pObj->SetPos( vPos );
	pObj->SetRadius( iRadius );
	pObj->SetCollisionCheck( bCollisionCheck );

	pObj->AddRenderState( AT_NORMAL, wsRenderName );

	m_mapReserveObj[iType].push_back( pObj );

	return pObj;
}

void CGameObjContainer::CollisionCheck()
{
	map< int, vector< CGameObj* >>::iterator mit = m_mapObj.begin();
	while( mit != m_mapObj.end() )
	{
		for( int i = (int)mit->second.size()-1; i >= 0; --i )
		{
			if( mit->second[i]->IsCollisionCheck() == false )
				continue ;

			map< int, vector< CGameObj* >>::iterator mit2 = m_mapObj.begin();
			while( mit2 != m_mapObj.end() )
			{
				for( int j = (int)mit2->second.size() -1; j >= 0; --j )
				{
		 			if( mit->second[i] == mit2->second[j] )
						continue ;

					if( mit2->second[j]->IsCollisionCheck() == false )
						continue ;

					float fObjDist = CUtil::CalcDist( mit->second[i], mit2->second[j] );
					int fCollisionDist = mit->second[i]->GetRadius() + mit2->second[j]->GetRadius();

					if( fObjDist <= (float)fCollisionDist )
						mit->second[i]->AddCollisionObj( mit2->second[j] );


				}

				++mit2;
			}
		}
		
		++mit;
	}
}

void CGameObjContainer::ClickCheck()
{
	map< int, vector< CGameObj* > >::iterator mit = m_mapObj.begin();
	while( mit != m_mapObj.end() )
	{
		for( int i = (int)mit->second.size() - 1; i >= 0; --i )
		{
			if( mit->second[i]->IsClickObj() == false )
				continue;

			if( mit->second[i]->GetState() == AT_DIE )
				continue;

			RECT rcRect = mit->second[i]->GetRect();
			if( PtInRect( &rcRect, D_GAMESTAGEMGR->GetMousePos() ) )
			{
				if( D_GAMESTAGEMGR->IsClickOn() == true )
				{
					mit->second[i]->SetClick( true );
					return;
				}
			}
		}
		
		++mit;
	}
}

void CGameObjContainer::PostProcess()
{
	for each( map< int, vector< CGameObj* >>::const_reference mr in m_mapReserveObj )
	{
		vector< CGameObj* >& vecObj = m_mapObj[mr.first];
		vecObj.insert( vecObj.end(), mr.second.begin(), mr.second.end() );
	}

	m_mapReserveObj.clear();
	m_mapRenderObj.clear();

	map< int, vector< CGameObj* >>::iterator mit = m_mapObj.begin();
	while( mit != m_mapObj.end() )
	{	
		for( int i = (int)mit->second.size()-1; i >= 0; --i )
		{
			mit->second[i]->ClearCollisionObj();

			if( mit->second[i]->IsDestroy() == false )
			{
				int iRenderTurn = mit->second[i]->GetRenderTurn();
				m_mapRenderObj[iRenderTurn].push_back( mit->second[i] );

				continue ;
			}
			
			SAFE_DELETE( mit->second[i] );
			mit->second.erase( mit->second.begin() + i );
		}

		if( mit->second.empty() )
			mit = m_mapObj.erase( mit );
		else
			++mit;

	}
}