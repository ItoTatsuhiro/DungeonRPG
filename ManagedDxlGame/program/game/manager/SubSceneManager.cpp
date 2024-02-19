#include "SubSceneManager.h"

SubSceneManager::SubSceneManager() {

}

SubSceneManager::~SubSceneManager() {

}


std::shared_ptr<SubSceneManager> SubSceneManager::GetInstance() {

	// SubSceneManagerクラスのインスタンス
	static std::shared_ptr<SubSceneManager> instance = nullptr;

	// 既に生成されていないときのみ新しく生成
	if (!instance) {
		instance = std::shared_ptr<SubSceneManager>(new SubSceneManager());
	}

	return instance;

}


void SubSceneManager::ChangeSubScene(ScenePlaySubScene nextSubScene) {

	if (nextSubScene == ScenePlaySubScene::BATTLE) {
		// scenePlay_->ChangeSubScene(scenePlay_->getBattleSubScene());

		scenePlay_->ChangeSubSceneToBattle();
	}
	else if (nextSubScene == ScenePlaySubScene::DUNGEON) {
		// scenePlay_->ChangeSubScene(scenePlay_->getDungeonSubScene());

		scenePlay_->ChangeSubSceneToDungeon();
	}
	return;
}
