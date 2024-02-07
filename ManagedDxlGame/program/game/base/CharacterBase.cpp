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

}


void CharacterBase::draw() {

}

// 移動を行う関数
// Player, Enemy等の移動を行う際はこの関数を使用する
void CharacterBase::Moving( float delta_time ) {

	// 処理が終了しているにもかかわらず誤って呼び出してしまった際の処理
	if (finishAction_) {
		tnl::DebugTrace("既に処理は終了しています\n");
		return;
	}

	// 移動量に応じて別の方向に移動
	if (moveGrid_ == tnl::Vector2i::up) {
		nowTransform_.setPos_(nowTransform_.getPos_() + tnl::Vector3{ 0, 0, moveVal_ });
	}
	else if (moveGrid_ == tnl::Vector2i::right) {
		nowTransform_.setPos_(nowTransform_.getPos_() + tnl::Vector3{ moveVal_, 0, 0 });
	}
	else if (moveGrid_ == tnl::Vector2i::down) {
		nowTransform_.setPos_(nowTransform_.getPos_() + tnl::Vector3{ 0, 0, -moveVal_ });
	}
	else if (moveGrid_ == tnl::Vector2i::left) {
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

		finishAction_ = true;
	}

}


// 回転を行う関数
// Plauer, Enemy等の回転を行う際はこの関数を使用する
// ※2024/02/08 現在、Enemyでの回転の処理はこれを使用していない
void CharacterBase::Rotating(float delta_time) {

	// 処理が終了しているにもかかわらず誤って呼び出してしまった際の処理
	if (finishAction_) {
		tnl::DebugTrace("既に処理は終了しています\n");
		return;
	}


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

	// 残りの移動量がなくなったとき処理を終了するための処理
	if (std::abs(rotValMax_) < FLT_EPSILON) {

		frontDir_ += nextDir_;

		nextDir_ = Enum::Dir4::UP;

		finishAction_ = true;
	}

}

// 移送先のマスを計算する関数
// 移動する量も計算しているため、移動する際はこれを一度呼び出すこと
tnl::Vector2i CharacterBase::calcMoveGrid(Enum::Dir4 moveDir) {

	// 移動先の座標
	// 戻り値で戻す用
	tnl::Vector2i nextGridPos;

	// 方向に応じて座標を計算
	switch (moveDir) {
	case Enum::Dir4::UP:
		nextGridPos = { gridPos_.x, gridPos_.y - 1 };
		break;

	case Enum::Dir4::LEFT:
		nextGridPos = { gridPos_.x - 1, gridPos_.y };
		break;

	case Enum::Dir4::DOWN:
		nextGridPos = { gridPos_.x, gridPos_.y + 1 };
		break;

	case Enum::Dir4::RIGHT:
		nextGridPos = { gridPos_.x + 1, gridPos_.y };
		break;
	}

	// 次の移動量を計算
	moveGrid_ = nextGridPos - gridPos_;

	return nextGridPos;
}