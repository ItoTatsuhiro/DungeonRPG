#include "ActionMeleeAttack.h"


// 攻撃のクラスを生成する処理をコンストラクタなんかに書く！
// かくかくかくかくかくかくかくかくかくかく！！！！！！！！！！！！！！！



// コンストラクタ
// 引数：	actionCharacter ... 行動を行うキャラクター, targetCharacter ... 攻撃対象のキャラクター
ActionMeleeAttack::ActionMeleeAttack(std::shared_ptr < BattleCharacterBase > actionCharacter, std::shared_ptr < BattleCharacterBase > targetCharacter)
	: ActionAttackBase(actionCharacter, targetCharacter), moveRangeMax_(150), moveRangeMin_(moveRangeMax_ / 2), attackRange_(30)
{
	// 移動先の座標を決定
	targetPosDecade();

}

// デストラクタ
ActionMeleeAttack::~ActionMeleeAttack() {

}


void ActionMeleeAttack::update(const float delta_time) {

	// 行動が終了している場合、以下の処理を行わない
	if (BattleActionBase::isFinished_) {
		return;
	}

	
	// ベースクラスの更新
	ActionAttackBase::update(delta_time);

	// シーケンスの更新
	seq_.update(delta_time);


}


// 行動を実行する前に、数値を初期化するための関数
void ActionMeleeAttack::setUpAction() {

	// 行動が終了していない状態に変更
	BattleActionBase::isFinished_ = false;

	targetPosDecade();

}

// 移動に関する初期設定を行う関数
void ActionMeleeAttack::targetPosDecade() {

	// 移動量を取得
	moveValue_ = actionCharacter_->getMoveValue();

	// 移動した距離を0にする
	movedValueCount_ = 0;



	// 移動の角度と距離を計算
	float angle = rand() % 360;
	float distance = rand() % static_cast<int>(moveRangeMax_);



	// 角度と距離から座標を計算
	targetPos_.x = actionCharacter_->getPos().x + distance * cos(angle);
	targetPos_.z = actionCharacter_->getPos().z + distance * sin(angle);

	// 移動する距離を計算
	totalMoveValue_ = (targetPos_ - actionCharacter_->getPos()).length();


	// 移動する方向を計算
	// （移動先の座標 - 現在の座標）を正規化
	moveVectorNor_ = tnl::Vector3::Normalize(targetPos_ - (actionCharacter_->getPos()));

	// 移動量を計算
	moveVector_ = moveVectorNor_ * moveValue_;

}


// 移動処理後に現在の位置を確認する処理
void ActionMeleeAttack::CheckPosition() {


	// 攻撃範囲内に入っているときは攻撃のシーケンスに切り替える
	if ((actionCharacter_->getPos() - targetPos_).length() <= attackRange_) {

		seq_.change(&ActionMeleeAttack::seqMeleeAttack);
	}

}


// 攻撃の方向を決定する関数
void ActionMeleeAttack::AttackDirectionDecade() {


	tnl::Vector3 toTargetVector = targetPos_ - actionCharacter_->getPos();



}



// 近寄ってくる際のシーケンス
bool ActionMeleeAttack::seqComing( const float delta_time ) {

	// 移動先の座標をセット
	targetPos_ = targetCharacter_->getPos();

	// 移動方向を計算
	moveVectorNor_ = tnl::Vector3::Normalize(targetPos_ - (actionCharacter_->getPos()));;

	// キャラクターを移動させる
	actionCharacter_->MoveCharacter(moveVectorNor_, moveVectorMag_);

	// 座標を確認
	CheckPosition();

	return true;
}


// 近接攻撃を行うシーケンス
bool ActionMeleeAttack::seqMeleeAttack(const float delta_time) {

	
	


}
