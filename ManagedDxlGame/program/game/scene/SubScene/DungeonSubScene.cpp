#include "DungeonSubScene.h"
#include "../../map/Stage.h"
#include "../../character/Dungeon/Player.h"
#include "../../character/Dungeon/Enemy.h"
#include "../../manager/TurnManager.h"
#include "../../manager/SubSceneManager.h"
#include "../../other/TransformCamera.h"
#include "../../other/Enum.h"


// コンストラクタ
DungeonSubScene::DungeonSubScene() {

	// 描画用のカメラの初期化
	FPCamera_ = std::make_shared< TransformCamera >(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// ステージを管理するクラスの生成
	stage_ = Stage::GetInstance("test", "csv/mapData.csv", gridSize_);

	// ターンマネージャー生成
	turnManager_ = std::shared_ptr<TurnManager>(new TurnManager());

	// キャラクター生成
	CreateCharacter();

	// 方向表示用のコンパスの画像を読み込み
	directionGpcHdl_ = ito::ResourceManager::GetInstance()->loadGraph("compass.png");
	// 操作説明画像の読み込み
	controlExpGpcHdl_ = ito::ResourceManager::GetInstance()->loadGraph("controlExp.png");

	// BGM読み込み
	dungeonBgmHdl_ = ito::ResourceManager::GetInstance()->loadSoundMem("キネマティック_03.mp3");

	// 音量調整
	ChangeVolumeSoundMem(50, dungeonBgmHdl_);
}

// デストラクタ
DungeonSubScene::~DungeonSubScene() {

	turnManager_.reset();
	player_.reset();

	enemyList_.clear();

}

// 更新用の関数
void DungeonSubScene::update(float delta_time){

	// BGMが流れていないとき再生
	if (!isPlayingBGM_) {

		PlaySoundMem(dungeonBgmHdl_, DX_PLAYTYPE_LOOP);

		isPlayingBGM_ = true;
	}

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


	// 表示する方向の画像の向きを計算
	switch (player_->getFrontDir()) {
	case Enum::eDir4::UP :
		directionGpcAngle_ = 0;
		break;
	case Enum::eDir4::DOWN:
		directionGpcAngle_ = tnl::PI ;
		break;
	case Enum::eDir4::LEFT:
		directionGpcAngle_ = tnl::PI / 2;
		break;
	case Enum::eDir4::RIGHT:
		directionGpcAngle_ = tnl::PI * 1.5;
		break;
	default :
		directionGpcAngle_ = 0;
		break;
	}

	// コンパス画像の表示
	DrawRotaGraph(directionGpcPos_.x, directionGpcPos_.y, directionGpcSize_, directionGpcAngle_, directionGpcHdl_, true);

	// 操作説明の表示
	DrawRotaGraph(controlExpPos_.x, controlExpPos_.y, controlExpSize_, 0, controlExpGpcHdl_, true);

}

// サブシーン切り替えの際に実行する関数
void DungeonSubScene::ChangeSubScene() {

	// BGM停止
	StopSoundMem(dungeonBgmHdl_);

	isPlayingBGM_ = false;
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
