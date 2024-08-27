#pragma once
#include "../../../../../dxlib_ext/dxlib_ext.h"
#include "../BattleActionBase.h"
#include "../../../other/BattleCharacterBase.h"
#include "../ActionAttackBase.h"


// これも続き各！！！！！！！！！！！！！！！！！！！１１１１１１１


// 移動の行動のクラス
// 移動のみの行動を行う場合に使用する
// ランダムな位置を決定し、移動させる
class ActionRangeAttack final : public ActionAttackBase {
public:

	// コンストラクタ
	// 引数：	actionCharacter ... 行動を行うキャラクター,
	//			charaList...シーンに存在するキャラクターのリスト
	//			waitTimeBefore...攻撃前の待機時間、デフォルトで1.0f
	//			waitTimeAfter...攻撃後の待機時間、デフォルトで1.0f
	ActionRangeAttack(const std::shared_ptr<BattleCharacterBase>& actionCharacter,
						const std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>>& charaList,
						float waitTimeBefore = 1.0f, float waitTimeAfter = 1.0);

	// デストラクタ
	~ActionRangeAttack();

	// 行動を実行するupdate関数
	void update(const float delta_time);


	// 行動を実行する前に、数値を初期化するための関数
	// 移動先の座標（targetPos_）、移動量関連（moveValue_, moveVectorNor_, moveVector_）を再度計算
	void setUpAction() override;



	// 攻撃対象を選択する関数
	// ActionAttackBaseの仮想関数をオーバーライドして使用
	void SelectTargetCharacter() override;



private:

	// ***********************************************************
	// 遠距離攻撃を生成する関数
	// 元の関数では通常の攻撃判定を作成するのみだったため、
	// 遠距離攻撃を生成する処理に変更して作ること！！！！！！！！！！！！
	//void MakeAttack(std::string fileName = "attackEffect.png", tnl::Vector3 pos = { 0, 0, 0 },
	//	float attackSize = 50, Enum::eDir4 front = Enum::eDir4::UP, float damage = 1.0f) override;



	// 攻撃前の待機時間
	float waitTimeBefore_;

	// 攻撃後の待機時間
	float waitTimeAfter_;

	// 遠距離攻撃の目標地点
	tnl::Vector3 targetPos_;



	tnl::Sequence<ActionRangeAttack> seq_ = tnl::Sequence<ActionRangeAttack>(this, &ActionRangeAttack::seqWaitBefore);




	// 攻撃前の待機シーケンス
	bool seqWaitBefore(const float delta_time);
	// 遠距離攻撃のシーケンス
	bool seqRangeAttack(const float delta_time);
	// 攻撃後の待機シーケンス
	bool seqWaitAfter(const float delta_time);




};