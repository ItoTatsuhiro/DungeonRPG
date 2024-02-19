#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "../../other/Enum.h"

// バトルシーンで操作するプレイヤーのクラス
// ダンジョンシーンと異なり、メッシュを持つ
// また、視点は1人称視点ではない
class BattlePlayer : public ito::Object3D {
public :
	// コンストラクタ
	// 引数：開始位置
	BattlePlayer( tnl::Vector3 startPos );
	// デストラクタ
	~BattlePlayer();
	// 更新用の関数
	void update(float delta_time);
	// 描画用の関数
	void draw( std::shared_ptr<dxe::Camera> camera);

	// 当たり判定のメッシュを取得する関数
	std::shared_ptr<ito::Object3D> getHitBox() { return hitBox_; }

	// 移動前の座標を取得する関数
	// 座標の補正等の際に使用
	tnl::Vector3 getBeforePos() { return beforePos_; }


private :

	// 当たり判定となるメッシュ(Box)
	std::shared_ptr<ito::Object3D> hitBox_ = nullptr;
	// 画像を表示させるメッシュ(Plane)
	std::vector<std::vector<std::shared_ptr<ito::Object3D>>> playerObjArray_;
	// 貼り付けるテクスチャの分割数
	// コンストラクタで読み込み
	tnl::Vector2i textureCutNum_ = { 0, 0 };
	// 貼り付けるテクスチャ
	std::shared_ptr<dxe::Texture> playerTexture_ = nullptr;
	// 移動前の座標
	// 座標の補正の際にこの座標を使用する
	tnl::Vector3 beforePos_;

	// 作成するメッシュの大きさ
	float meshSize_ = 50;

	// 向いている向き
	// デフォルトでは右向き
	Enum::Dir4 frontDir = Enum::Dir4::RIGHT;
	
	// 画像の向いている向き
	// 画像は左右の絵しかないため、左右を押した際に向きに応じて切り替わる
	// 上下の移動では切り替えない
	Enum::Dir4 animFrontDir = Enum::Dir4::RIGHT;

	// アニメーション用のメッシュを切り替える時間
	const float animChangeTime_ = 0.15;
	// 現在のアニメーションを再生している時間
	// 移動等のアニメーションは止めた際に0にリセットする
	float animChangeCount_ = 0;

	// 表示中のオブジェクトの番号
	tnl::Vector2i displayObj_ = { 0, 0 };

	// 移動量
	float moveValue_ = 5;

	// 移動を行う関数
	void Move(float delta_time);

	// 攻撃の処理に入るための関数
	// 攻撃のためのキー入力が入ったときシーケンスを切り替える処理を行う
	void OnAttackKey();

	// 攻撃のリスト
	std::list<std::shared_ptr<ito::Object3D>> attackList_;

	// 攻撃の大きさ
	// コンストラクタで初期化
	float attackSize_ = 0;

	// シーケンス処理用の変数
	tnl::Sequence<BattlePlayer> seq_ = tnl::Sequence<BattlePlayer>(this, &BattlePlayer::seqIdle);

	// 待機中のシーケンス
	bool seqIdle(const float delta_time);
	// 攻撃のシーケンス
	bool seqAttack(const float delta_time);

};
