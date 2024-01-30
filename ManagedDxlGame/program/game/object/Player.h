#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

#include "../other/Enum.h"
#include "../base/EntityBase.h"
#include "../map/Stage.h"

// 操作を行うプレイヤーのクラス
// 引数：
class Player final : public EntityBase {
public :

	// プレイヤークラスのコンストラクタ
	// cellSize_(マップの1マス分の大きさ)とgridPos_(存在している座標)を初期化
	// 引数：cellSize, startGridPos
	Player( float gridSize, tnl::Vector2i startGridPos );

	// プレイヤークラスのデストラクタ
	~Player();

	void update(float delta_time);

	// プレイヤーのTransformを取得する関数
	const ito::Transform& getTransform() { return nowTransform_; }

	// 次に移動する移動先を計算する関数
	// moveGrid_（マス目を移動する方向ベクトル）も計算
	// 引数：移動方向(Enum::Dir4型)
	// 戻り値：移動先のマスの座標(nextGridPos_に入れる用)
	tnl::Vector2i calcMoveGrid( Enum::Dir4 moveDir );
	
private :

	// ステージのポインタ
	// シーンで生成してあるStageクラスから、ステージの配列の情報を持ってくるために使用
	std::shared_ptr<Stage> stage_;

	// 現在のtransform情報
	// 座標(pos_)と回転の情報(rot_)を使用
	ito::Transform nowTransform_;

	// 次のtransform情報
	// 座標(pos_)と回転の情報(rot_)を使用
	ito::Transform nextTransform_;

	// 次に移動する座標(ステージの配列上)
	tnl::Vector2i nextGridPos_;

	// マス目上を移動する方向のベクトル
	// nextGridPos_ - gridPos_で移動前に計算
	tnl::Vector2i moveGrid_;

	// ～～～～～～～～～～～～～～～～～～～～～～～～～
	// tnl::Vector2i gridPos_;
	// ↑現在の配列上での座標はEntityBaseクラスにある
	// 取得する関数：getGridPos()
	// ～～～～～～～～～～～～～～～～～～～～～～～～～

	// 1フレームで移動する量
	float moveVal_ = 0;

	// 1フレーム内で回転させる量
	float rotValFrame_ = 3.0f;

	// 回転させる最大量
	// seqRotateCheckで値を入れ、毎フレーム回転させる毎に値を引く
	float rotValMax_ = 0;

	// 次の位置に移動できるかどうかのフラグ
	bool isMove_ = true;

	// 正面の向きの変数はEntityBaseクラスに存在

	// 次に向く方向の変数
	// Dir4クラスは別ファイルで定義
	Enum::Dir4 nextDir_ = Enum::Dir4::UP;

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
