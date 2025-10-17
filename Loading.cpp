
#include "DXUT.h"
#include "NameSpace.h"

void LoadingThread(map< string, SAseData* >* mapAseData, bool* bClear)
{
	D_GAMEOBJPOOL->CreateMeshData("Data/MeshData.txt", *mapAseData);
	*bClear = true;
}

CLoading::CLoading():
m_bClear( false ),
m_thLoadingThread(NULL)
{

}

CLoading::~CLoading()
{
	HANDLE hThread = m_thLoadingThread->native_handle();
	TerminateThread(hThread, NULL);
	CloseHandle(hThread);
}

void CLoading::StartStage()
{
	D_RANKING->Load("Data/Ranking.txt");
	D_GAMEOBJPOOL->LoadSprite("Intro", "Image/Intro/Intro (", ").jpg", 580, 0.01f, false);
	D_GAMEOBJPOOL->LoadSprite("Ending", "Image/Ending/Ending (", ").jpg", 61, 0.03f, false);
	D_GAMEOBJPOOL->CreateSpriteData("Data/SpriteData.txt");
	D_PROCESSMGR->CreateTextureUI("Loading", D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);

	m_thLoadingThread = new thread(LoadingThread, &m_mapAseData, &m_bClear);
}

void CLoading::OnFrameMove(float fElapsedTime)
{
	if (m_bClear)
	{
		D_GAMEOBJPOOL->LoadMeshToAseData(m_mapAseData);
		D_GAMESTAGEMGR->ChangeStage(ES_INTRO);
	}

}

void CLoading::OnFrameRender()
{

}

void CLoading::EndStage()
{
	D_PROCESSMGR->ClearObj();
	D_PROCESSMGR->ClearUI();
}