#include <iostream>
#include <memory>
#include "ito_GameManager.h"
#include "ito_ResourceManager.h"
#include "../Base/ito_SceneBase.h"
#include "../../game/manager/ObjectManager.h"

namespace ito {

	// �R���X�g���N�^
	ito::GameManager::GameManager(SceneBase* startScene) : nowScene_(startScene) {

		// �}�l�[�W���[�N���X�̃C���X�^���X��
		ito::ResourceManager::GetInstance();

	}

	ito::GameManager::~GameManager() {

		// �}�l�[�W���[�N���X�̃C���X�^���X���폜
		ito::ResourceManager::GetInstance()->Destroy();

	}

	// �Q�[���}�l�[�W���[���C���X�^���X������ۂɎg�p����֐�
	// �����FstartScene...�Q�[�����J�n����ۂɏ��߂Ɏ��s����V�[��
	GameManager* GameManager::GetInstance_(SceneBase* startScene) {

		static GameManager* instance(nullptr);
		if (!instance) {
			instance = new GameManager(startScene);
		}
		return instance;

	}

	void GameManager::update(float delta_time) {
		if (nowScene_) nowScene_->update(delta_time);
		if (nowScene_) nowScene_->draw();
	}

	void GameManager::changeScene(SceneBase* nextScene) {
		nextScene_ = nextScene;
		nowScene_ = nullptr;
		nowScene_ = nextScene_;
	}

	//void GameManager::Load_CsvAddress() {
	//
	//	// ����csv�A�h���X���i�[����csv�����[�h
	//	//csvAddress = tnl::LoadCsv<std::string>("csv/CsvAddress.csv");
	//
	//
	//}

}