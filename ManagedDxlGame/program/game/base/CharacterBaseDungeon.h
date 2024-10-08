#pragma once

#include "EntityBase.h"


//---------------------------------------------------
// 前方宣言

class Stage;


// プレイヤー・敵キャラクターに継承するベースクラス
// 引数：gridSize...ステージのマスの大きさ
// startPos...生成された際のマップ上での位置
class CharacterBaseDungeon : public EntityBase {
public :

	// コンストラクタ
	// 引数：gridSize...ステージのマスの大きさ
	// startPos...生成された際のマップ上での位置
	CharacterBaseDungeon( float gridSize, tnl::Vector2i startPos );

	// デストラクタ
	virtual ~CharacterBaseDungeon();

	// 毎フレーム処理を行う関数
	virtual void update( float delta_time );

	// 描画処理の関数
	virtual void draw();

	// プレイヤーのTransformを取得する関数
	 ito::Transform getTransform() const { return nowTransform_; }

	// 次の移動先のマスを取得する関数
	 tnl::Vector2i getNextGridPos() const { return nextGridPos_; }

protected :

	// 移動を行う関数
	// Player, Enemy等の移動を行う際はこの関数を使用する
	void Moving(float delta_time);

	// 回転を行う関数
	// Plauer, Enemy等の回転を行う際はこの関数を使用する
	void Rotating(float delta_time);

	// 行動が終了しているかどうかのフラグ
	// Move, Rotate等の処理中はfalseにすること
	bool finishAction_ = true;

	// 次に移動する移動先を計算する関数
	// moveGrid_（マス目を移動する方向ベクトル）も計算
	// 引数：移動方向(Enum::Dir4型)
	// 戻り値：移動先のマスの座標(nextGridPos_に入れる用)
	tnl::Vector2i calcMoveGrid(Enum::eDir4 moveDir);

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

	// 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
	// tnl::Vector2i gridPos_;
	// ↑現在の配列上での座標はEntityBaseクラスにある
	// 取得する関数：getGridPos()
	// 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

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
	Enum::eDir4 nextDir_ = Enum::eDir4::UP;




};