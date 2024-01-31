#include "Player.h"

// コンストラクタ
// 引数：cellSize...1マス分の大きさ, startGridPos...マップ上での初期座標
Player::Player(float gridSize, tnl::Vector2i startGridPos) : CharacterBase(gridSize, startGridPos) {

	// 生成済のステージのインスタンスを取得
	stage_ = Stage::GetInstance();

	// 座標を設定
	nowTransform_.setPos_(tnl::Vector3(gridPos_.x, 1, gridPos_.y) * gridSize_);

	// 1フレームの移動量を初期化
	moveVal_ = gridSize_ / 10;
}


// デストラクタ
//
Player::~Player() {

}


void Player::update(float delta_time) {

	seq_.update(delta_time);

	DrawStringEx(900, 100, -1, " nowPos =  %d, %d", gridPos_.x, gridPos_.y);
	DrawStringEx(900, 200, -1, " nextPos =  %d, %d", nextGridPos_.x, nextGridPos_.y);

	DrawStringEx(900, 300, -1, " nowPos =  %f, %f, %f", nowTransform_.getPos_().x, nowTransform_.getPos_().y, nowTransform_.getPos_().z);
	DrawStringEx(900, 400, -1, " nextPos =  %f, %f, %f", nextTransform_.getPos_().x, nextTransform_.getPos_().y, nextTransform_.getPos_().z);

	DrawStringEx(100, 200, -1, "%s", seqNow_.c_str());
	DrawStringEx(100, 300, -1, "%d", frontDir_);
}


// 待機中のシーケンス
// 基本のシーケンスとなるので、
// 他のシーケンスが終了したらこのシーケンスに戻すこと
bool Player::seqIdle(const float delta_time) {

	//----------------------------------------------------------------------
	// 正面に前進する処理

	// Wを押したとき
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {

		// 次に移動する座標を計算する
		nextGridPos_ = calcMoveGrid(frontDir_);

		// 移動するシーケンスに移動
		seq_.change(&Player::seqMoveCheck);
		seqNow_ = " seqMoveCheck ";
	}


	//----------------------------------------------------------------------
	// 正面移動以外の処理

	// Aを押したとき
	else if (tnl::Input::IsKeyDown(eKeys::KB_A)) {

		// 左に平行移動する処理
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			// 移動先を左のマスに設定
			nextGridPos_ = calcMoveGrid(frontDir_ + Enum::Dir4::LEFT);

			// 移動するシーケンスに移動
			seq_.change(&Player::seqMoveCheck);
			seqNow_ = " seqMoveCheck ";
		}
		// 左向きに回転する処理
		else {
			// 向く方向を左に回す
			nextDir_ += Enum::Dir4::LEFT;
			// 回転するシーケンスに移動
			seq_.change(&Player::seqRotateCheck);

			seqNow_ = " seqRotCheck ";
		}
	}

	// Dを押したとき
	else if (tnl::Input::IsKeyDown(eKeys::KB_D)) {

		// 右に平行移動する処理
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			// 移動先を右のマスに設定
			nextGridPos_ = calcMoveGrid(frontDir_ + Enum::Dir4::RIGHT);

			// 移動するシーケンスに移動
			seq_.change(&Player::seqMoveCheck);
			seqNow_ = " seqMoveCheck ";
		}
		// 右向きに回転する処理
		else {
			// 向く方向を右に回す
			nextDir_ += Enum::Dir4::RIGHT;
			// 回転するシーケンスに移動
			seq_.change(&Player::seqRotateCheck);

			seqNow_ = " seqRotCheck ";
		}
	}

	// Sを押したとき
	else if (tnl::Input::IsKeyDown(eKeys::KB_S)) {

		// 後ろに平行移動する処理
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			// 移動先を後ろのマスに設定
			nextGridPos_ = calcMoveGrid(frontDir_ + Enum::Dir4::DOWN);

			// 移動するシーケンスに移動
			seq_.change(&Player::seqMoveCheck);
			seqNow_ = " seqMoveCheck ";
		}

		else {
			// 向く方向を後ろ向きに回す
			nextDir_ += Enum::Dir4::DOWN;
			// 回転するシーケンスに移動
			seq_.change(&Player::seqRotateCheck);

			seqNow_ = " seqRotCheck ";
		}
	}

	return true;
}


// 移動を準備するシーケンス
bool Player::seqMoveCheck(const float delta_time) {

	// 移動先が配列外の場合移動しないようにするための処理
	if (stage_->CheckGridPosInt(nextGridPos_) == -1) {
		tnl::DebugTrace("配列外のため移動できません\n");
		
		seqNow_ = "seqIdle";
		
		seq_.change(&Player::seqIdle);

		return true;
	}

	// 移動先のマスが移動できないとき
	if ( !(stage_->CheckGridPosObj(nextGridPos_)->getCanMove()) ) {

		// 次の座標を現在の座標に戻す
		nextGridPos_ = gridPos_;
		// シーケンスを待機中に戻す
		seq_.change(&Player::seqIdle);

		seqNow_ = " seqIdle ";
		// 処理を終了する
		return true;
	}
	// 移動できるとき
	else {
		// 移動先の座標を設定
		nextTransform_.setPos_( { nextGridPos_.x * gridSize_, gridSize_, -nextGridPos_.y * gridSize_ });

		// 動作を行うシーケンスに切り替え
		seq_.change(&Player::seqMoving);

		// シーケンスの切り替えを制限
		canChengeSeq_ = false;

		seqNow_ = " seqMoving ";

		return true;
	}
	
}

// 回転を準備するシーケンス
bool Player::seqRotateCheck(const float delta_time) {

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
	seq_.change(&Player::seqRotating);

	// シーケンスの切り替えを制限
	canChengeSeq_ = false;

	seqNow_ = " seqRotating ";

	return true;
}

// 移動を行うシーケンス
bool Player::seqMoving(const float delta_time) {

	Moving(delta_time);

	if (canChengeSeq_) {
		seq_.change(&Player::seqIdle);
	}

	return true;
}


// 回転を行うシーケンス
bool Player::seqRotating(const float delta_time) {

	Rotating(delta_time);

	if (canChengeSeq_) {

		seq_.change(&Player::seqIdle);
		seqNow_ = " seqIdle ";

	}

	return true;
	
}


