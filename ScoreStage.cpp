
#include "DXUT.h"
#include "NameSpace.h"

CScoreStage::CScoreStage():
pFont( NULL )
{

}

CScoreStage::~CScoreStage()
{

}

void CScoreStage::StartStage()
{
	D_GAMESTAGEMGR->SetKey(true);
	D_GAMESTAGEMGR->ClearString();

	D_PROCESSMGR->CreateTextureUI("Write", D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0.0f, 0);
	pFont = D_PROCESSMGR->CreateFontUI("이름을 입력하시오.", D3DXVECTOR2(1920.0f / 2.0f, 500.0f), 60, DT_CENTER, 1);
	
	stringstream os;
	os << "점수: " << D_SCORE->GetScore();
	D_PROCESSMGR->CreateFontUI(os.str(), D3DXVECTOR2(1920.0f / 2.0f, 300.0f), 70, DT_CENTER, 1);
}

void CScoreStage::OnFrameMove(float fElapsedTime)
{
	if (DXUTWasKeyPressed(VK_RETURN))
	{
		D_RANKING->AddScoreData(D_GAMESTAGEMGR->GetString(), D_SCORE->GetScore());
		return D_GAMESTAGEMGR->ChangeStage(ES_RANKING);
	}

	if (pFont != NULL)
	{
		string sString = D_GAMESTAGEMGR->GetString();
		if (!sString.empty())
			pFont->SetString(sString);
		else
			pFont->SetString("이름을 입력하시오. (띄어쓰기 안됨 특수문자 가능)");
	}
}

void CScoreStage::OnFrameRender()
{

}

void CScoreStage::EndStage()
{
	D_GAMESTAGEMGR->ClearString();
	D_GAMESTAGEMGR->SetKey(false);

	D_PROCESSMGR->ClearObj();
	D_PROCESSMGR->ClearUI();

	D_RANKING->UpdateRank();
	D_RANKING->Write();
}