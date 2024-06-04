#include <iostream>
#include <memory>
#include "ito_GameManager.h"
#include "ito_ResourceManager.h"
#include "../Base/ito_SceneBase.h"
#include "../../game/manager/ObjectManager.h"

namespace ito {

	// コンストラクタ
	ito::GameManager::GameManager(std::shared_ptr<SceneBase> startScene) : nowScene_(startScene) {

		// マネージャークラスのインスタンス化
		ito::ResourceManager::GetInstance();

	}

	ito::GameManager::~GameManager() {

		// マネージャークラスのインスタンスを削除
		ito::ResourceManager::GetInstance()->Destroy();

	}

	// ゲームマネージャーをインスタンス化する際に使用する関数
	// 引数：startScene...ゲームを開始する際に初めに実行するシーン
	GameManager* GameManager::GetInstance_(std::shared_ptr<SceneBase> startScene) {

		static GameManager* instance(nullptr);
		if (!instance) {
			instance = new GameManager(startScene);
		}
		return instance;

	}

	// 現在実行中のシーンを更新する関数
	void GameManager::update(float delta_time) {
		if (nowScene_) nowScene_->update(delta_time);
		if (nowScene_) nowScene_->draw();
	}

	// シーンを切り替える関数
	void GameManager::changeScene(std::shared_ptr<SceneBase> nextScene) {
		nextScene_ = nextScene;
		nowScene_.reset();
		nowScene_ = nextScene_;
	}

	// インスタンスを削除する関数
	void GameManager::Destroy() {
		delete GetInstance_();
	}

	//void GameManager::Load_CsvAddress() {
	//
	//	// 他のcsvアドレスを格納するcsvをロード
	//	//csvAddress = tnl::LoadCsv<std::string>("csv/CsvAddress.csv");
	//
	//
	//}

}