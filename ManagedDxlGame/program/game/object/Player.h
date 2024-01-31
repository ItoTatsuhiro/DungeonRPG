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

	
private :


	std::string seqNow_ = "seqIdle";



	// プレイヤーの状態用のシーケンス
	tnl::Sequence<Player> seq_ = tnl::Sequence<Player>(this, &Player::seqIdle);

	// 待機中のシーケンス
	bool seqIdle(const float delta_time);
	// 移動を準備するシーケンス
	bool seqMoveCheck(const float delta_time);
	// 回転を準備するシーケンス
	bool seqRotateCheck(const float delta_time);
	// 移動を行うシーケンス
	bool seqMoving(const float delta_time);
	// 回転を行うシーケンス
	bool seqRotating(const float delta_time);
};
