#include "ActionMove.h"

// コンストラクタ
// 引数：	actionCharacter ... 行動を行うキャラクター
ActionMove::ActionMove(std::shared_ptr < BattleCharacterBase > actionCharacter)
	: BattleActionBase(actionCharacter), moveRangeMax_(150), moveRangeMin_(moveRangeMax_ / 2)
{
	// 移動先の座標を決定
	targetPosDecade();



}

// デストラクタ
ActionMove::~ActionMove() {

}


void ActionMove::update(const float delta_time) {

	// 行動が終了している場合、以下の処理を行わない
	if (BattleActionBase::isFinished_) {
		return;
	}

	auto actionCharacter = actionCharacter_.lock();

	if (actionCharacter == nullptr) {
		return;
	}


	// 移動量分移動の処理を行う
	actionCharacter->MoveCharacter(delta_time, moveVectorNor_);

	// 移動した距離をカウント
	movedValueCount_ += actionCharacter->getMoveValue() * delta_time;


	// 距離を移動し切ったとき行動を終了させる
	if (movedValueCount_ >= totalMoveValue_) {

		// キャラクターの座標を目標地点の座標に補正
		actionCharacter->setPos(targetPos_);

		movedValueCount_ = 0;

		// 行動が終了しているかのフラグをtrueにする
		BattleActionBase::isFinished_ = true;

		return;
	}
}


// 行動を実行する前に、数値を初期化するための関数
void ActionMove::setUpAction() {

	// 行動が終了していない状態に変更
	BattleActionBase::isFinished_ = false;

	targetPosDecade();


	auto actionCharacter = actionCharacter_.lock();

	if (actionCharacter == nullptr) {
		return;
	}
	// 移動状態をセット
	actionCharacter->setNowSituation(BattleCharacterBase::Situation::MOVING);
}

// 移動に関する初期設定を行う関数
void ActionMove::targetPosDecade() {

	auto actionCharacter = actionCharacter_.lock();

	if (actionCharacter == nullptr) {
		return;
	}


	// 移動量を取得
	moveValue_ = actionCharacter->getMoveValue();

	// 移動した距離を0にする
	movedValueCount_ = 0;

	// 移動の角度と距離を計算
	float angle = rand() % 360;
	float distance = rand() % static_cast<int>(moveRangeMax_);


	// 角度と距離から座標を計算
	targetPos_.x = actionCharacter->getPos().x + distance * cos(angle);
	targetPos_.z = actionCharacter->getPos().z + distance * sin(angle);

	// 移動する距離を計算
	totalMoveValue_ = (targetPos_ - actionCharacter->getPos()).length();


	// 移動する方向を計算
	// （移動先の座標 - 現在の座標）を正規化
	moveVectorNor_ = tnl::Vector3::Normalize(targetPos_ - (actionCharacter->getPos()));

	// 移動量を計算
	moveVector_ = moveVectorNor_ * moveValue_;
}
