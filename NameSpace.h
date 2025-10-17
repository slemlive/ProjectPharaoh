
#pragma once

#pragma comment(lib, "dsound")

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <thread>
#include <omp.h>
#include <vector>
#include <list>
#include <map>
#include <deque>
#include <queue>

#include <dsound.h>
#include <SDKsound.h>
#include <SDKwavefile.h>

#define D_TEXTURE CTexture::GetInstance()
#define D_SPRITE CSprite::GetInstance()
#define D_MESH CMesh::GetInstance()
#define D_GAMEOBJPOOL CGameObjPool::GetInstance()
#define D_CAMERA CCamera::GetInstance()
#define D_PROCESSMGR CProcessMgr::GetInstance()
#define D_GAMESTAGEMGR CGameStageMgr::GetInstance()
#define D_SOUNDMGR CSoundMgr::GetInstance()
#define D_PLAYERCTR CPlayer::GetInstance()
#define D_UNITMGR CUnitMgr::GetInstance()
#define D_RANKING CRankMgr::GetInstance()
#define D_SCORE CScore::GetInstance()
#define D_PATHFIND CPathfind::GetInstance()

using namespace std;

#include "frstream.h"
#include "Ase.h"

#include "Singleton.h"

#include "Texture.h"
#include "Sprite.h"
#include "Mesh.h"

#include "GameObjPool.h"

#include "GameObj.h"
#include "Effect.h"
#include "ParticleSystem.h"
#include "Item.h"
#include "Portal.h"
#include "Unit.h"
#include "Snake.h"
#include "Cat.h"
#include "Mummy.h"
#include "Scorpion.h"
#include "SC.h"
#include "Boss.h"
#include "Player.h"
#include "Torch.h"
#include "Arrow.h"

#include "GameUI.h"
#include "TextureUI.h"
#include "FontUI.h"

#include "Stage.h"
#include "New.h"
#include "Loading.h"
#include "Intro.h"
#include "Main.h"
#include "Introduce.h"
#include "Explayin.h"
#include "Ranking.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Ending.h"
#include "ScoreStage.h"

#include "GameStageMgr.h"
#include "GameObjContainer.h"
#include "GameUIContainer.h"
#include "ProcessMgr.h"
#include "Pathfind.h"

#include "UnitMgr.h"
#include "Score.h"
#include "RankMgr.h"

#include "SoundMgr.h"

#include "Camera.h"
#include "Util.h"