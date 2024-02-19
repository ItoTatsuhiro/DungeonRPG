#include "ScenePlay.h"

#include "../manager/TurnManager.h"

#include "SubScene/DungeonSubScene.h"
#include "SubScene/BattleSubScene.h"


ScenePlay::ScenePlay() {

	// ダンジョンのサブシーンを生成
	dungeonSubScene_ = std::shared_ptr<DungeonSubScene>(new DungeonSubScene());

	// 初期のシーンをダンジョンシーンに設定
	// nowSubScene_ = dungeonSubScene_;


	battleSubScene_ = std::shared_ptr<BattleSubScene>(new BattleSubScene());

	// デバッグ用
	// バトルシーンを実行
	// nowSubScene_ = battleSubScene_;

	nowSubScene_ = dungeonSubScene_;
}


ScenePlay::~ScenePlay() {

}


void ScenePlay::update(float delta_time) {

	nowSubScene_->update(delta_time);

}

void ScenePlay::draw() {

	nowSubScene_->draw();

}

void ScenePlay::ChangeSubScene(std::shared_ptr<SubSceneBase> nextSubScene) {

	nowSubScene_ = nextSubScene;

	return;
}


// ダンジョンのサブシーンに切り替え
void ScenePlay::ChangeSubSceneToDungeon() {

	nowSubScene_ = dungeonSubScene_;

}
// バトルのサブシーンに切り替え
void ScenePlay::ChangeSubSceneToBattle() {

	nowSubScene_ = battleSubScene_;
}
