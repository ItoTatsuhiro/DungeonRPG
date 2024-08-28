#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

#include "../character/Dungeon/Enemy.h"

// 前方宣言
class Player;
class Enemy;
class SubSceneManager;


// ターンの処理を管理する用のクラス
// プレイヤー、敵の処理状態を確認し、揃える役割
class TurnManager final{
public :

	// コンストラクタ
	TurnManager();


	// デストラクタ
	~TurnManager();

	// 更新用の関数
	void update(float delta_time);

	// プレイヤーをセットする関数
	// シーンで呼び出してセットする
	// 引数：プレイヤー
	void setPlayer(std::shared_ptr<Player> player) { player_ = player; };
	// 敵のリストをセットする関数
	// シーンで呼び出してセットする
	// 引数：敵のリスト
	void setEnemyList(std::list<std::shared_ptr<Enemy>> enemyList);

	//// サブシーンマネージャーをセットする関数
	//// シーンで呼び出してセット
	//// 引数：サブシーンマネージャー
	//void setSubSceneManager(std::shared_ptr<SubSceneManager> subSceneManager) { subSceneManager_ = subSceneManager; }

	// プレイヤーが入力が行われた際に呼び出す関数
	// 敵の処理を行うシーケンスに遷移するための関数
	void ChangeSeqFromWaitPlayerInput();

	// プレイヤーの行動が終了した際に呼び出す関数
	// actionEndPlayer_をtrueにする
	void ActionEndPlayer();

	// 敵の行動が終了した際に呼び出す関数
	// actionEndEnemyListのうち、falseを一つtrueにする関数
	void ActionEndEnemy();

	// 自身を削除する関数
	void Destroy();

private :

	// キャラクターの位置を確認する関数
	void CheckCharacterPos();

	//// サブシーンマネージャーのインスタンス
	//// ターンマネージャーが生成された際に引数で入れる
	//std::shared_ptr<SubSceneManager> subSceneManager_ = nullptr;

	// プレイヤー
	// シーンでsetPlayer関数を用いてセットする
	// 座標等取得に必要
	std::weak_ptr<Player> player_;

	// 敵キャラクターのリスト
	// シーンでsetEnemyList関数でセットする
	// 座標取得に必要
	// ***************************************************
	// 修正する！
	// ***************************************************
	std::list<std::shared_ptr<Enemy>> enemyList_;

	// プレイヤーの行動が終了しているかどうかのフラグ
	bool actionEndPlayer_ = false;


	std::list<bool> actionEndEnemyList_;

	// 敵キャラクターが動くかどうかのフラグ
	bool canMoveEnemy_ = true;




	// ターンマネージャーのシーケンスを表す定数
	enum class TurnManagerSeq {
		WAIT_PLAYER_INPUT,
		ENEMY_ACTION_DICADE,
		CHECK_ACTION,
		ACTION
	};

	// ターンを切り替える際のフラグ
	bool isSceneChange_ = false;

	// シーンを切り替える際の暗転時間
	float transTime_ = 0.5f;
	// シーンを切り替える際の暗転用
	int transGpc_ = 0;

	tnl::Vector2i goalPos_;

	std::weak_ptr< Enemy > battlingEnemy_;

	// 現在のシーケンス
	TurnManagerSeq nowSeq_ = TurnManagerSeq::WAIT_PLAYER_INPUT;

	// 動作を管理する用のシーケンス
	tnl::Sequence<TurnManager> seq_ = tnl::Sequence<TurnManager>(this, &TurnManager::seqWaitPlayerInput);

	// プレイヤーの入力待ちのシーケンス
	bool seqWaitPlayerInput(const float delta_time);
	// 敵キャラクターの行動を決定するシーケンス
	bool seqEnemyActionDecade(const float delta_time);
	// それぞれのキャラクターの行動を確認するシーケンス
	bool seqCheckAction(const float delta_time);
	// 行動を行うシーケンス
	bool seqAction(const float delta_time);
	// サブシーンを切り替えるシーケンス
	bool seqChangeSubScene(const float delta_time);
};