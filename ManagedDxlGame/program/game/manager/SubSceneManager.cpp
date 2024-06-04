#include "SubSceneManager.h"
#include "../scene/SubScene/BattleSubScene.h"
#include "../scene/SubScene/DungeonSubScene.h"
#include "../character/Dungeon/Enemy.h"

SubSceneManager::SubSceneManager() {

	// ダンジョンサブシーンの生成
	dungeonSubScene_ = std::shared_ptr<DungeonSubScene>(new DungeonSubScene());



	nowSubScene_ = dungeonSubScene_;

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


// 更新用の関数
// 現在のサブシーンの更新を行う
void SubSceneManager::update(float delta_time) {

	if (!nowSubScene_) {
		return;
	}

	nowSubScene_->update(delta_time);

}

// 描画用の関数
// 現在のサブシーンの描画を行う関数
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

// バトルシーンの作成,遷移
// バトルシーンに遷移する際、この関数を呼び出す
void SubSceneManager::ChangeBattleScene(std::shared_ptr<Enemy> battlingEnemy) {


	// 敵キャラクターをセット
	battlingEnemy_ = battlingEnemy;

	battleSubScene_ = std::shared_ptr<BattleSubScene>(new BattleSubScene());

	nowSubScene_ = battleSubScene_;

}


void SubSceneManager::Destroy() {

	dungeonSubScene_.reset();
	battleSubScene_.reset();

	SubSceneManager::GetInstance().reset();
}