#include "ActionWait.h"
#include "../BattleActionBase.h"



// コンストラクタ
// 引数：	actionCharacter ... 行動を行うキャラクター
ActionWait::ActionWait(std::shared_ptr < BattleCharacterBase > actionCharacter) 
	: BattleActionBase(actionCharacter), waitTimeMax_(3), waitTimeMin_(waitTimeMax_ / 2)
{
	setUpAction();
}

// デストラクタ
ActionWait::~ActionWait() {

}

// 行動を実行するupdate関数
void ActionWait::update(const float delta_time) {

	// 経過時間を加算
	waitCount_ += delta_time;

	// 経過時間がランダムに決定した待機時間を超えたとき
	if (waitCount_ >= waitTime_) {

		// 行動が終了しているかのフラグをtrueにする
		BattleActionBase::isFinished_ = true;

	}
}


// 行動を実行する前に、数値を初期化するための関数
void ActionWait::setUpAction() {

	// 待機時間の決定
	float waitTimeRange = waitTimeMax_ - waitTimeMin_;
	float randTime = (rand() % static_cast<int>(waitTimeRange));
	waitTime_ = waitTimeMin_ + randTime;

	// 経過時間をリセット
	waitCount_ = 0;


	auto actionCharacter = actionCharacter_.lock();

	if (actionCharacter == nullptr) {
		return;
	}

	// 状態を待機状態にする
	actionCharacter->setNowSituation(BattleCharacterBase::Situation::WAITING);

}


