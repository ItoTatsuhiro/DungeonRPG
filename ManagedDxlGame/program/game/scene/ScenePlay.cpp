#include "ScenePlay.h"

#include "../manager/SubSceneManager.h"
#include "../base/SubSceneBase.h"
#include "SubScene/DungeonSubScene.h"
#include "SubScene/BattleSubScene.h"


ScenePlay::ScenePlay() {

	//// サブシーンマネージャーの作成
	//subSceneManager_ = std::shared_ptr<SubSceneManager>(new SubSceneManager());

	SubSceneManager::GetInstance()->SetUp();


}


ScenePlay::~ScenePlay() {


	SubSceneManager::GetInstance()->Destroy();

}

// 更新用の関数
void ScenePlay::update(float delta_time) {


	SubSceneManager::GetInstance()->update(delta_time);

}

// 描画用の関数
void ScenePlay::draw() {


	SubSceneManager::GetInstance()->draw();
}

