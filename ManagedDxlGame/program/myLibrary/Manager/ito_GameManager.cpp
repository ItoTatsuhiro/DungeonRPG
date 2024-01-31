#include <iostream>
#include <memory>
#include "ito_GameManager.h"
#include "ito_ResourceManager.h"
#include "../Base/ito_SceneBase.h"
#include "../../game/manager/ObjectManager.h"

namespace ito {

	// コンストラクタ
	ito::GameManager::GameManager(SceneBase* startScene) : nowScene_(startScene) {

		// マネージャークラスのインスタンス化
		ito::ResourceManager::GetInstance();

	}

	ito::GameManager::~GameManager() {

		// マネージャークラスのインスタンスを削除
		ito::ResourceManager::GetInstance()->Destroy();

	}

	// ゲームマネージャーをインスタンス化する際に使用する関数
	// 引数：startScene...ゲームを開始する際に初めに実行するシーン
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
	//	// 他のcsvアドレスを格納するcsvをロード
	//	//csvAddress = tnl::LoadCsv<std::string>("csv/CsvAddress.csv");
	//
	//
	//}

}