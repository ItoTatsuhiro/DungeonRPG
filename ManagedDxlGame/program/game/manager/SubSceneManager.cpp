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

	// nowSubScene_->update(delta_time);

	seq_.update(delta_time);


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_P)) {
		debugMode_ = true;
	}

	if (debugMode_) {
		screenEffect_->drawGuiController( {0, 0} );
	}
}

// 描画用の関数
// 現在のサブシーンの描画を行う関数
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

	// 引数として値を入れられた時はその値、入れられなかったときは変数のbattlingEnemyを入れる
	battlingEnemy_ = (battlingEnemy != nullptr) ? battlingEnemy : battlingEnemy_;

	seq_.change(&SubSceneManager::seqSubSceneChange);


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

// 初期設定を行う関数
void SubSceneManager::SetUp() {

	// スクリーンエフェクトのリセット
	if (screenEffect_) {
		screenEffect_.reset();
	}
	// スクリーンエフェクトクラスの生成
	screenEffect_ = std::shared_ptr<dxe::ScreenEffect>(new dxe::ScreenEffect(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT));
	// 設定したステータスの読み込み
	screenEffect_->loadStatus("screen_effect.bin");

	// サブシーンのリセット
	if (dungeonSubScene_) {
		dungeonSubScene_.reset();

	}
	if (battleSubScene_) {
		battleSubScene_.reset();

	}

	// ダンジョンサブシーンの生成
	dungeonSubScene_ = std::shared_ptr<DungeonSubScene>(new DungeonSubScene());
	// 現在のサブシーンを設定
	nowSubScene_ = dungeonSubScene_;
	// シーン切り替え時の画像を読み込み
	transGpc_ = ito::ResourceManager::GetInstance()->loadGraph("black.png");

}


// インスタンスを削除する関数
void SubSceneManager::Destroy() {

	dungeonSubScene_.reset();
	battleSubScene_.reset();

	SubSceneManager::GetInstance().reset();
}


// サブシーンの更新を行うシーケンス
bool SubSceneManager::seqSubSceneUpdate(const float delta_time) {

	nowSubScene_->update(delta_time);

	return true;
}

// サブシーンを切り替える際のシーケンス
// 基本的に画面の暗転を行う
bool SubSceneManager::seqSubSceneChange(const float delta_time) {


	float blurAlpha = (seq_.getProgressTime() / transTime_);
	screenEffect_->setBlurAlpha(blurAlpha);


	int levelMin = blurAlpha * 255.0f;
	screenEffect_->setLevelMin(levelMin);



	if (blurAlpha >= 1.0f) {

		// シーンを切り替える
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


// サブシーンを開始する際のシーケンス
// 基本的に画面を明るくする処理を行う
bool SubSceneManager::seqSubSceneStart(const float delta_time) {

	float blurAlpha = (1.0f - seq_.getProgressTime() / transTime_) >= 0 ? (1.0f - seq_.getProgressTime() / transTime_) : 0;
	screenEffect_->setBlurAlpha(blurAlpha);


	int levelMin = blurAlpha * 255;
	screenEffect_->setLevelMin(levelMin);



	if (blurAlpha == 0.0f) {

		// シーケンスを切り替える
		seq_.change(&SubSceneManager::seqSubSceneUpdate);

	}


	return true;

}