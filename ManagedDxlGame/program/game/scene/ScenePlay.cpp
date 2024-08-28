#include "ScenePlay.h"

#include "../manager/SubSceneManager.h"
#include "../base/SubSceneBase.h"
#include "SubScene/DungeonSubScene.h"
#include "SubScene/BattleSubScene.h"


ScenePlay::ScenePlay() {

	//// �T�u�V�[���}�l�[�W���[�̍쐬
	//subSceneManager_ = std::shared_ptr<SubSceneManager>(new SubSceneManager());

	SubSceneManager::GetInstance()->SetUp();


}


ScenePlay::~ScenePlay() {


	SubSceneManager::GetInstance()->Destroy();

}

// �X�V�p�̊֐�
void ScenePlay::update(float delta_time) {


	SubSceneManager::GetInstance()->update(delta_time);

}

// �`��p�̊֐�
void ScenePlay::draw() {


	SubSceneManager::GetInstance()->draw();
}

