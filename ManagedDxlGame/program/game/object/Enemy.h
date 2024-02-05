#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../base/CharacterBase.h"


// 前方宣言
class Player;

// ステージ上での敵キャラクターのクラス
// 引数：cellSize...ステージの1マスの大きさ
// startGridPos...生成時の初期位置
class Enemy : public CharacterBase {
public :
	// コンストラクタ
	// cellSize_(マップの1マス分の大きさ)とgridPos_(存在している座標)を初期化
	// 引数：cellSize...ステージの1マスの大きさ
	// startGridPos...生成時の初期位置
	Enemy(float gridSize, tnl::Vector2i startGridPos, std::shared_ptr<Player> player);

	// デストラクタ
	~Enemy();

	// 毎フレーム実行する関数
	void update(float delta_time);

	// 描画用の関数
	void draw( std::shared_ptr<dxe::Camera> camera );


	// シーケンスをIdleから切り替える処理
	void ChangeSeqFromIdle();

	// シーケンスをWaitから次の処理に切り替える処理
	void ChangeSeqFromWait();



private :
	// 前にいたマス
	// 移動を決定する場合は行き止まり以外では前のマス以外に行くようにする
	tnl::Vector2i beforeGrid_ = { 0, 0 };

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
	




	//// プレイヤーの状態用のシーケンス
	//tnl::Sequence<Enemy> seq_ = tnl::Sequence<Enemy>(this, &Enemy::seqIdle);

	//// 待機中のシーケンス
	//bool seqIdle(const float delta_time);
	//// 行動内容を決定するシーケンス
	//bool seqActionDecide(const float delta_time);
	//// 移動を準備するシーケンス
	//bool seqMoveCheck(const float delta_time);
	//// 回転を準備するシーケンス
	//bool seqRotateCheck(const float delta_time);
	//// 待機するシーケンス
	//bool seqWait(const float delta_time);
	//// 移動を行うシーケンス
	//bool seqMoving(const float delta_time);
	//// 回転を行うシーケンス
	//bool seqRotating(const float delta_time);



};