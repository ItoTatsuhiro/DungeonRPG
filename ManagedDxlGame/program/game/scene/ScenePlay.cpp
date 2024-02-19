#include "ScenePlay.h"

#include "../manager/TurnManager.h"

#include "SubScene/DungeonSubScene.h"
#include "SubScene/BattleSubScene.h"


ScenePlay::ScenePlay() {

	// �_���W�����̃T�u�V�[���𐶐�
	dungeonSubScene_ = std::shared_ptr<DungeonSubScene>(new DungeonSubScene());

	// �����̃V�[�����_���W�����V�[���ɐݒ�
	// nowSubScene_ = dungeonSubScene_;


	battleSubScene_ = std::shared_ptr<BattleSubScene>(new BattleSubScene());

	// �f�o�b�O�p
	// �o�g���V�[�������s
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


// �_���W�����̃T�u�V�[���ɐ؂�ւ�
void ScenePlay::ChangeSubSceneToDungeon() {

	nowSubScene_ = dungeonSubScene_;

}
// �o�g���̃T�u�V�[���ɐ؂�ւ�
void ScenePlay::ChangeSubSceneToBattle() {

	nowSubScene_ = battleSubScene_;
}
