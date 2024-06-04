#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "../../other/Enum.h"
#include "../../base/SpriteObjectBase.h"
#include "../other/BattleCharacterBase.h"


// バトルシーンで操作するプレイヤーのクラス
// ダンジョンシーンと異なり、メッシュを持つ
// CharacterBaseBattleを継承
// 引数：tnl::Vector3 startPos...開始位置, float objSize...オブジェクトの大きさ, std::string objectName...オブジェクト名
class BattlePlayer : public BattleCharacterBase {
public :
	// コンストラクタ
	// 引数：tnl::Vector3 startPos...開始位置, float objSize...オブジェクトの大きさ, std::string objectName...オブジェクト名
	// 移動前の座標は開始位置で初期化
	// SpriteObjectBaseの引数も入れる
	BattlePlayer( tnl::Vector3 startPos,float objSize, std::string objName );
	// デストラクタ
	~BattlePlayer();
	// 更新用の関数
	void update(float delta_time) override;
	// 描画用の関数
	void draw( std::shared_ptr<dxe::Camera> camera) override;


protected :


	// 移動を行う関数
	void Move(float delta_time);

	// 攻撃の処理に入るための関数
	// 攻撃のためのキー入力が入ったときシーケンスを切り替える処理を行う
	void OnAttackKey();


	//// 攻撃の大きさ
	//// コンストラクタで初期化
	//float attackSize_;

	// シーケンス処理用の変数
	tnl::Sequence<BattlePlayer> seq_ = tnl::Sequence<BattlePlayer>(this, &BattlePlayer::seqIdle);

	// 待機中のシーケンス
	bool seqIdle(const float delta_time);
	// 攻撃のシーケンス
	bool seqAttack(const float delta_time);

};
