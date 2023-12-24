#include "ScenePlay.h"



ScenePlay::ScenePlay() {

	camera_ = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// ステージを管理するクラスの生成
	stage_ = std::shared_ptr<Stage>(new Stage("test", "csv/mapData.csv"));
	


}


ScenePlay::~ScenePlay() {

}


void ScenePlay::update(float delta_time) {

	DrawGridGround(camera_, 50, 20);

	camera_->update();

	// ステージの更新
	stage_->update(delta_time);
}

void ScenePlay::draw() {

	// ステージの描画
	stage_->draw(camera_);

}

