#include "SubSceneManager.h"
#include "../scene/SubScene/BattleSubScene.h"
#include "../scene/SubScene/DungeonSubScene.h"
#include "../character/Dungeon/Enemy.h"

SubSceneManager::SubSceneManager() {


	SetUp();

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

	// nowSubScene_->update(delta_time);

	seq_.update(delta_time);


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_P)) {
		debugMode_ = true;
	}

	if (debugMode_) {
		screenEffect_->drawGuiController( {0, 0} );
	}
}

// �`��p�̊֐�
// ���݂̃T�u�V�[���̕`����s���֐�
void SubSceneManager::draw() {

	if (!nowSubScene_) {
		return;
	}


	screenEffect_->renderBegin();

	nowSubScene_->draw();

	screenEffect_->renderEnd();

}


void SubSceneManager::ChangeSubScene(ScenePlaySubScene nextSubScene, std::shared_ptr<Enemy> battlingEnemy) {

	nextSubScene_ = nextSubScene;

	// �����Ƃ��Ēl������ꂽ���͂��̒l�A������Ȃ������Ƃ��͕ϐ���battlingEnemy������
	battlingEnemy_ = (battlingEnemy != nullptr) ? battlingEnemy : battlingEnemy_;

	seq_.change(&SubSceneManager::seqSubSceneChange);


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

// �����ݒ���s���֐�
void SubSceneManager::SetUp() {

	// �X�N���[���G�t�F�N�g�̃��Z�b�g
	if (screenEffect_) {
		screenEffect_.reset();
	}
	// �X�N���[���G�t�F�N�g�N���X�̐���
	screenEffect_ = std::shared_ptr<dxe::ScreenEffect>(new dxe::ScreenEffect(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT));
	// �ݒ肵���X�e�[�^�X�̓ǂݍ���
	screenEffect_->loadStatus("screen_effect.bin");

	// �T�u�V�[���̃��Z�b�g
	if (dungeonSubScene_) {
		dungeonSubScene_.reset();

	}
	if (battleSubScene_) {
		battleSubScene_.reset();

	}

	// �_���W�����T�u�V�[���̐���
	dungeonSubScene_ = std::shared_ptr<DungeonSubScene>(new DungeonSubScene());
	// ���݂̃T�u�V�[����ݒ�
	nowSubScene_ = dungeonSubScene_;
	// �V�[���؂�ւ����̉摜��ǂݍ���
	transGpc_ = ito::ResourceManager::GetInstance()->loadGraph("black.png");

}


// �C���X�^���X���폜����֐�
void SubSceneManager::Destroy() {

	dungeonSubScene_.reset();
	battleSubScene_.reset();

	SubSceneManager::GetInstance().reset();
}


// �T�u�V�[���̍X�V���s���V�[�P���X
bool SubSceneManager::seqSubSceneUpdate(const float delta_time) {

	nowSubScene_->update(delta_time);

	return true;
}

// �T�u�V�[����؂�ւ���ۂ̃V�[�P���X
// ��{�I�ɉ�ʂ̈Ó]���s��
bool SubSceneManager::seqSubSceneChange(const float delta_time) {


	float blurAlpha = (seq_.getProgressTime() / transTime_);
	screenEffect_->setBlurAlpha(blurAlpha);


	int levelMin = blurAlpha * 255.0f;
	screenEffect_->setLevelMin(levelMin);



	if (blurAlpha >= 1.0f) {

		// �V�[����؂�ւ���
		switch (nextSubScene_) {
		case ScenePlaySubScene::DUNGEON:
			nowSubScene_ = dungeonSubScene_;

			dungeonSubScene_->DeleteEnemy(battlingEnemy_);
			
			break;

		case ScenePlaySubScene::BATTLE:

			ChangeBattleScene(battlingEnemy_);
			
			break;
		}
		seq_.change(&SubSceneManager::seqSubSceneStart);
	}


	return true;
}


// �T�u�V�[�����J�n����ۂ̃V�[�P���X
// ��{�I�ɉ�ʂ𖾂邭���鏈�����s��
bool SubSceneManager::seqSubSceneStart(const float delta_time) {

	float blurAlpha = (1.0f - seq_.getProgressTime() / transTime_) >= 0 ? (1.0f - seq_.getProgressTime() / transTime_) : 0;
	screenEffect_->setBlurAlpha(blurAlpha);


	int levelMin = blurAlpha * 255;
	screenEffect_->setLevelMin(levelMin);



	if (blurAlpha == 0.0f) {

		// �V�[�P���X��؂�ւ���
		seq_.change(&SubSceneManager::seqSubSceneUpdate);

	}


	return true;

}