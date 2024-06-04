#include "SubSceneManager.h"
#include "../scene/SubScene/BattleSubScene.h"
#include "../scene/SubScene/DungeonSubScene.h"
#include "../character/Dungeon/Enemy.h"

SubSceneManager::SubSceneManager() {

	// �_���W�����T�u�V�[���̐���
	dungeonSubScene_ = std::shared_ptr<DungeonSubScene>(new DungeonSubScene());



	nowSubScene_ = dungeonSubScene_;

}

SubSceneManager::~SubSceneManager() {


}


std::shared_ptr<SubSceneManager> SubSceneManager::GetInstance() {

	// SubSceneManager�N���X�̃C���X�^���X
	static std::shared_ptr<SubSceneManager> instance = nullptr;

	// ���ɐ�������Ă��Ȃ��Ƃ��̂ݐV��������
	if (!instance) {
		instance = std::shared_ptr<SubSceneManager>(new SubSceneManager());
	}

	return instance;

}


// �X�V�p�̊֐�
// ���݂̃T�u�V�[���̍X�V���s��
void SubSceneManager::update(float delta_time) {

	if (!nowSubScene_) {
		return;
	}

	nowSubScene_->update(delta_time);

}

// �`��p�̊֐�
// ���݂̃T�u�V�[���̕`����s���֐�
void SubSceneManager::draw() {

	if (!nowSubScene_) {
		return;
	}

	nowSubScene_->draw();
}


void SubSceneManager::ChangeSubScene(ScenePlaySubScene nextSubScene, std::shared_ptr<Enemy> battlingEnemy) {

	switch (nextSubScene) {
	case ScenePlaySubScene::DUNGEON :
		nowSubScene_ = dungeonSubScene_;

		dungeonSubScene_->DeleteEnemy(battlingEnemy_);
		break;

	case ScenePlaySubScene::BATTLE :
		// nowSubScene_ = battleSubScene_;

		ChangeBattleScene(battlingEnemy);

		break;
	}

	return;
}

// �o�g���V�[���̍쐬,�J��
// �o�g���V�[���ɑJ�ڂ���ہA���̊֐����Ăяo��
void SubSceneManager::ChangeBattleScene(std::shared_ptr<Enemy> battlingEnemy) {


	// �G�L�����N�^�[���Z�b�g
	battlingEnemy_ = battlingEnemy;

	battleSubScene_ = std::shared_ptr<BattleSubScene>(new BattleSubScene());

	nowSubScene_ = battleSubScene_;

}


void SubSceneManager::Destroy() {

	dungeonSubScene_.reset();
	battleSubScene_.reset();

	SubSceneManager::GetInstance().reset();
}