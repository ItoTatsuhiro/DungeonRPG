#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../base/CharacterBase.h"


// ステージ上での敵キャラクターのクラス
// 引数：cellSize...ステージの1マスの大きさ
// startGridPos...生成時の初期位置
class Enemy : public CharacterBase {
public :
	// コンストラクタ
	// cellSize_(マップの1マス分の大きさ)とgridPos_(存在している座標)を初期化
	// 引数：cellSize...ステージの1マスの大きさ
	// startGridPos...生成時の初期位置
	Enemy(float gridSize, tnl::Vector2i startGridPos);

	// デストラクタ
	~Enemy();

	// 毎フレーム実行する関数
	void update(float delta_time);

	// 描画用の関数
	void draw( std::shared_ptr<dxe::Camera> camera );


private :

	// EnemyのMesh
	// 2Dの画像を貼り付けるPlaneを用意する用
	std::shared_ptr<ito::Object3D> enemyObj_;


	//// プレイヤーの状態用のシーケンス
	//tnl::Sequence<Enemy> seq_ = tnl::Sequence<Enemy>(this, &Enemy::seqIdle);

	//// 待機中のシーケンス
	//bool seqIdle(const float delta_time);
	//// 移動を準備するシーケンス
	//bool seqMoveCheck(const float delta_time);
	//// 回転を準備するシーケンス
	//bool seqRotateCheck(const float delta_time);
	//// 移動を行うシーケンス
	//bool seqMoving(const float delta_time);
	//// 回転を行うシーケンス
	//bool seqRotating(const float delta_time);



};