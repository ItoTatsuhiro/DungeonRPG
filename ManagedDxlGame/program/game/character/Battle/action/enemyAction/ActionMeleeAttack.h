#pragma once
#include "../../../../../dxlib_ext/dxlib_ext.h"
#include "../BattleActionBase.h"
#include "../../../other/BattleCharacterBase.h"
#include "../ActionAttackBase.h"


// 移動の行動のクラス
// 移動のみの行動を行う場合に使用する
// ランダムな位置を決定し、移動させる
class ActionMeleeAttack final : public ActionAttackBase {
public:

	// コンストラクタ
	// 引数：actionCharacter ... 行動を行うキャラクター, charaList...シーンに存在するキャラクターのリスト
	ActionMeleeAttack(const std::shared_ptr<BattleCharacterBase>& actionCharacter, const std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>>& charaList);

	// デストラクタ
	~ActionMeleeAttack();

	// 行動を実行するupdate関数
	void update(const float delta_time);


	// 行動を実行する前に、数値を初期化するための関数
	// 移動先の座標（targetPos_）、移動量関連（moveValue_, moveVectorNor_, moveVector_）を再度計算
	void setUpAction() override;


	// 移動先の座標を決定する
	void targetPosDecade();


	// 攻撃対象を選択する関数
	// ActionAttackBaseの仮想関数をオーバーライドして使用
	void SelectTargetCharacter() override;


private:




	// 目標地点の座標
	// 関数で移動地点の変更毎に変更
	tnl::Vector3 targetPos_;

	// 攻撃を行う範囲
	// この範囲内まで移動した際に攻撃を実行する
	float attackRange_;

	// 移動量の倍率
	// 攻撃前に近づく速度を通常の移動速度より速くしたい場合に変更
	// 通常は1.0f
	float moveVectorMag_;




	// 移動範囲の最大の大きさ
	// （キャラクターからの半径）
	// 関数で移動地点の変更毎に変更
	float moveRangeMax_;

	// 移動範囲の最小の大きさ
	// （キャラクターからの半径）
	// 関数で移動地点の変更毎に変更
	float moveRangeMin_;

	//// 移動量
	// 関数で移動地点の変更毎に変更
	float moveValue_;

	// 移動した距離をカウントする変数
	// この値がtotalMoveValue_を超えたとき移動の処理を終了させる
	float movedValueCount_;

	// 最終的に移動する距離の変数
	// 移動の際に、最終的にこの距離を進むようにする
	float totalMoveValue_;

	// 移動方向のベクトル
	// コンストラクタ内で計算し初期化
	tnl::Vector3 moveVectorNor_;

	// 移動のベクトル
	// コンストラクタ内で計算し初期化
	tnl::Vector3 moveVector_;

	// 移動処理後に現在の位置を確認する処理
	void CheckPosition();


	// 攻撃の方向を決定する関数
	void SetAttackDetail();



	tnl::Sequence<ActionMeleeAttack> seq_ = tnl::Sequence<ActionMeleeAttack>(this, &ActionMeleeAttack::seqComing);


	// 近寄ってくる際のシーケンス
	bool seqComing(const float delta_time);
	// 近接攻撃を行うシーケンス
	bool seqMeleeAttack(const float delta_time);


};