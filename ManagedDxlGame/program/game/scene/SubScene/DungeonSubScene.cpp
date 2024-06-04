#include "DungeonSubScene.h"
#include "../../map/Stage.h"
#include "../../character/Dungeon/Player.h"
#include "../../character/Dungeon/Enemy.h"
#include "../../manager/TurnManager.h"
#include "../../manager/SubSceneManager.h"
#include "../../other/TransformCamera.h"


// DungeonSubSceneクラスのインスタンスを取得する関数
std::shared_ptr<DungeonSubScene> DungeonSubScene::GetInstance() {

	// DungeonSubSceneクラスのインスタンス
	static std::shared_ptr<DungeonSubScene> instance = nullptr;

	// 既に生成されていないときのみ新しく生成
	if (!instance) {
		instance = std::shared_ptr<DungeonSubScene>(new DungeonSubScene());
	}

	return instance;

}


// コンストラクタ
DungeonSubScene::DungeonSubScene() {

	// 描画用のカメラの初期化
	FPCamera_ = std::make_shared< TransformCamera >(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// ステージを管理するクラスの生成
	stage_ = Stage::GetInstance("test", "csv/mapData.csv", gridSize_);

	// ターンマネージャーの生成とサブシーンマネージャーのセット
	//TurnManager::GetInstance()->setSubSceneManager( SubSceneManager::GetInstance() );


	CreateCharacter();


}

// デストラクタ
DungeonSubScene::~DungeonSubScene() {


}

// 更新用の関数
void DungeonSubScene::update(float delta_time){

	// 線の描画
	// DrawGridGround(FPCamera_, 50, 20);

	// カメラの座標をプレイヤーの座標に合わせる
	FPCamera_->pos_ = player_->getTransform().getPos_();

	// カメラの回転をプレイヤーの回転の状態に合わせる
	FPCamera_->update(player_->getTransform().getRot3D_());



	// ステージの更新
	stage_->update(delta_time);
	// プレイヤーの更新
	player_->update(delta_time);
	// 敵のリストの処理
	auto it = enemyList_.begin();
	while (it != enemyList_.end()) {
		(*it)->update(delta_time);
		++it;
	}

	// ターンマネージャーの更新
	TurnManager::GetInstance()->update(delta_time);


}

// 描画用の関数
void DungeonSubScene::draw() {

	// ステージの描画
	stage_->draw(FPCamera_);

	// 敵のリストの描画処理
	auto it = enemyList_.begin();
	while (it != enemyList_.end()) {
		(*it)->draw(FPCamera_);
		++it;
	}

}


// 敵を消す関数
void DungeonSubScene::DeleteEnemy(std::shared_ptr<Enemy> deleteEnemy) {


	auto it = enemyList_.begin();

	while (it != enemyList_.end()) {

		if ((*it) == deleteEnemy) {

			enemyList_.erase(it);

			break;
		}

		++it;
	}

}


// プレイヤー、敵キャラクターを作成する処理
void DungeonSubScene::CreateCharacter() {

	// プレイヤーの作成
	player_ = std::shared_ptr<Player>(new Player(gridSize_, { 1, 1 }, stage_->getGridObjPos( {1, 1} ) ));

	//// 90度回転した状態で開始
	//player_->getTransform().setRot3D_(player_->getTransform().getRot3D_() * tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(90)));

	// プレイヤーのセット
	TurnManager::GetInstance()->setPlayer(player_);

	// 敵キャラクターの作成
	enemy_ = std::shared_ptr<Enemy>(new Enemy(gridSize_, { 5, 2 }, player_));
	// リストに入れる
	enemyList_.emplace_back(enemy_);
	// 敵のリストをセット
	TurnManager::GetInstance()->setEnemyList(enemyList_);

}
