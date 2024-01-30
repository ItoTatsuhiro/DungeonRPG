#include "ScenePlay.h"



ScenePlay::ScenePlay() {

	// camera_ = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	FPCamera_ = std::make_shared< TransformCamera >(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// ステージを管理するクラスの生成
	// stage_ = std::shared_ptr<Stage>(new Stage("test", "csv/mapData.csv"));
	stage_ = Stage::GetInstance("test", "csv/mapData.csv", gridSize_);

	// プレイヤーの作成
	player_ = std::shared_ptr<Player>( new Player(gridSize_, { 0, 0 }) );
}


ScenePlay::~ScenePlay() {

}


void ScenePlay::update(float delta_time) {

	DrawGridGround(FPCamera_, 50, 20);

	FPCamera_->pos_ = player_->getTransform().getPos_();

	// camera_->target_ = player_->getTransform().getPos_();

	FPCamera_->update( player_->getTransform().getRot3D_() );

	// ステージの更新
	stage_->update(delta_time);

	player_->update(delta_time);
}

void ScenePlay::draw() {

	// ステージの描画
	stage_->draw(FPCamera_);

}

