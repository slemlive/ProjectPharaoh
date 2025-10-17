#include "DXUT.h"
#include "Home.h"


CRender::CRender( CGameObj* pGameObj ):
m_pGameObj( pGameObj ),
	m_iCurIndex( 0 ),
	m_bEndAni( false ),
	m_fTrackTime( 0.0f )
{
	D3DXMatrixIdentity( &m_matWorld );
}


CRender::~CRender(void)
{
}

void CRender::Load( const SSpriteData* pData )
{
	m_vecTexture = pData->m_vecTexture;
	m_fTrackSpeed = pData->m_fTrackSpeed;
	m_bLoop = pData->m_bLoop;
}

void CRender::MakeRot( D3DXMATRIX& matRot )
{
	if( m_pGameObj == NULL )
		return ;

	D3DXMatrixIdentity( &matRot );
	D3DXMatrixRotationZ( &matRot, D3DXToRadian( m_pGameObj->GetAngle() ));
}

void CRender::MakeTrans( D3DXMATRIX& matTrans )
{
	if( m_pGameObj == NULL )
		return ;

	D3DXMatrixIdentity( &matTrans );
	matTrans._41 = m_pGameObj->GetPos()->x;
	matTrans._42 = m_pGameObj->GetPos()->y;
}

void CRender::MakeScale( D3DXMATRIX& matScale )
{
	if( m_pGameObj == NULL )
		return ;

	D3DXMatrixIdentity( &matScale );
	matScale._11 = m_pGameObj->GetScl()->x;
	matScale._22 = m_pGameObj->GetScl()->y;
}

void CRender::MakeLocal( D3DXMATRIX& matLocal )
{
	if( m_pGameObj == NULL )
		return ;

	D3DXMatrixIdentity( &matLocal );
	const STextureInfo* pTextureInfo = D_TEXTURE->GetTextureInfo( m_vecTexture[m_iCurIndex] );
	if( pTextureInfo == NULL )
		return ;

	m_pGameObj->SetImgSize( D3DXVECTOR2( (float)pTextureInfo->m_TextureInfo.Width, (float)pTextureInfo->m_TextureInfo.Height ) ); 

	RECT rcRect;
	SetRect( &rcRect, (LONG)m_pGameObj->GetPos()->x
		, (LONG)m_pGameObj->GetPos()->y
		, (LONG)( m_pGameObj->GetPos()->x + pTextureInfo->m_TextureInfo.Width )
		, (LONG)( m_pGameObj->GetPos()->y + pTextureInfo->m_TextureInfo.Height ) );

	m_pGameObj->SetRect( rcRect );

	switch( m_pGameObj->GetRenderType() )
	{
	case ERENDER_LEFTUP :
		{
			break;
		}
	case ERENDER_CENTER :
		{
			matLocal._41 -= pTextureInfo->m_TextureInfo.Width * 0.5f;
			matLocal._42 -= pTextureInfo->m_TextureInfo.Height * 0.5f;
			break;
		}

	case ERENDER_UNDER:
		{
			matLocal._41 -= pTextureInfo->m_TextureInfo.Width * 0.5f;
			matLocal._42 -= pTextureInfo->m_TextureInfo.Height * 1.0f;
			break;
		}

	}
}

void CRender::SetCurIndex( int iIndex )
{
	m_iCurIndex = iIndex;
	m_fTrackTime = 0.0f;
	m_bEndAni = false;
}

void CRender::UpdateWorld()
{
	D3DXMATRIX matRot;
	MakeRot( matRot );

	D3DXMATRIX matTrans;
	MakeTrans( matTrans );

	D3DXMATRIX matScale;
	MakeScale( matScale );

	D3DXMATRIX matLocal;
	MakeLocal( matLocal );

	m_matWorld = matLocal * matRot * matScale * matTrans;
	m_matWorld._43 = 0.0f;
}

bool CRender::OnFrameMove( float fElapsedTime )
{
	UpdateWorld();

	m_fTrackTime += fElapsedTime;

	bool bChange = m_fTrackTime > m_fTrackSpeed;

	if( bChange )
	{
		int iIndex = m_iCurIndex + 1;

		if( iIndex >= (int)m_vecTexture.size() )
		{
			if( m_bLoop )
				SetCurIndex( 0 );
			else
			{
				m_bEndAni = true;
				return false;
			}
		}
		else
			SetCurIndex( iIndex );
	}

	return true;
}

void CRender::OnFrameRender()
{
	if( m_iCurIndex < 0 || m_iCurIndex >= (int)m_vecTexture.size() )	// 이미지 장수와 텍스쳐 배열크기 비교
		return ;

	D3DXMATRIX matView;
	D3DXMatrixIdentity( &matView );


	if( m_pGameObj->IsCamera() )
		D_CAMERA->GetTransform( &matView );

	D3DXMATRIX matWorld = m_matWorld * matView;
	matWorld._43 = 0.0f;

	D_SPRITE->SetTransform( &matWorld );
	D_SPRITE->OnDraw( D_TEXTURE->GetTexture( m_vecTexture[m_iCurIndex] ), NULL, 0.0f, 0.0f, m_pGameObj->GetColor() );
}