#include "ScenePlay.h"

#include "../manager/TurnManager.h"

#include "../base/SubSceneBase.h"
#include "SubScene/DungeonSubScene.h"
#include "SubScene/BattleSubScene.h"


ScenePlay::ScenePlay() {


	SubSceneManager::GetInstance();

}


ScenePlay::~ScenePlay() {

	SubSceneManager::GetInstance()->Destroy();
	TurnManager::GetInstance()->Destroy();

}

// 更新用の関数
void ScenePlay::update(float delta_time) {

	SubSceneManager::GetInstance()->update(delta_time);

}

// 描画用の関数
void ScenePlay::draw() {

	SubSceneManager::GetInstance()->draw();

}

