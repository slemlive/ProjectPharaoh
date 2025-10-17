
#include "DXUT.h"
#include "Home.h"

CPuzzleMgr* CPuzzleMgr::m_pPuzzleMgr;

CPuzzleMgr::CPuzzleMgr():
m_iWidth( 0 ),
m_iHeight( 0 ),
m_pTarget1( NULL ),
m_pTarget2( NULL ),
m_fHintTime( 0.0f ),
m_fTimeOut( 0.0f ),
m_vPuzzlePos( 0.0f, 0.0f )
{
	m_pPuzzleMgr = NULL;
}

CPuzzleMgr::~CPuzzleMgr()
{
	DestroyPuzzle();
}

void CPuzzleMgr::DestroyPuzzle()
{
	map< int, vector< CPuzzle* > >::iterator mit = m_mapPuzzle.begin();
	while( mit != m_mapPuzzle.end() )
	{
		for( int i = 0; i < (int)mit->second.size(); ++i )
		{
			if( mit->second[i]->IsDestroy() == false )
				mit->second[i]->Destroy();
		}
		mit->second.clear();

		++mit;
	}

	m_mapPuzzle.clear();
}

void CPuzzleMgr::ClearPuzzle()
{
	map< int, vector< CPuzzle* > >::iterator mit = m_mapPuzzle.begin();
	while( mit != m_mapPuzzle.end() )
	{
		mit->second.clear();
		++mit;
	}

	m_mapPuzzle.clear();
}

void CPuzzleMgr::CreatePuzzle( int iWidth, int iHeight, D3DXVECTOR2 vPos )
{
	srand( (int)time( NULL ) );

	m_vPuzzlePos = vPos;

	m_iWidth = iWidth;
	m_iHeight = iHeight;

	for( int i = 1; i <= iWidth; ++i )
	{
		for( int j = 1; j <= iHeight; ++j )
		{
			int iRand = rand()%iHeight + 1;

			wstringstream os;
			os << L"°úÀÏ" << iRand;

			CPuzzle* pObj = (CPuzzle*)D_GAMEOBJMGR->CreateObj( EGAMEOBJ_PUZZLE, os.str(), L"¹°¹æ¿ï", D3DXVECTOR2( vPos.x + ( 64 * (float)i ), vPos.y - ( 64 * (float)j ) ), 0, false, ERENDER_LEFTUP, 1, 0, false );
			pObj->SetKey( i );
			pObj->SetCount( j );

			m_mapPuzzle[i].push_back( pObj );
		}
	}
}

void CPuzzleMgr::OnFrameMove( float fElapsedTime )
{
	if( D_GAMESTAGEMGR->IsGameStart() == false )
		return;

	m_fTimeOut += fElapsedTime;
	if( m_fTimeOut >= 10.0f )
	{
		D_GAMESTAGEMGR->SetGameStart( true );
	}
	else
		m_fHintTime += fElapsedTime;
	
	if( m_fHintTime >= 3.0f )
	{
		map< int, vector< CPuzzle* > >::iterator mitHint = m_mapPuzzle.begin();
		while( mitHint != m_mapPuzzle.end() )
		{
			if( m_vecHint.size() >= 3 )
				break;

			for( int i = 0; i < (int)mitHint->second.size(); ++i )
			{
				if( i == m_iHeight - 1 )
					continue;

				CPuzzle* pHint = mitHint->second[i];
				mitHint->second[i] = mitHint->second[i+1];
				mitHint->second[i+1] = pHint;

				mitHint->second[i]->SetCount( i );
				mitHint->second[i+1]->SetCount( i + 1 );
				mitHint->second[i]->SetKey( mitHint->first );
				mitHint->second[i+1]->SetKey( mitHint->first );

				for( int j = 0; j < (int)mitHint->second.size(); ++j )
				{
					if( m_vecHint.empty() == true )
						m_vecHint.push_back( mitHint->second[j] );
					else
					{
						if( m_vecHint[m_vecHint.size()-1]->GetName() == mitHint->second[j]->GetName() /*&&
							m_vecHint[m_vecHint.size()-1]->GetCount() + 1 == mitHint->second[j]->GetCount()*/ )
							m_vecHint.push_back( mitHint->second[j] );
						else
						{
							if( m_vecHint.size() >= 3 )
							{
								m_fHintTime = 0.0f;
								break;
							}
							else
							{
								m_vecHint.clear();
								m_vecHint.push_back( mitHint->second[j] );
							}
						}
					}

					if( j == (int)mitHint->second.size() -1 )
					{
						if( m_vecHint.size() < 3 )
							m_vecHint.clear();
					}
				}

				map< int, vector< CPuzzle* > >::iterator mitHint2 = m_mapPuzzle.begin();
				while( mitHint2 != m_mapPuzzle.end() )
				{
					if( m_vecHint.empty() == true )
						m_vecHint.push_back( mitHint2->second[i] );
					else
					{
						if( m_vecHint[m_vecHint.size()-1]->GetKey() + 1 == mitHint2->second[i]->GetKey() &&
							m_vecHint[m_vecHint.size()-1]->GetName() == mitHint2->second[i]->GetName() )
							m_vecHint.push_back( mitHint2->second[i] );
						else
						{
							if( m_vecHint.size() >= 3 )
							{
								m_fHintTime = 0.0f;
								break;
							}
							else
							{
								m_vecHint.clear();
								m_vecHint.push_back( mitHint2->second[i] );
							}
						}

						if( i == (int)mitHint2->second.size() - 1 )
						{
							if( m_vecHint.size() < 3 )
								m_vecHint.clear();
						}

						++mitHint2;
					}
				}

				CPuzzle* pHint2 = mitHint->second[i];
				mitHint->second[i] = mitHint->second[i+1];
				mitHint->second[i+1] = pHint2;

				mitHint->second[i]->SetCount( i );
				mitHint->second[i+1]->SetCount( i + 1 );
				mitHint->second[i]->SetKey( mitHint->first );
				mitHint->second[i+1]->SetKey( mitHint->first );

				if( m_vecHint.size() >= 3 )
					break;
				else
					m_vecHint.clear();
			}

			++mitHint;
		}

		for( int i = 0; i < (int)m_iWidth; ++i )
		{
			map< int, vector< CPuzzle* > >::iterator mitHint1 = m_mapPuzzle.begin();
			while( mitHint1 != m_mapPuzzle.end() )
			{
				map< int, vector< CPuzzle* > >::iterator mitHint2 = m_mapPuzzle.begin();
				while( mitHint2 != m_mapPuzzle.end() )
				{
					if( abs( mitHint1->first - mitHint2->first ) == 1 )
					{
						CPuzzle* pHint = mitHint1->second[i];
						mitHint1->second[i] = mitHint2->second[i];
						mitHint2->second[i] = pHint;

						mitHint1->second[i]->SetKey( mitHint1->first );
						mitHint2->second[i]->SetKey( mitHint2->first );

						for( int j = 0; j < (int)mitHint2->second.size(); ++j )
						{
							if( m_vecHint.empty() == true )
								m_vecHint.push_back( mitHint2->second[j] );
							else
							{
								if( m_vecHint[m_vecHint.size()-1]->GetName() == mitHint2->second[j]->GetName() &&
									m_vecHint[m_vecHint.size()-1]->GetCount() + 1 == mitHint2->second[j]->GetCount() )
									m_vecHint.push_back( mitHint2->second[j] );
								else
								{
									if( m_vecHint.size() >= 3 )
									{
										m_fHintTime = 0.0f;
										break;
									}
									else
									{
										m_vecHint.clear();
										m_vecHint.push_back( mitHint2->second[j] );
									}
								}
							}
						}

						map< int, vector< CPuzzle* > >::iterator mitHint3 = m_mapPuzzle.begin();
						while( mitHint3 != m_mapPuzzle.end() )
						{
							if( m_vecHint.empty() == true )
								m_vecHint.push_back( mitHint3->second[i] );
							else
							{
								if( m_vecHint[m_vecHint.size()-1]->GetName() == mitHint3->second[i]->GetName() &&
									m_vecHint[m_vecHint.size()-1]->GetKey() + 1 == mitHint3->second[i]->GetKey() )
									m_vecHint.push_back( mitHint3->second[i] );
								else
								{
									if( m_vecHint.size() >= 3 )
									{
										m_fHintTime = 0.0f;
										break;
									}
									else
									{
										m_vecHint.clear();
										m_vecHint.push_back( mitHint3->second[i] );
									}
								}
							}

							++mitHint3;
						}

						CPuzzle* pHint2 = mitHint1->second[i];
						mitHint1->second[i] = mitHint2->second[i];
						mitHint2->second[i] = pHint2;

						mitHint1->second[i]->SetKey( mitHint1->first );
						mitHint2->second[i]->SetKey( mitHint2->first );
					}

					++mitHint2;
				}

				++mitHint1;
			}
		}

		if( m_vecHint.size() < 3 )
		{
			m_vecHint.clear();
			map< int, vector< CPuzzle* > >::iterator mitHint3 = m_mapPuzzle.begin();
			while( mitHint3 != m_mapPuzzle.end() )
			{
				for( int i = 0; i < (int)mitHint3->second.size(); ++i )
				{
					if( mitHint3->second[i]->GetName() == L"¾ÆÀÌÅÛ" ||
						mitHint3->second[i]->GetName() == L"ÆøÅº" )
					{
						m_vecHint.push_back( mitHint3->second[i] );
					}
				}
				++mitHint3;
			}

			if( m_vecHint.empty() == false )
			{
				if( m_vecHint[0]->GetName() == L"¾ÆÀÌÅÛ" ||
					m_vecHint[0]->GetName() == L"ÆøÅº" )
				{
					m_vecHint.clear();
					m_fHintTime = 0.0f;
				}
			}
			else
			{
				DestroyPuzzle();
				CreatePuzzle( m_iWidth, m_iHeight, m_vPuzzlePos );
			}
		}

		m_fHintTime = 0.0f;
	}

	if( m_vecHint.empty() == false )
	{
		for( int i = 0; i < (int)m_vecHint.size(); ++i )
		{
			if( m_vecHint.size() >= 3 )
			{
				if( m_vecHint[i]->GetState() != AT_HINT )
				{
					m_vecHint[i]->AddRenderState( AT_HINT, L"¹°¹æ¿ïÈùÆ®" );
					m_vecHint[i]->SetState( AT_HINT );
				}
			}
		}
		m_vecHint.clear();
	}

	map< int, vector< CPuzzle* > >::iterator mit = m_mapPuzzle.begin();
	while( mit != m_mapPuzzle.end() )
	{
		SPuzzleLine sHeightLine;
		for( int i = 0; i < (int)mit->second.size(); ++i )
		{
			if( mit->second[i]->GetPos()->y == m_vPuzzlePos.y - ( 64 * (float)mit->second[i]->GetCount() ) &&
				mit->second[i]->GetPos()->x == m_vPuzzlePos.x + ( 64 * (float)mit->second[i]->GetKey() ) )
			{
				if( sHeightLine.m_vecPuzzleLine.empty() == true )
					sHeightLine.m_vecPuzzleLine.push_back( mit->second[i] );
				else
				{
					if( sHeightLine.m_vecPuzzleLine[(int)sHeightLine.m_vecPuzzleLine.size()-1]->GetName() == mit->second[i]->GetName() &&
						sHeightLine.m_vecPuzzleLine[(int)sHeightLine.m_vecPuzzleLine.size()-1]->GetCount() + 1 == mit->second[i]->GetCount() )
						sHeightLine.m_vecPuzzleLine.push_back( mit->second[i] );
					else
					{
						if( (int)sHeightLine.m_vecPuzzleLine.size() >= 3 )
						{
							m_vecPuzzleLine.push_back( sHeightLine );
							sHeightLine.m_vecPuzzleLine.clear();
							sHeightLine.m_vecPuzzleLine.push_back( mit->second[i] );

							if( D_GAMESTAGEMGR->IsFever() == true )
							{
								SPuzzleLine sFever;

								map< int, vector< CPuzzle* > >::iterator mitFever1 = m_mapPuzzle.find( sHeightLine.m_vecPuzzleLine[0]->GetKey() - 1 );
								if( mitFever1 != m_mapPuzzle.end() )
									sFever.m_vecPuzzleLine.push_back( mitFever1->second[i-1] );

								map< int, vector< CPuzzle* > >::iterator mitFever2 = m_mapPuzzle.find( sHeightLine.m_vecPuzzleLine[0]->GetKey() + 1 );
								if( mitFever2 != m_mapPuzzle.end() )
									sFever.m_vecPuzzleLine.push_back( mitFever2->second[i-1] );

								m_vecPuzzleLine.push_back( sFever );
							}
						}
						else
						{
							sHeightLine.m_vecPuzzleLine.clear();
							sHeightLine.m_vecPuzzleLine.push_back( mit->second[i] );
						}
					}

					if( i >= (int)mit->second.size() - 1 )
					{
						if( (int)sHeightLine.m_vecPuzzleLine.size() >= 3 )
						{
							m_vecPuzzleLine.push_back( sHeightLine );

							if( D_GAMESTAGEMGR->IsFever() == true )
							{
								SPuzzleLine sFever;

								map< int, vector< CPuzzle* > >::iterator mitFever1 = m_mapPuzzle.find( sHeightLine.m_vecPuzzleLine[0]->GetKey() - 1 );
								if( mitFever1 != m_mapPuzzle.end() )
									sFever.m_vecPuzzleLine.push_back( mitFever1->second[i-1] );

								map< int, vector< CPuzzle* > >::iterator mitFever2 = m_mapPuzzle.find( sHeightLine.m_vecPuzzleLine[0]->GetKey() + 1 );
								if( mitFever2 != m_mapPuzzle.end() )
									sFever.m_vecPuzzleLine.push_back( mitFever2->second[i-1] );

								m_vecPuzzleLine.push_back( sFever );
							}
						}
					}
				}
			}
		}

		++mit;
	}

	for( int i = 0; i < m_iWidth; ++i )
	{
		SPuzzleLine sWidthLine;
		map< int, vector< CPuzzle* > >::iterator mitWidth = m_mapPuzzle.begin();
		while( mitWidth != m_mapPuzzle.end() )
		{
			if( mitWidth->second[i]->GetPos()->x == m_vPuzzlePos.x + ( 64 * mitWidth->second[i]->GetKey() ) &&
				mitWidth->second[i]->GetPos()->y == m_vPuzzlePos.y - ( 64 * mitWidth->second[i]->GetCount() ) )
			{
				if( sWidthLine.m_vecPuzzleLine.empty() == true )
					sWidthLine.m_vecPuzzleLine.push_back( mitWidth->second[i] );
				else
				{
					if( sWidthLine.m_vecPuzzleLine[(int)sWidthLine.m_vecPuzzleLine.size()-1]->GetName() == mitWidth->second[i]->GetName() &&
						sWidthLine.m_vecPuzzleLine[(int)sWidthLine.m_vecPuzzleLine.size()-1]->GetKey() + 1 == mitWidth->second[i]->GetKey() )
						sWidthLine.m_vecPuzzleLine.push_back( mitWidth->second[i] );
					else
					{
						if( (int)sWidthLine.m_vecPuzzleLine.size() >= 3 )
						{
							m_vecPuzzleLine.push_back( sWidthLine );
							sWidthLine.m_vecPuzzleLine.clear();
							sWidthLine.m_vecPuzzleLine.push_back( mitWidth->second[i] );

							if( D_GAMESTAGEMGR->IsFever() == true )
							{
								SPuzzleLine sFever;

								map< int, vector< CPuzzle* > >::iterator mitFever = m_mapPuzzle.find( sWidthLine.m_vecPuzzleLine[0]->GetKey() );
								if( mitFever != m_mapPuzzle.end() )
								{
									if( mitFever->second[i]->GetCount() - 1 > 0 )
										sFever.m_vecPuzzleLine.push_back( mitFever->second[i-1] );

									if( mitFever->second[i]->GetCount() < m_iHeight )
										sFever.m_vecPuzzleLine.push_back( mitFever->second[i+1] );

									m_vecPuzzleLine.push_back( sFever );
								}
							}
						}
						else
						{
							sWidthLine.m_vecPuzzleLine.clear();
							sWidthLine.m_vecPuzzleLine.push_back( mitWidth->second[i] );
						}
					}
					
					if( mitWidth->first >= m_iWidth )
					{
						if( (int)sWidthLine.m_vecPuzzleLine.size() >= 3 )
						{
							m_vecPuzzleLine.push_back( sWidthLine );

							if( D_GAMESTAGEMGR->IsFever() == true )
							{
								SPuzzleLine sFever;

								map< int, vector< CPuzzle* > >::iterator mitFever = m_mapPuzzle.find( sWidthLine.m_vecPuzzleLine[0]->GetKey() );
								if( mitFever != m_mapPuzzle.end() )
								{
									if( mitFever->second[i]->GetCount() - 1 > 0 )
										sFever.m_vecPuzzleLine.push_back( mitFever->second[i-1] );

									if( mitFever->second[i]->GetCount() < m_iHeight )
										sFever.m_vecPuzzleLine.push_back( mitFever->second[i+1] );

									m_vecPuzzleLine.push_back( sFever );
								}
							}
						}
					}
				}
			}
			
			++mitWidth;
		}
	}

	map< int, vector< CPuzzle* > >::iterator mitBomb = m_mapPuzzle.begin();
	while( mitBomb != m_mapPuzzle.end() )
	{
		for( int i = 0; i < (int)mitBomb->second.size(); ++i )
		{
			if( m_pTarget1 != NULL )
			{
				if( m_pTarget1->GetState() != AT_DIE )
				{
					if( m_pTarget1->GetName() == L"ÆøÅº" )
					{
						if( m_pTarget1 == mitBomb->second[i] )
						{
							SPuzzleLine sLine;

							sLine.m_vecPuzzleLine.push_back( mitBomb->second[i] );

							for( int j = 0; j < (int)mitBomb->second.size(); ++j )
							{
								sLine.m_vecPuzzleLine.push_back( mitBomb->second[j] );
							}

							map< int, vector< CPuzzle* > >::iterator mitLine = m_mapPuzzle.begin();
							while( mitLine != m_mapPuzzle.end() )
							{
								sLine.m_vecPuzzleLine.push_back( mitLine->second[i] );
								++mitLine;
							}

							m_vecPuzzleLine.push_back( sLine );
							m_pTarget1 = NULL;
						}	
					}
				}
			}
		}
		++mitBomb;
	}

	map< int, vector< CPuzzle* > >::iterator mitItem = m_mapPuzzle.begin();
	while( mitItem != m_mapPuzzle.end() )
	{
		for( int i = 0; i < (int)mitItem->second.size(); ++i )
		{
			if( m_pTarget1 != NULL )
			{
				if( m_pTarget1->GetState() != AT_DIE )
				{
					if( m_pTarget1->GetName() == L"¾ÆÀÌÅÛ" )
					{
						if( m_pTarget1 == mitItem->second[i] )
						{
							SPuzzleLine sLine;

							sLine.m_vecPuzzleLine.push_back( mitItem->second[i] );

							int iArr = i;
							if( iArr + 1 < m_iHeight )
								sLine.m_vecPuzzleLine.push_back( mitItem->second[i+1] );

							if( iArr - 1 >= 0 )
								sLine.m_vecPuzzleLine.push_back( mitItem->second[i-1] );

							map< int, vector< CPuzzle* > >::iterator mitItem2 = m_mapPuzzle.begin();
							while( mitItem2 != m_mapPuzzle.end() )
							{
								if( mitItem->first + 1 == mitItem2->first )
									sLine.m_vecPuzzleLine.push_back( mitItem2->second[i] );

								if( mitItem->first - 1 == mitItem2->first )
									sLine.m_vecPuzzleLine.push_back( mitItem2->second[i] );

								++mitItem2;
							}

							m_vecPuzzleLine.push_back( sLine );
							m_pTarget1 = NULL;
						}
					}
				}
			}
		}

		++mitItem;
	}

	if( m_vecPuzzleLine.empty() == false )
	{
		for( int i = 0; i < (int)m_vecPuzzleLine.size(); ++i )
		{
			for( int j = 0; j < (int)m_vecPuzzleLine[i].m_vecPuzzleLine.size(); ++j )
			{
				if( m_vecPuzzleLine[i].m_vecPuzzleLine[j]->GetState() != AT_DIE )
				{
					if( m_vecPuzzleLine[i].m_vecPuzzleLine[j]->GetName() == L"ÆøÅº" )
						m_vecPuzzleLine[i].m_vecPuzzleLine[j]->AddRenderState( AT_DIE, L"Æø¹ß" );
					else
						m_vecPuzzleLine[i].m_vecPuzzleLine[j]->AddRenderState( AT_DIE, L"¹°¹æ¿ïÅÍÁü" );
				
					m_vecPuzzleLine[i].m_vecPuzzleLine[j]->SetState( AT_DIE );
				}

				for( int k = 0; k < (int)m_vecTargetMgr.size(); ++k )
				{
					if( m_vecTargetMgr[k].m_pTarget1 == m_vecPuzzleLine[i].m_vecPuzzleLine[j] ||
						m_vecTargetMgr[k].m_pTarget2 == m_vecPuzzleLine[i].m_vecPuzzleLine[j] )
						m_vecTargetMgr.erase( m_vecTargetMgr.begin() + k );
				}
			}

			if( m_vecPuzzleLine[i].m_vecPuzzleLine[0]->GetName() == L"¾ÆÀÌÅÛ" ||
				m_vecPuzzleLine[i].m_vecPuzzleLine[0]->GetName() == L"ÆøÅº" )
			{
				D_GAMESTAGEMGR->AddCombo();
				int iScore = 0;
				if( (int)m_vecPuzzleLine[i].m_vecPuzzleLine.size() >= 3 )
					iScore = 100;
				else if( (int)m_vecPuzzleLine[i].m_vecPuzzleLine.size() >= 4 )
					iScore = 150;
				else if( (int)m_vecPuzzleLine[i].m_vecPuzzleLine.size() >= 5 )
					iScore = 300;

				int iCombo = 0;
				if( D_GAMESTAGEMGR->GetCombo() >= 2 )
					iCombo = D_GAMESTAGEMGR->GetCombo() * 10;
				else if( D_GAMESTAGEMGR->GetCombo() >= 10 )
					iCombo = 100;

				D_GAMESTAGEMGR->AddScore( iScore + ( iCombo ) );
				D_GAMESTAGEMGR->AddBombGage( iScore + ( iCombo ) );
			}

			if( m_vecPuzzleLine[i].m_vecPuzzleLine[0]->GetState() == AT_DIE &&
				m_vecPuzzleLine[i].m_vecPuzzleLine[0]->GetRender()->IsEndAni() == true )
			{
				D_GAMESTAGEMGR->AddCombo();
				int iScore = 0;
				if( (int)m_vecPuzzleLine[i].m_vecPuzzleLine.size() >= 3 )
					iScore = 100;
				else if( (int)m_vecPuzzleLine[i].m_vecPuzzleLine.size() >= 4 )
					iScore = 150;
				else if( (int)m_vecPuzzleLine[i].m_vecPuzzleLine.size() >= 5 )
					iScore = 300;

				int iCombo = 0;
				if( D_GAMESTAGEMGR->GetCombo() >= 2 )
					iCombo = D_GAMESTAGEMGR->GetCombo() * 10;
				else if( D_GAMESTAGEMGR->GetCombo() >= 10 )
					iCombo = 100;

				D_GAMESTAGEMGR->AddScore( iScore + ( iCombo ) );
				D_GAMESTAGEMGR->AddBombGage( iScore + ( iCombo ) );

				if( D_GAMESTAGEMGR->GetBombGage() >= 5000 )
				{
					map< int, vector< CPuzzle* > >::iterator mitBoom = m_mapPuzzle.begin();
					while( mitBoom != m_mapPuzzle.end() )
					{
						for( int j = 0; j < (int)mitBoom->second.size(); ++j )
						{
							if( mitBoom->second[j] == m_vecPuzzleLine[i].m_vecPuzzleLine[1] )
							{
								CPuzzle* pBoom = (CPuzzle*)D_GAMEOBJMGR->CreateObj( EGAMEOBJ_PUZZLE, L"ÆøÅº", L"ÆøÅº", D3DXVECTOR2( m_vPuzzlePos.x + ( 64 * (float)( mitBoom->first ) ), m_vPuzzlePos.y - ( 64 * (float)( j + 1 ) ) ), 0, false, ERENDER_LEFTUP, 1, 0, false );
								pBoom->SetKey( mitBoom->first );
								pBoom->SetCount( j + 1 );

								mitBoom->second[j]->Destroy();
								mitBoom->second[j] = pBoom;

								D_GAMESTAGEMGR->SubBombGage( 5000 );
							}
						}
						++mitBoom;
					}
				}

				if( m_vecPuzzleLine[i].m_vecPuzzleLine[0]->GetName() != L"¾ÆÀÌÅÛ" )
				{
					if( m_vecPuzzleLine[i].m_vecPuzzleLine.size() >= 4 )
					{
						map< int, vector< CPuzzle* > >::iterator mitItem = m_mapPuzzle.begin();
						while( mitItem != m_mapPuzzle.end() )
						{
							for( int j = 0; j < (int)mitItem->second.size(); ++j )
							{
								if( mitItem->second[j] == m_vecPuzzleLine[i].m_vecPuzzleLine[0] )
								{
									CPuzzle* pItem = (CPuzzle*)D_GAMEOBJMGR->CreateObj( EGAMEOBJ_PUZZLE, L"¾ÆÀÌÅÛ", L"¾ÆÀÌÅÛ", D3DXVECTOR2( m_vPuzzlePos.x + ( 64 * (float)( mitItem->first ) ), m_vPuzzlePos.y - ( 64 * (float)( j + 1 ) ) ), 0, false, ERENDER_LEFTUP, 1, 0, false );
									pItem->SetKey( mitItem->first );
									pItem->SetCount( j + 1 );

									mitItem->second[j]->Destroy();
									mitItem->second[j] = pItem;
								}
							}

							++mitItem;
						}
					}
				}
			}

			m_vecPuzzleLine[i].m_vecPuzzleLine.clear();
		}
		m_vecPuzzleLine.clear();
		m_fHintTime = 0.0f;
	}

	map< int, vector< CPuzzle* > >::iterator mitDestroy = m_mapPuzzle.begin();
	while( mitDestroy != m_mapPuzzle.end() )
	{
		for( int i = 0; i < (int)mitDestroy->second.size(); ++i )
		{
			if( mitDestroy->second[i]->GetState() == AT_DIE &&
				mitDestroy->second[i]->GetRender()->IsEndAni() == true )
			{
				if( m_pTarget1 == mitDestroy->second[i] )
					m_pTarget1 = NULL;

				if( m_pTarget2 == mitDestroy->second[i] )
					m_pTarget2 = NULL;

				mitDestroy->second[i]->Destroy();
				m_fHintTime = 0.0f;
				m_fTimeOut = 0.0f;
			}
		}

		++mitDestroy;
	}

	map< int, vector< CPuzzle* > >::iterator mitCheck = m_mapPuzzle.begin();
	while( mitCheck != m_mapPuzzle.end() )
	{
		for( int i = 0; i < (int)mitCheck->second.size(); ++i )
		{
			mitCheck->second[i]->SetCount( i + 1 );
			mitCheck->second[i]->SetKey( mitCheck->first );

			for( int j = 0; j < (int)mitCheck->second.size(); ++j )
			{
				for( int k = 0; k < (int)mitCheck->second.size(); ++k )
				{
					if( mitCheck->second[k]->IsDestroy() == true )
					{
						mitCheck->second.erase( mitCheck->second.begin() + k );
					}
				}

				for( int k = 0; k < (int)mitCheck->second.size(); ++k )
				{
					if( (int)mitCheck->second.size() != m_iHeight )
					{
						if( (int)mitCheck->second.size() - 1 == k )
						{
							int iRand = rand()%m_iHeight + 1;
						
							wstringstream os;
							os << L"°úÀÏ" << iRand;

							CPuzzle* pObj = (CPuzzle*)D_GAMEOBJMGR->CreateObj( EGAMEOBJ_PUZZLE, os.str(), L"¹°¹æ¿ï", D3DXVECTOR2( m_vPuzzlePos.x + ( 64 * (float)( mitCheck->first ) ), m_vPuzzlePos.y - ( 64 * (float)( m_iHeight ) ) ), 0, false, ERENDER_LEFTUP, 1, 0, false );
							pObj->SetKey( mitCheck->first );
							pObj->SetCount( (int)mitCheck->second.size() + 1 );

							mitCheck->second.push_back( pObj );
						}
					}
				}
			}
		}

		for( int i = 0; i < (int)mitCheck->second.size(); ++i )
		{
			if( m_pTarget1 != NULL && m_pTarget2 != NULL )
			{
				if( m_pTarget1->IsDestroy() == true )
					m_pTarget1 = NULL;

				if( m_pTarget2->IsDestroy() == true )
					m_pTarget2 = NULL;

				mitCheck->second[i]->SetClick( false );
				continue;
			}

			if( m_pTarget1 == NULL )
			{
				if( mitCheck->second[i]->IsClick() == true )
				{
					m_pTarget1 = mitCheck->second[i];
					m_pTarget1->SetClick( false );
					if( m_pTarget1->GetState() != AT_CLICK )
					{
						m_pTarget1->AddRenderState( AT_CLICK, L"¹°¹æ¿ïÅ¬¸¯" );
						m_pTarget1->SetState( AT_CLICK );
					}

					map< int, vector< CPuzzle* > >::iterator mitTarget = m_mapPuzzle.begin();
					while( mitTarget != m_mapPuzzle.end() )
					{
						for( int j = 0; j < (int)mitTarget->second.size(); ++j )
						{
							if( mitTarget->second[j]->GetState() == AT_HINT )
								mitTarget->second[j]->SetState( AT_NORMAL );
						}
						++mitTarget;
					}
				}
			}
			else
			{
				if( mitCheck->second[i]->IsClick() == true )
				{
					if( m_pTarget1 != mitCheck->second[i] )
					{
						if( abs( m_pTarget1->GetKey() - mitCheck->second[i]->GetKey() ) <= 1 &&
							abs( m_pTarget1->GetCount() - mitCheck->second[i]->GetCount() ) == 0 )
						{
							m_pTarget2 = mitCheck->second[i];
							m_pTarget2->SetClick( false );
						}
						else if( abs( m_pTarget1->GetKey() - mitCheck->second[i]->GetKey() ) == 0 &&
								 abs( m_pTarget1->GetCount() - mitCheck->second[i]->GetCount() ) <= 1 )
						{
							m_pTarget2 = mitCheck->second[i];
							m_pTarget2->SetClick( false );
						}
						else
						{
							mitCheck->second[i]->SetClick( false );
							m_pTarget1->SetClick( false );
						}
					}
					else
					{
						mitCheck->second[i]->SetClick( false );
						m_pTarget1->SetClick( false );
						m_pTarget1->SetState( AT_NORMAL );
						m_pTarget1 = NULL;
					}

					map< int, vector< CPuzzle* > >::iterator mitTarget2 = m_mapPuzzle.begin();
					while( mitTarget2 != m_mapPuzzle.end() )
					{
						for( int j = 0; j < (int)mitTarget2->second.size(); ++j )
						{
							if( mitTarget2->second[j]->GetState() == AT_HINT )
								mitTarget2->second[j]->SetState( AT_NORMAL );
						}
						++mitTarget2;
					}
				}
			}
		}

		++mitCheck;
	}

	map< int, vector< CPuzzle* > >::iterator mitChange = m_mapPuzzle.begin();
	while( mitChange != m_mapPuzzle.end() )
	{
		for( int i = 0; i < (int)mitChange->second.size(); ++i )
		{
			map< int, vector< CPuzzle* > >::iterator mitChange2 = m_mapPuzzle.begin();
			while( mitChange2 != m_mapPuzzle.end() )
			{
				for( int j = 0; j < (int)mitChange2->second.size(); ++j )
				{
					if( m_pTarget1 != NULL && m_pTarget2 != NULL )
					{
						if( mitChange->second[i] == m_pTarget1 &&
							mitChange2->second[j] == m_pTarget2 )
						{
							mitChange->second[i] = mitChange2->second[j];
							mitChange2->second[j] = m_pTarget1;
					
							mitChange->second[i]->SetKey( mitChange->first );
							mitChange->second[i]->SetCount( i + 1 );
							mitChange2->second[j]->SetKey( mitChange2->first );
							mitChange2->second[j]->SetCount( j + 1 );
						
							STargetMgr sTargetMgr;
							sTargetMgr.m_pTarget1 = m_pTarget1;
							sTargetMgr.m_pTarget2 = m_pTarget2;

							m_vecTargetMgr.push_back( sTargetMgr );

							m_pTarget1->SetState( AT_NORMAL );

							m_pTarget1 = NULL;
							m_pTarget2 = NULL;
						}
					}

					if( m_vecTargetMgr.empty() == false )
					{
						for( int k = 0; k < (int)m_vecTargetMgr.size(); ++k )
						{
							if( mitChange->second[i] == m_vecTargetMgr[k].m_pTarget1 &&
								mitChange2->second[j] == m_vecTargetMgr[k].m_pTarget2 )
							{
								if( m_vecTargetMgr[k].m_pTarget1->GetPos()->x == m_vPuzzlePos.x + ( 64 * m_vecTargetMgr[k].m_pTarget1->GetKey() ) &&
									m_vecTargetMgr[k].m_pTarget1->GetPos()->y == m_vPuzzlePos.y - ( 64 * m_vecTargetMgr[k].m_pTarget1->GetCount() ) &&
									m_vecTargetMgr[k].m_pTarget2->GetPos()->x == m_vPuzzlePos.x + ( 64 * m_vecTargetMgr[k].m_pTarget2->GetKey() ) &&
									m_vecTargetMgr[k].m_pTarget2->GetPos()->y == m_vPuzzlePos.y - ( 64 * m_vecTargetMgr[k].m_pTarget2->GetCount() ) )
								{
									if( m_vecTargetMgr[k].m_pTarget1->IsDestroy() == false &&
										m_vecTargetMgr[k].m_pTarget2->IsDestroy() == false )
									{
										mitChange->second[i] = mitChange2->second[j];
										mitChange2->second[j] = m_vecTargetMgr[k].m_pTarget1;
					
										mitChange->second[i]->SetKey( mitChange->first );
										mitChange->second[i]->SetCount( i + 1 );
										mitChange2->second[j]->SetKey( mitChange2->first );
										mitChange2->second[j]->SetCount( j + 1 );

										D_GAMESTAGEMGR->ResetCombo();
										m_vecTargetMgr.erase( m_vecTargetMgr.begin() + k );
									}
								}
							}
						}
					}
				}

				++mitChange2;
			}
		}

		++mitChange;
	}
}