#include "ScenePlay.h"



ScenePlay::ScenePlay() {

	// camera_ = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	FPCamera_ = std::make_shared< TransformCamera >(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// �X�e�[�W���Ǘ�����N���X�̐���
	// stage_ = std::shared_ptr<Stage>(new Stage("test", "csv/mapData.csv"));
	stage_ = Stage::GetInstance("test", "csv/mapData.csv", gridSize_);

	// �v���C���[�̍쐬
	player_ = std::shared_ptr<Player>( new Player(gridSize_, { 0, 0 }) );
}


ScenePlay::~ScenePlay() {

}


void ScenePlay::update(float delta_time) {

	DrawGridGround(FPCamera_, 50, 20);

	FPCamera_->pos_ = player_->getTransform().getPos_();

	// camera_->target_ = player_->getTransform().getPos_();

	FPCamera_->update( player_->getTransform().getRot3D_() );

	// �X�e�[�W�̍X�V
	stage_->update(delta_time);

	player_->update(delta_time);
}

void ScenePlay::draw() {

	// �X�e�[�W�̕`��
	stage_->draw(FPCamera_);

}

