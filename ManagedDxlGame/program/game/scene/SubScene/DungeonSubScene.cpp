#include "DungeonSubScene.h"
#include "../../map/Stage.h"
#include "../../character/Dungeon/Player.h"
#include "../../character/Dungeon/Enemy.h"
#include "../../manager/TurnManager.h"
#include "../../manager/SubSceneManager.h"
#include "../../other/TransformCamera.h"


// コンストラクタ
DungeonSubScene::DungeonSubScene() {

	// 描画用のカメラの初期化
	FPCamera_ = std::make_shared< TransformCamera >(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// ステージを管理するクラスの生成
	stage_ = Stage::GetInstance("test", "csv/mapData.csv", gridSize_);


	turnManager_ = std::shared_ptr<TurnManager>(new TurnManager());

	CreateCharacter();

}

// デストラクタ
DungeonSubScene::~DungeonSubScene() {

	turnManager_.reset();
	player_.reset();

	enemyList_.clear();

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
	turnManager_->update(delta_time);


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

			turnManager_->setEnemyList(enemyList_);

			break;
		}

		++it;
	}

}


// プレイヤー、敵キャラクターを作成する処理
void DungeonSubScene::CreateCharacter() {

	// プレイヤーの作成
	player_ = std::shared_ptr<Player>(new Player(gridSize_, { 1, 1 }, stage_->getGridObjPos( {1, 1} ), turnManager_ ));


	// プレイヤーのセット
	turnManager_->setPlayer(player_);

	// 敵キャラクターの作成
	enemy_ = std::shared_ptr<Enemy>(new Enemy(gridSize_, { 5, 2 }, player_, turnManager_));
	// リストに入れる
	enemyList_.emplace_back(enemy_);
	// 敵のリストをセット
	turnManager_->setEnemyList(enemyList_);

}
