#include "ScenePlay.h"

#include "../manager/TurnManager.h"

ScenePlay::ScenePlay() {

	// camera_ = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	FPCamera_ = std::make_shared< TransformCamera >(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// ステージを管理するクラスの生成
	stage_ = Stage::GetInstance("test", "csv/mapData.csv", gridSize_);

	
	turnManager_ = TurnManager::GetInstance();


	CreateCharacter();

}


ScenePlay::~ScenePlay() {

}


void ScenePlay::update(float delta_time) {

	DrawGridGround(FPCamera_, 50, 20);

	FPCamera_->pos_ = player_->getTransform().getPos_();
	//FPCamera_->angle_ = tnl::ToRadian(15);


	FPCamera_->update( player_->getTransform().getRot3D_() );



	// ステージの更新
	stage_->update(delta_time);

	player_->update(delta_time);

	// 敵のリストの処理
	auto it = enemyList_.begin();
	while (it != enemyList_.end()) {
		(*it)->update(delta_time);
		++it;
	}

	TurnManager::GetInstance()->update(delta_time);


	// enemy_->update(delta_time);





}

void ScenePlay::draw() {

	// ステージの描画
	stage_->draw(FPCamera_);

	// enemy_->draw(FPCamera_);

	// 敵のリストの描画処理
	auto it = enemyList_.begin();

	while (it != enemyList_.end()) {
		(*it)->draw(FPCamera_);
		++it;
	}

}


void ScenePlay::CreateCharacter() {

	// プレイヤーの作成
	player_ = std::shared_ptr<Player>(new Player(gridSize_, { 0, 0 }));

	TurnManager::GetInstance()->setPlayer(player_);

	enemy_ = std::shared_ptr<Enemy>(new Enemy(gridSize_, { 4, 1 }, player_));


	enemyList_.emplace_back(enemy_);

	TurnManager::GetInstance()->setEnemyList(enemyList_);
}
