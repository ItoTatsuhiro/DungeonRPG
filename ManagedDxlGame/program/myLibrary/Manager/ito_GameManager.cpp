#include <iostream>
#include <memory>
#include "ito_GameManager.h"
#include "ito_ResourceManager.h"
#include "../Base/ito_SceneBase.h"


namespace ito {

	ito::GameManager::GameManager(SceneBase* start_scene) : now_scene_(start_scene) {

		// マネージャークラスのインスタンス化
		ito::ResourceManager::GetInstance_();

	}

	ito::GameManager::~GameManager() {

		// マネージャークラスのインスタンスを削除
		ito::ResourceManager::GetInstance_()->Destroy();

	}


	GameManager* GameManager::GetInstance_(SceneBase* start_scene) {

		static GameManager* instance(nullptr);
		if (!instance) {
			instance = new GameManager(start_scene);
		}
		return instance;

	}

	void GameManager::update(float delta_time) {
		if (now_scene_) now_scene_->update(delta_time);
		if (now_scene_) now_scene_->draw();
	}

	void GameManager::changeScene(SceneBase* next_scene) {
		next_scene_ = next_scene;
		now_scene_ = nullptr;
		now_scene_ = next_scene_;
	}

	//void GameManager::Load_CsvAddress() {
	//
	//	// 他のcsvアドレスを格納するcsvをロード
	//	//csvAddress = tnl::LoadCsv<std::string>("csv/CsvAddress.csv");
	//
	//
	//}

}