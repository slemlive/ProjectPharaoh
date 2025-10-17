
#pragma comment( lib, "dsound" )

#include < iostream >
#include < vector >
#include < sstream >
#include < string >
#include < map >
#include < list >
#include <time.h>

#include "DSound.h"
#include "SDKsound.h"
#include "SDKwavefile.h"

#define D_TEXTURE CTexture::GetTexture()
#define D_SPRITE CSprite::GetSprite()
#define D_CAMERA CCamera::GetCamera()
#define D_GAMEOBJPOOL CGameObjPool::GetGameObjPool()
#define D_GAMEOBJMGR CGameObjMgr::GetGameObjMgr()
#define D_GAMESTAGEMGR CGameStageMgr::GetStageMgr()
#define D_SOUND CSoundMgr::GetSoundMgr()
#define D_FONT CGameFontMgr::GetFontMgr()
#define D_PUZZLEMGR CPuzzleMgr::GetPuzzleMgr()

using namespace std;

#include "Texture.h"
#include "Sprite.h"
#include "GameObj.h"
#include "Puzzle.h"

#include "GameObjPool.h"
#include "Render.h"

#include "Camera.h"

#include "GameObjContainer.h"
#include "GameObjMgr.h"
#include "PuzzleMgr.h"

#include "Util.h"

#include "GameStage.h"
#include "Intro.h"
#include "MainMenu.h"
#include "Report.h"
#include "Way.h"
#include "Rank.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "ScorePage.h"
#include "Ending.h"

#include "SoundMgr.h"

#include "GameStageMgr.h"

#include "GameFontMgr.h"
