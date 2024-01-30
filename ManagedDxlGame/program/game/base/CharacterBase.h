#pragma once

#include "EntityBase.h"


//---------------------------------------------------
// 前方宣言

class Stage;


class CharacterBase : public EntityBase {
public :

	// コンストラクタ
	// 引数：gridSize...ステージのマスの大きさ
	// startPos...生成された際のマップ上での位置
	CharacterBase( float gridSize, tnl::Vector2i startPos );

	// デストラクタ
	virtual ~CharacterBase();

	// 毎フレーム処理を行う関数
	void update( float delta_time );

	// 描画処理の関数
	void draw();


	const ito::Transform getTransform(){ }


protected :

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

	// シーケンス制御用変数
	tnl::Sequence<CharacterBase> seq_ = tnl::Sequence<CharacterBase>(this, &CharacterBase::seqIdle);

	// 待機中のシーケンス
	// プレイヤーと敵それぞれで個別に
	virtual bool seqIdle(const float delta_time);
	// 移動を準備するシーケンス
	bool seqMoveCheck(const float delta_time);
	// 回転を準備するシーケンス
	bool seqRotateCheck(const float delta_time);
	// 移動を行うシーケンス
	bool seqMoving(const float delta_time);
	// 回転を行うシーケンス
	bool seqRotating(const float delta_time);
};