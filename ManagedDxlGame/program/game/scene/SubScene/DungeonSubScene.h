#pragma once
#include "../../base/SubSceneBase.h"



// --------------------------------------------------------------
// 前方宣言
class Stage;
class Player;
class Enemy;
class TurnManager;
class TransformCamera;


// ダンジョン上での操作を行うサブシーン
// シーンプレイ内で必要に応じてupdate,drawする
class DungeonSubScene final : public SubSceneBase {
public :

	// コンストラクタ
	DungeonSubScene();
	// デストラクタ
	~DungeonSubScene();

	// 更新用の関数
	void update(float delta_time) override;

	// 描画用の関数
	void draw() override;

	// ステージを取得する関数
	std::shared_ptr<Stage> getStage() const { return stage_; }
	// プレイヤーを取得する関数
	std::shared_ptr<Player> getPlayer() const { return player_; }
	// 敵キャラクターを取得する関数
	std::shared_ptr<Enemy> getEnemy() const { return enemy_; }

private:


	std::shared_ptr< TurnManager > turnManager_ = nullptr;

	// プレイヤー、エネミーを生成する関数
	void CreateCharacter();

	// 一人称のカメラ
	std::shared_ptr< TransformCamera > FPCamera_;


	// ステージを管理するクラス
	std::shared_ptr<Stage> stage_ = nullptr;

	// プレイヤーのクラス
	std::shared_ptr<Player> player_ = nullptr;

	// 敵キャラクターのクラス
	std::shared_ptr<Enemy> enemy_ = nullptr;

	// 敵キャラクターのリスト
	std::list<std::shared_ptr<Enemy>> enemyList_;


	// 1マスの縦横の大きさ
	float gridSize_ = 50;


};