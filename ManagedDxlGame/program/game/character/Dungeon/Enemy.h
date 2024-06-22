#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "../../base/CharacterBaseDungeon.h"


// 前方宣言
class Player;
class TurnManager;

// ステージ上での敵キャラクターのクラス
// 引数：cellSize...ステージの1マスの大きさ
// startGridPos...生成時の初期位置
class Enemy : public CharacterBaseDungeon {
public :
	// コンストラクタ
	// cellSize_(マップの1マス分の大きさ)とgridPos_(存在している座標)を初期化
	// 引数：gridSize...ステージの1マスの大きさ
	// startGridPos...生成時の初期位置
	Enemy(float gridSize, tnl::Vector2i startGridPos, std::shared_ptr<Player> player, std::shared_ptr<TurnManager> turnManager);

	// デストラクタ
	~Enemy();

	// 毎フレーム実行する関数
	void update(float delta_time);

	// 描画用の関数
	void draw( std::shared_ptr<dxe::Camera> camera );

	// 自身を削除する関数
	void Destroy();

	// シーケンスをIdleから切り替える処理
	void ChangeSeqFromIdle();

	// シーケンスをWaitから次の処理に切り替える処理
	void ChangeSeqFromWait();

	// 敵のシーケンスを表す定数
	enum class EnemySeq {
		IDLE,				// プレイヤーの入力待ち
		ACTION_DICADE,		// 行動を決定
		MOVE_CHECK,			// 移動の確認
		ROT_CHECK,			// 回転の確認
		WAIT,				// 待機
		MOVING,				// 移動中
		ROTATING			// 回転中
	};

	EnemySeq getNowSeqEnemy() const { return nowSeq_; }

private :

	// ターン管理用のクラス
	// サブシーンで作成し引数で渡してくる
	std::shared_ptr<TurnManager> turnManager_;

	// 特定のキーを押したときに敵だけで動くようにする
	bool actDebugMove = false;


	// 進行方向
	// 壁等にぶつかるまでは進行方向に進み続ける
	Enum::Dir4 moveDir_ = frontDir_;

	// EnemyのMesh
	// 2Dの画像を貼り付けるPlaneを用意する用
	std::vector< std::vector< std::shared_ptr<ito::Object3D>>> enemyObjArray_;

	// 貼り付けるテクスチャ
	std::shared_ptr<dxe::Texture> enemyTexture_;

	// テクスチャの分割数
	tnl::Vector2i textureCutNum_;

	// 表示中のオブジェクトの番号
	tnl::Vector2i displayObj_ = { 0, 0 };

	// 現在のアニメーションを表示している時間
	float animCount_ = 0;
	// アニメーションを切り替える時間
	float animTime_ = 0.5f;

	tnl::Vector3 size;

	std::shared_ptr<Player> player_ = nullptr;
	

	// 現在のシーケンス
	EnemySeq nowSeq_ = EnemySeq::IDLE;

	// 実行する行動
	// WAITに移動する際に決定したシーケンスを入れる
	// WAITから切り替える際にこれを参照して切り替える
	// 行動が決定していないときはWAITにしておく
	EnemySeq decadedSeq_ = EnemySeq::WAIT;

	// 敵の状態用のシーケンス
	tnl::Sequence<Enemy> seq_ = tnl::Sequence<Enemy>(this, &Enemy::seqIdle);

	// 待機中のシーケンス
	bool seqIdle(const float delta_time);
	// 行動内容を決定するシーケンス
	bool seqActionDecide(const float delta_time);
	// 移動を準備するシーケンス
	bool seqMoveCheck(const float delta_time);
	// 回転を準備するシーケンス
	bool seqRotateCheck(const float delta_time);
	// 行動待ちシーケンス
	bool seqWait(const float delta_time);
	// 移動を行うシーケンス
	bool seqMoving(const float delta_time);
	// 回転を行うシーケンス
	bool seqRotating(const float delta_time);



};