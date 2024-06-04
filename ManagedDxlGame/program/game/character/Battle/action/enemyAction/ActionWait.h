#pragma once
#include "../../../../../dxlib_ext/dxlib_ext.h"
#include "../BattleActionBase.h"
#include "../../../other/BattleCharacterBase.h"

// 移動の行動のクラス
// 移動のみの行動を行う場合に使用する
// ランダムな位置を決定し、移動させる
class ActionWait final : public BattleActionBase {
public:

	// コンストラクタ
	// 引数：	actionCharacter ... 行動を行うキャラクター
	ActionWait(std::shared_ptr < BattleCharacterBase > actionCharacter);

	// デストラクタ
	~ActionWait();

	// 行動を実行するupdate関数
	void update(const float delta_time);


	// 行動を実行する前に、数値を初期化するための関数
	void setUpAction() override;


	//// 待機する時間を決定する関数
	//void waitTimeDecade();

private:


	// 待機する時間の最大値
	float waitTimeMax_;

	// 待機する時間の最小値
	float waitTimeMin_;

	// 待機する時間
	float waitTime_;

	// 待機し始めてから経過した時間
	float waitCount_;

};