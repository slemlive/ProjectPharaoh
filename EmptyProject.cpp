//--------------------------------------------------------------------------------------
// File: EmptyProject.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "DXUT.h"
#include "Home.h"
#include "resource.h"

//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
    // Typically want to skip back buffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// Before a device is created, modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
	D_GAMEOBJPOOL->LoadSprite( L"과일1", L"Texture/과일/딸기 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"과일1애니", L"Texture/과일애니/딸기/딸기 (", L").png", 3, 0.2f, false );
	D_GAMEOBJPOOL->LoadSprite( L"과일2", L"Texture/과일/레몬 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"과일2애니", L"Texture/과일애니/레몬/레몬 (", L").png", 3, 0.2f, false );
	D_GAMEOBJPOOL->LoadSprite( L"과일3", L"Texture/과일/바나나 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"과일3애니", L"Texture/과일애니/바나나/바나나 (", L").png", 3, 0.2f, false );
	D_GAMEOBJPOOL->LoadSprite( L"과일4", L"Texture/과일/사과 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"과일4애니", L"Texture/과일애니/사과/사과 (", L").png", 3, 0.2f, false );
	D_GAMEOBJPOOL->LoadSprite( L"과일5", L"Texture/과일/수박 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"과일5애니", L"Texture/과일애니/수박/수박 (", L").png", 3, 0.2f, false );
	D_GAMEOBJPOOL->LoadSprite( L"과일6", L"Texture/과일/참외 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"과일6애니", L"Texture/과일애니/참외/참외 (", L").png", 3, 0.2f, false );
	D_GAMEOBJPOOL->LoadSprite( L"과일7", L"Texture/과일/파인애플 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"과일7애니", L"Texture/과일애니/파인애플/파인애플 (", L").png", 3, 0.2f, false );
	D_GAMEOBJPOOL->LoadSprite( L"과일8", L"Texture/과일/포도 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"과일8애니", L"Texture/과일애니/포도/포도 (", L").png", 3, 0.2f, false );
	D_GAMEOBJPOOL->LoadSprite( L"물방울", L"Texture/물방울/물방울 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"물방울클릭", L"Texture/물방울/클릭물방울 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"물방울터짐", L"Texture/물방울터짐/물방울 (", L").png", 4, 0.1f, false );
	D_GAMEOBJPOOL->LoadSprite( L"물방울힌트", L"Texture/물방울힌트/힌트 (", L").png", 2, 0.3f, true );
	D_GAMEOBJPOOL->LoadSprite( L"폭탄", L"Texture/폭탄/폭탄 (", L").png", 4, 0.2f, true );
	D_GAMEOBJPOOL->LoadSprite( L"아이템", L"Texture/물방울아이템/아이템 (", L").png", 7, 0.1f, true );
	D_GAMEOBJPOOL->LoadSprite( L"폭발", L"Texture/폭발/폭발 (", L").png", 8, 0.05f, false );
	D_GAMEOBJPOOL->LoadSprite( L"배경", L"Texture/Stage/배경 (", L").jpg", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"1스테이지", L"Texture/Stage/1스테이지 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"2스테이지", L"Texture/Stage/2스테이지 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"3스테이지", L"Texture/Stage/3스테이지 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"피버", L"Texture/피버모드/피버모드 (", L").jpg", 4, 0.1f, true );
	D_GAMEOBJPOOL->LoadSprite( L"타이머배경", L"Texture/UI/게이지/타이머배경 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"타이머게이지", L"Texture/UI/게이지/타이머게이지 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"폭탄배경", L"Texture/UI/게이지/폭탄배경 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"폭탄게이지", L"Texture/UI/게이지/폭탄게이지 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"점수판", L"Texture/UI/게이지/점수판 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"폭탄아이콘", L"Texture/UI/게이지/폭탄아이콘 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"피버타임배경", L"Texture/UI/게이지/피버타임배경 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"피버타임게이지", L"Texture/UI/게이지/피버타임게이지 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"피버타임시간", L"Texture/UI/게이지/피버타임시간 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"1콤보", L"Texture/콤보/1Combo (", L").png", 4, 0.05f, false );
	D_GAMEOBJPOOL->LoadSprite( L"2콤보", L"Texture/콤보/2Combo (", L").png", 4, 0.05f, false );
	D_GAMEOBJPOOL->LoadSprite( L"3콤보", L"Texture/콤보/3Combo (", L").png", 4, 0.05f, false );
	D_GAMEOBJPOOL->LoadSprite( L"4콤보", L"Texture/콤보/4Combo (", L").png", 4, 0.05f, false );
	D_GAMEOBJPOOL->LoadSprite( L"피버콤보", L"Texture/콤보/Fever (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"게임방법배경", L"Texture/UI/게임방법 (", L").jpg", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"게임소개배경", L"Texture/UI/게임소개 (", L").jpg", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"랭킹배경", L"Texture/UI/랭킹 (", L").jpg", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"뒤로가기", L"Texture/UI/뒤로가기 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"레디", L"Texture/UI/Ready (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"스타트", L"Texture/UI/Start (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"타임오버", L"Texture/타임오버 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"스코어", L"Texture/스코어 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"끝나셨습니다", L"Texture/끝나셨습니다 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"끝내기", L"Texture/끝내기 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"이어하기", L"Texture/이어하기 (", L").png", 1, 1.0f, true );
	D_GAMEOBJPOOL->LoadSprite( L"인트로", L"Texture/인트로/인트로 (", L").jpg", 13, 0.1f, false );
	D_GAMEOBJPOOL->LoadSprite( L"엔딩", L"Texture/엔딩/엔딩 (", L").jpg", 15, 0.1f, false );

	D_SOUND;
	D_GAMESTAGEMGR->ChangeStage( ESTAGE_INTRO );
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{
	D_SPRITE->OnResetDevice();
	D_CAMERA->InitSize( pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
	D_GAMESTAGEMGR->OnFrameMove( fElapsedTime );
	D_PUZZLEMGR->OnFrameMove( fElapsedTime );
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    // Clear the render target and the zbuffer 
    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
		D_GAMESTAGEMGR->OnFrameRender();
		D_FONT->OnFrameRender();
        V( pd3dDevice->EndScene() );
    }
}


//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
	switch( uMsg )
	{
	case WM_LBUTTONDOWN:
		D_GAMESTAGEMGR->SetClickOn( true );
		return 0;
	}

    return 0;
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9ResetDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
	D_SPRITE->OnLostDevice();
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
	D_TEXTURE->~CTexture();
	D_FONT->~CGameFontMgr();
	D_SPRITE->~CSprite();
	D_CAMERA->~CCamera();
	D_GAMEOBJMGR->~CGameObjMgr();
	D_PUZZLEMGR->~CPuzzleMgr();
}


//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
//--------------------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // Set the callback functions
    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackFrameMove( OnFrameMove );

    // TODO: Perform any application-level initialization here

    // Initialize DXUT and create the desired Win32 window and Direct3D device for the application
    DXUTInit( true, true ); // Parse the command line and show msgboxes
    DXUTSetHotkeyHandling( true, true, true );  // handle the default hotkeys
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
    DXUTCreateWindow( L"EmptyProject" );
    DXUTCreateDevice( true, 1280, 720 );

    // Start the render loop
    DXUTMainLoop();

    // TODO: Perform any application-level cleanup here

    return DXUTGetExitCode();
}


