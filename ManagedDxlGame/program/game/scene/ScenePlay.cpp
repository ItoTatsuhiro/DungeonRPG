#include "ScenePlay.h"

#include "../manager/TurnManager.h"

ScenePlay::ScenePlay() {

	// �_���W�����̃T�u�V�[���𐶐�
	dungeonSubScene_ = std::shared_ptr<DungeonSubScene>(new DungeonSubScene());

	// �����̃V�[�����_���W�����V�[���ɐݒ�
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


