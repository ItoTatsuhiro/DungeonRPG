#pragma once

#include "../other/BattleCharacterBase.h"

// バトルシーンでの敵キャラクターのクラス
// 引数：tnl::Vector3 startPos...開始位置, float objSize...オブジェクトの大きさ, std::string objectName...オブジェクト名
class BattleEnemy : public BattleCharacterBase {
public :
	// コンストラクタ
	// 引数：tnl::Vector3 startPos...開始位置, float objSize...オブジェクトの大きさ, std::string objectName...オブジェクト名
	// 移動前の座標は開始位置で初期化
	// SpriteObjectBaseの引数も入れる
	BattleEnemy(tnl::Vector3 startPos, float objSize, std::string objName);

	// デストラクタ
	~BattleEnemy();

	// 更新用の関数
	void update(float delta_time) override;
	// 描画用の関数
	void draw(std::shared_ptr<dxe::Camera> camera) override;


protected :

	// 移動を行う関数
	void Move(float delta_time);

	// 攻撃の処理に入るための関数
	// 攻撃のためのキー入力が入ったときシーケンスを切り替える処理を行う
	void OnAttackKey();

	// 移動する目標地点の座標
	tnl::Vector3 moveTargetPos_;


	// 攻撃の大きさ
	// コンストラクタで初期化
	float attackSize_;

	// シーケンス処理用の変数
	tnl::Sequence<BattleEnemy> seq_ = tnl::Sequence<BattleEnemy>(this, &BattleEnemy::seqActDecade);

	// 行動を決定するシーケンス
	bool seqActDecade(const float delta_time);
	// 移動を行うシーケンス
	bool seqMove(const float delta_time);
	// 攻撃のシーケンス
	bool seqAttack(const float delta_time);

};