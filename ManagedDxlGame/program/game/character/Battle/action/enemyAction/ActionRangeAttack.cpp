#include "ActionRangeAttack.h"
#include "../../attack/Attack.h"
#include "../../../other/BattleCharacterBase.h"

// コンストラクタ
// 引数：	actionCharacter ... 行動を行うキャラクター,
//			charaList...シーンに存在するキャラクターのリスト
//			waitTimeBefore...攻撃前の待機時間、デフォルトで1.0f
//			waitTimeAfter...攻撃後の待機時間、デフォルトで1.0f
ActionRangeAttack::ActionRangeAttack(const std::shared_ptr<BattleCharacterBase>& actionCharacter,
		const std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>>& charaList,
		float waitTimeBefore, float waitTimeAfter)
	: ActionAttackBase(actionCharacter, charaList)
{
	//// 移動先の座標を決定
	//targetPosDecade();


}

// デストラクタ
ActionRangeAttack::~ActionRangeAttack() {

}


void ActionRangeAttack::update(const float delta_time) {

	// 行動が終了している場合、以下の処理を行わない
	if (BattleActionBase::isFinished_) {
		return;
	}

	// シーケンスの更新
	seq_.update(delta_time);


}


// 行動を実行する前に、数値を初期化するための関数
void ActionRangeAttack::setUpAction() {

	// 行動が終了していない状態に変更
	BattleActionBase::isFinished_ = false;

	MakeAttack();

	SelectTargetCharacter();

	//targetPosDecade();

	// シーケンスを初期状態に戻しておく
	seq_.change(&ActionRangeAttack::seqWaitBefore);
}




// 攻撃対象を選択する関数
// ActionAttackBaseの仮想関数をオーバーライドして使用
void ActionRangeAttack::SelectTargetCharacter() {

	// キャラクターのリストの確認
	auto charaList = charaList_.lock();
	// 行動するキャラクターの確認
	auto actionCharacter = actionCharacter_.lock();

	if (!charaList || !actionCharacter) {
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




// 攻撃前の待機シーケンス
bool ActionRangeAttack::seqWaitBefore(const float delta_time) {

	// **********************************************
	// 待機中の処理が有れば書く
	// *********************************************



	// シーケンスの経過時間が攻撃前の待機時間を超えたとき
	if (seq_.getProgressTime() > waitTimeBefore_) {


		// 目標地点を決定
		targetPos_ = targetCharacter_.lock()->getPos();


		// 遠距離攻撃のシーケンスに移る
		seq_.change(&ActionRangeAttack::seqRangeAttack);

	}

	return true;
}


// 遠距離攻撃のシーケンス
bool ActionRangeAttack::seqRangeAttack(const float delta_time) {


	


	return true;


}


// 攻撃後の待機シーケンス
bool ActionRangeAttack::seqWaitAfter(const float delta_time) {






	return true;

}


