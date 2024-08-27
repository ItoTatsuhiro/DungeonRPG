#include "ActionMeleeAttack.h"
#include "../../attack/Attack.h"

// コンストラクタ
// 引数：	actionCharacter ... 行動を行うキャラクター, targetCharacter ... 攻撃対象のキャラクター
ActionMeleeAttack::ActionMeleeAttack(const std::shared_ptr<BattleCharacterBase>& actionCharacter, const std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>>& charaList)
	: ActionAttackBase(actionCharacter, charaList), moveRangeMax_(150), moveRangeMin_(moveRangeMax_ / 2), attackRange_(30), moveVectorMag_(1.0)
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

	// シーケンスの更新
	seq_.update(delta_time);


}


// 行動を実行する前に、数値を初期化するための関数
void ActionMeleeAttack::setUpAction() {

	// 行動が終了していない状態に変更
	BattleActionBase::isFinished_ = false;
	
	MakeAttack("attackEffect.png");

	SelectTargetCharacter();

	targetPosDecade();

	// シーケンスを初期状態に戻しておく
	seq_.change(&ActionMeleeAttack::seqComing);
}


// 移動に関する初期設定を行う関数
void ActionMeleeAttack::targetPosDecade() {


	auto actionCharacter = actionCharacter_.lock();

	if ( !actionCharacter ) {
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




// 攻撃対象を選択する関数
// ActionAttackBaseの仮想関数をオーバーライドして使用
void ActionMeleeAttack::SelectTargetCharacter() {

	// キャラクターのリストの確認
	auto charaList = charaList_.lock();
	// 行動するキャラクターの確認
	auto actionCharacter = actionCharacter_.lock();

	if ( !charaList || !actionCharacter ) {
		return;
	}



	auto it = charaList->begin();

	while (it != charaList->end()) {

		// 自身と異なる種類のキャラクターを見つけたとき対象のキャラクターとする
		// ※プレイヤーキャラクターは現状1キャラの予定のため、見つけたらそれを攻撃対象とする
		if ((*it)->getCharacterType() != actionCharacter->getCharacterType()) {

			targetCharacter_ = (*it);

			break;
		}

		++it;
	}

	return;

}




//----------------------------------------------------------------------------------------------------
// private

// 移動処理後に現在の位置を確認する処理
void ActionMeleeAttack::CheckPosition() {

	auto actionCharacter = actionCharacter_.lock();

	if (actionCharacter == nullptr) {
		return;
	}


	// 攻撃範囲内に入っているときは攻撃のシーケンスに切り替える
	if ((actionCharacter->getPos() - targetPos_).length() <= attackRange_) {

		seq_.change(&ActionMeleeAttack::seqMeleeAttack);
	}

}


// 攻撃の方向を決定する関数
void ActionMeleeAttack::SetAttackDetail() {

	auto actionCharacter = actionCharacter_.lock();

	auto attack = attack_.lock();

	if (!actionCharacter || !attack) {
		return;
	}


	//--------------------------------------------------------------------------------
	// 攻撃方向を決定

	// ターゲットへの方向を確認
	tnl::Vector3 toTargetVector = tnl::Vector3::Normalize(targetPos_ - actionCharacter->getPos());


	//--------------------------------------------------------------------------------
	// 座標の計算、セット

	// 攻撃のメッシュの座標を計算
	tnl::Vector3 attackPos = actionCharacter->getPos() + toTargetVector * attack->getMeshSize();
	// 攻撃のメッシュの座標をセット
	attack->setPos(attackPos);
	// 状態をアクティブにセット
	attack->setIsActive(true);
}






// 近寄ってくる際のシーケンス
bool ActionMeleeAttack::seqComing( const float delta_time ) {

	auto actionCharacter = actionCharacter_.lock();

	auto targetCharacter = targetCharacter_.lock();

	if ( !actionCharacter || !targetCharacter ) {
		return true;
	}


	// 移動先の座標をセット
	targetPos_ = targetCharacter->getPos();

	// 移動方向を計算
	moveVectorNor_ = tnl::Vector3::Normalize(targetPos_ - (actionCharacter->getPos()) );

	// キャラクターを移動させる
	actionCharacter->MoveCharacter(delta_time, moveVectorNor_, moveVectorMag_);

	// 座標を確認
	// 攻撃範囲内に入っているときは攻撃のシーケンスに切り替える
	if ((actionCharacter->getPos() - targetPos_).length() <= attackRange_) {

		SetAttackDetail();

		seq_.change(&ActionMeleeAttack::seqMeleeAttack);
	}

	return true;
}


// 近接攻撃を行うシーケンス
bool ActionMeleeAttack::seqMeleeAttack(const float delta_time) {


	// ベースクラスの更新
	// ベースクラスでは攻撃のメッシュの更新のみ行っているので、
	// 攻撃の処理を更新するこのシーケンスで更新を行う
	ActionAttackBase::update(delta_time);


	auto attack = attack_.lock();

	if (!attack->getIsActive()) {

		seq_.change(&ActionMeleeAttack::seqComing);

		// 行動を終了している状態にする
		// （敵キャラクターのクラスで、実行する行動を切り替えるため）
		isFinished_ = true;

		return true;
	}


	// 攻撃の処理が終了している際は処理を終了させる
	if (attack->getIsEnd()) {
		seq_.change(&ActionMeleeAttack::seqComing);

		// 行動を終了している状態にする
		// （敵キャラクターのクラスで、実行する行動を切り替えるため）
		isFinished_ = true;
	}


	return true;
}

