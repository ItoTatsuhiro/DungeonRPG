#include "ScenePlay.h"

#include "../manager/TurnManager.h"

ScenePlay::ScenePlay() {

	// ダンジョンのサブシーンを生成
	dungeonSubScene_ = std::shared_ptr<DungeonSubScene>(new DungeonSubScene());

	// 初期のシーンをダンジョンシーンに設定
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


