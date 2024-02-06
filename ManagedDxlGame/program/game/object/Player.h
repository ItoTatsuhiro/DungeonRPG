#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

#include "../other/Enum.h"
#include "../base/CharacterBase.h"
#include "../map/Stage.h"

// 操作を行うプレイヤーのクラス
// 引数：
class Player final : public CharacterBase {
public :

	// プレイヤークラスのコンストラクタ
	// cellSize_(マップの1マス分の大きさ)とgridPos_(存在している座標)を初期化
	// 引数：cellSize, startGridPos
	Player( float gridSize, tnl::Vector2i startGridPos );

	// プレイヤークラスのデストラクタ
	~Player();

	void update(float delta_time);

	// シーケンスをWaitから次の処理に切り替える処理
	void ChangeSeqFromWait();
	

	enum class PlayerSeq {
		IDLE,			// 待機状態のシーケンス
		MOVE_CHECK,		// 移動の確認のシーケンス
		ROTATE_CHECK,	// 回転の確認のシーケンス
		WAIT,			// 待機中のシーケンス
		MOVING,			// 移動を行うシーケンス
		ROTATING		// 回転を行うシーケンス

	};

	PlayerSeq getNowSeq() const { return nowSeq_; }

private :

	// デバッグ用の状態
	// trueのときエネミーの処理を待たずに動ける
	bool debugMode_ = false;




	// 実行中のシーケンス
	PlayerSeq nowSeq_ = PlayerSeq::IDLE;

	// 実行する行動
	// WAITに移動する際に決定したシーケンスを入れる
	// WAITから切り替える際にこれを参照して切り替える
	// 行動が決定していないときはWAITにしておく
	PlayerSeq decadedSeq = PlayerSeq::WAIT;

	// プレイヤーの状態用のシーケンス
	tnl::Sequence<Player> seq_ = tnl::Sequence<Player>(this, &Player::seqIdle);

	// 待機中のシーケンス
	bool seqIdle(const float delta_time);
	// 移動を準備するシーケンス
	bool seqMoveCheck(const float delta_time);
	// 回転を準備するシーケンス
	bool seqRotateCheck(const float delta_time);
	// 待機するシーケンス
	bool seqWait(const float delta_time);
	// 移動を行うシーケンス
	bool seqMoving(const float delta_time);
	// 回転を行うシーケンス
	bool seqRotating(const float delta_time);
};
