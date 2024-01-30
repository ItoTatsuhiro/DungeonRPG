#include "CharacterBase.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include "../map/Stage.h"


CharacterBase::CharacterBase(float gridSize, tnl::Vector2i startPos) : EntityBase(startPos, gridSize) {

	// 生成済のステージのインスタンスを取得
	stage_ = Stage::GetInstance();

	// 座標を設定
	nowTransform_.setPos_(tnl::Vector3(gridPos_.x, 1, gridPos_.y) * gridSize_);

	// 1フレームの移動量を初期化
	moveVal_ = gridSize_ / 10;

}


CharacterBase::~CharacterBase() {

}


void CharacterBase::update(float delta_time) {

	seq_.update(delta_time);

}


void CharacterBase::draw() {

}

// 待機中のシーケンス
// 基本のシーケンスとなるので、他のシーケンスが終了したらこのシーケンスに戻す
// ※継承先でそれぞれオーバーライドして使用すること
bool CharacterBase::seqIdle(const float delta_time) {

	return true;
}


// 移動を準備するシーケンス
bool CharacterBase::seqMoveCheck(const float delta_time) {

	// 移動先が配列外の場合移動しないようにするための処理
	if (stage_->CheckGridPosInt(nextGridPos_) == -1) {
		tnl::DebugTrace("配列外のため移動できません\n");

		// seqNow_ = "seqIdle";

		seq_.change(&CharacterBase::seqIdle);

		return true;
	}

	// 移動先のマスが移動できないとき
	if (!(stage_->CheckGridPosObj(nextGridPos_)->getCanMove())) {

		// 次の座標を現在の座標に戻す
		nextGridPos_ = gridPos_;
		// シーケンスを待機中に戻す
		seq_.change(&CharacterBase::seqIdle);

		// seqNow_ = " seqIdle ";
		// 処理を終了する
		return true;
	}
	// 移動できるとき
	else {

		nextTransform_.setPos_({ nextGridPos_.x * gridSize_, gridSize_, -nextGridPos_.y * gridSize_ });

		// 動作を行うシーケンスに切り替え
		seq_.change(&CharacterBase::seqMoving);

		// seqNow_ = " seqMoving ";

		return true;
	}

}

// 回転を準備するシーケンス
bool CharacterBase::seqRotateCheck(const float delta_time) {

	// 次の向きに応じて次の方向を変更する
	// 左周りをプラスとする
	if (nextDir_ == Enum::Dir4::LEFT) {
		// 回転させる量を90度にする
		rotValMax_ = -90;
	}
	else if (nextDir_ == Enum::Dir4::DOWN) {
		// 回転させる量を180度にする
		rotValMax_ = -180;
	}
	else if (nextDir_ == Enum::Dir4::RIGHT) {
		// 回転させる量を-90度にする
		rotValMax_ = 90;
	}

	// 次の角度を現在の角度から回転量分回転させる
	nextTransform_.setRot3D_(nextTransform_.getRot3D_() * tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(rotValMax_)));

	// 回転を行うシーケンスに切り替え
	seq_.change(&CharacterBase::seqRotating);

	// seqNow_ = " seqRotating ";

	return true;
}

// 移動を行うシーケンス
bool CharacterBase::seqMoving(const float delta_time) {

	// 移動量に応じて別の方向に移動
	if (moveGrid_ == tnl::Vector2i{ 0, -1 }) {
		nowTransform_.setPos_(nowTransform_.getPos_() + tnl::Vector3{ 0, 0, moveVal_ });
	}
	else if (moveGrid_ == tnl::Vector2i{ 1, 0 }) {
		nowTransform_.setPos_(nowTransform_.getPos_() + tnl::Vector3{ moveVal_, 0, 0 });
	}
	else if (moveGrid_ == tnl::Vector2i{ 0, 1 }) {
		nowTransform_.setPos_(nowTransform_.getPos_() + tnl::Vector3{ 0, 0, -moveVal_ });
	}
	else if (moveGrid_ == tnl::Vector2i{ -1, 0 }) {
		nowTransform_.setPos_(nowTransform_.getPos_() + tnl::Vector3{ -moveVal_, 0, 0 });
	}


	// 移動先の座標と現在の座標の差が十分に小さい時(移動しきったとき)
	if ((nextTransform_.getPos_() - nowTransform_.getPos_()).length() < FLT_EPSILON) {

		// 現在の座標を移動先の座標に合わせる
		nowTransform_.setPos_(nextTransform_.getPos_());
		// 現在のマス目を更新
		gridPos_ = nextGridPos_;
		// 移動する量をリセット
		moveGrid_ = tnl::Vector2i{ 0, 0 };

		// 待機中のシーケンスに切り替え
		seq_.change(&CharacterBase::seqIdle);

		// seqNow_ = " seqIdle ";

		return true;
	}


}

// 回転を行うシーケンス
bool CharacterBase::seqRotating(const float delta_time) {

	if (rotValMax_ > 0) {

		// 回転量分回す
		nowTransform_.setRot3D_(nowTransform_.getRot3D_() * tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(rotValFrame_)));
		// 回した分、残りの回転量から引く
		rotValMax_ -= rotValFrame_;

		// 回りすぎたとき
		if (rotValMax_ < 0) {
			// 回りすぎた分を戻す
			nowTransform_.setRot3D_(nextTransform_.getRot3D_());

			rotValMax_ = 0;
		}

	}
	else if (rotValMax_ < 0) {

		// 回転量分回す
		nowTransform_.setRot3D_(nowTransform_.getRot3D_() * tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(-rotValFrame_)));
		// 回した分残りの回転量に加算する
		// (回転量がマイナスからのスタートのため)
		rotValMax_ += rotValFrame_;
		// 回りすぎた時
		if (rotValMax_ > 0) {
			// 回りすぎた分を戻す
			nowTransform_.setRot3D_(nextTransform_.getRot3D_());

			rotValMax_ = 0;
		}

	}

	if (std::abs(rotValMax_) < FLT_EPSILON) {

		frontDir_ += nextDir_;

		nextDir_ = Enum::Dir4::UP;

		seq_.change(&CharacterBase::seqIdle);

		// seqNow_ = " seqIdle ";

		return true;
	}

}