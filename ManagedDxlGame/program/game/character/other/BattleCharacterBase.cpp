#include "BattleCharacterBase.h"

// コンストラクタ
// 引数：startPos...開始位置, objSize...作成するキャラクターの大きさ, objName...名前
// 移動前の座標は開始位置で初期化
BattleCharacterBase::BattleCharacterBase(tnl::Vector3 startPos, float objSize, std::string fileName)
	: beforePos_(startPos), attackSize_(objSize * 1.5), SpriteObjectBase(startPos, objSize, fileName) {

	// SpriteObjectBaseクラスの関数
	// テクスチャを表示する用のplaneの配列を作成する
	CreateSpriteObjArray(fileName);

	// ステータスのクラスを生成
	status_ = std::shared_ptr<StatusCharacter>(new StatusCharacter());

	return;
}

// デストラクタ
BattleCharacterBase::~BattleCharacterBase() {

}

// 更新用の関数
// *********************************************************************
// 継承先のupdate関数でも、このクラスのupdate関数を呼び出すこと!!
// *********************************************************************
// 処理内容
// 1.
void BattleCharacterBase::update(float delta_time) {

	// 状態がActiveでないとき以下の処理を行わない
	if (!isActive_) {
		return;
	}

	SpriteObjectBase::update(delta_time);

	// 攻撃の処理を実行
	auto it = attackList_.begin();
	while (it != attackList_.end()) {
		(*it)->update(delta_time);

		if ((*it)->getIsEnd()) {

			it = attackList_.erase(it);

		}
		else {
			++it;
		}
	}

	// 無敵時間の処理
	// 無敵状態の時以下の処理を行う
	if (!canTakeDamage_) {

		// 無敵時間のカウントを減らす
		invincibleTimeCount_ += delta_time;
		// 点滅カウントを増やす
		invincibleBlinkCount_ += delta_time;

		// 残りの無敵時間が無敵時間の最大値を上回ったとき
		if (invincibleTimeCount_ >= invincibleTimeMax_) {

			// ダメージを受ける状態にする
			canTakeDamage_ = true;

			// 描画する状態にする
			isDisplay_ = true;

			// 無敵の時間をリセット
			invincibleTimeCount_ = 0;

			// 点滅時間のカウントをリセット
			invincibleBlinkCount_ = 0;
		}

		// 点滅時間が間隔を上回ったとき
		if (invincibleBlinkCount_ >= invincibleBlinkInterval_) {

			// 描画状態を入れ替える
			isDisplay_ = !isDisplay_;
			// 点滅時間のカウントをリセット
			invincibleBlinkCount_ = 0;
		}


	}

}


// 描画用の関数
// *********************************************************************
// 継承先のdraw関数でも、このクラスのdraw関数を呼び出すこと!!
// *********************************************************************
// 処理内容
// 1.描画するメッシュの座標を更新
// 2.攻撃のメッシュの描画
void BattleCharacterBase::draw(const std::shared_ptr<dxe::Camera>& camera ) {

	// 状態がActiveでないときには以下の処理を行わない
	if (!isActive_) {
		return;
	}

	if (canTakeDamage_ && !isDisplay_) {
		isDisplay_ = true;
	}

	// 自身を描画
	if (isDisplay_) {
		SpriteObjectBase::draw(camera);
	}

	// 攻撃のメッシュを描画
	auto it = attackList_.begin();
	while (it != attackList_.end()) {

		if( (*it)->getIsActive() ){

			(*it)->draw(camera);

		}

		++it;
	}

	return;

}


// キャラクターを移動させる関数
// 継承先のそれぞれのキャラクタークラスでキャラクターを動かす際にこの関数を用いて動かす
// 
// 引数：moveVector...移動方向, moveVectorMag...移動量の倍率、特定の行動の時のみ移動速度を上げたい場合に使用、デフォルトで1倍
void BattleCharacterBase::MoveCharacter(float delta_time, tnl::Vector3 moveVector, float moveVectorMag) {

	// 現在の座標に対して移動量を加算する処理
	// 移動量は移動方向と移動量（と倍率）をかけ合わせて計算
	transform_.setPos_(transform_.getPos_() + moveVector * moveValue_ * moveVectorMag * delta_time);

	return;
}


// ダメージを受ける関数
// 引数：damage...受けるダメージ
void BattleCharacterBase::TakeDamage(float damage) {

	// 以下の条件の時処理を行わずreturnする
	// １．被ダメージ後の無敵状態のとき
	// ２．体力が0以下のとき
	if (!canTakeDamage_ || status_->getHp() <= 0 ) {
		return;
	}

	// 計算されたダメージ
	// 防御力をダメージから引いた値
	// 計算結果が1以下になったときは1ダメージとする
	float calcDamage = ((damage - status_->getDef() > 1) ? (damage - status_->getDef()) : 1);

	// HPをcalcDamageの値分減らす
	status_->setHp( status_->getHp() - calcDamage );

	// 体力が0未満になったとき0をセットする
	if (status_->getHp() < 0) {
		status_->setHp(0);
	}


	// 無敵状態にする
	canTakeDamage_ = false;

	// 無敵時間のカウントのリセット
	invincibleTimeCount_ = 0;

	// 点滅時間のリセット
	invincibleBlinkCount_ = 0;
}