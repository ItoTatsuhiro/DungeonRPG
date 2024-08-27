#include "Player.h"
#include "../../manager/TurnManager.h"
#include "../../manager/InputManager.h"

// コンストラクタ
// 引数：cellSize...1マス分の大きさ, startGridPos...マップ上での初期座標
Player::Player(float gridSize, tnl::Vector2i startGridPos, tnl::Vector3 startPos, std::shared_ptr< TurnManager > turnManager)
	: CharacterBaseDungeon(gridSize, startGridPos), turnManager_(turnManager)
{

	// 生成済のステージのインスタンスを取得
	stage_ = Stage::GetInstance();


	// 座標を設定
	nowTransform_.setPos_(startPos + tnl::Vector3{0, gridSize_, 0});

	// 1フレームの移動量を初期化
	moveVal_ = gridSize_ / 10;
}


// デストラクタ
Player::~Player() {

}


void Player::update(float delta_time) {



	if (tnl::Input::IsKeyDown(eKeys::KB_LCONTROL) && tnl::Input::IsKeyDownTrigger(eKeys::KB_Q)) {
		debugMode_ = !debugMode_;
		tnl::DebugTrace("debugMode_ = %d", debugMode_);
	}

	seq_.update(delta_time);

	// デバッグ用
	//DrawStringEx(900, 100, -1, " nowPos =  %d, %d", gridPos_.x, gridPos_.y);
	//DrawStringEx(900, 200, -1, " nextPos =  %d, %d", nextGridPos_.x, nextGridPos_.y);

	//DrawStringEx(900, 300, -1, " nowPos =  %f, %f, %f", nowTransform_.getPos_().x, nowTransform_.getPos_().y, nowTransform_.getPos_().z);
	//DrawStringEx(900, 400, -1, " nextPos =  %f, %f, %f", nextTransform_.getPos_().x, nextTransform_.getPos_().y, nextTransform_.getPos_().z);

	//DrawStringEx(100, 200, -1, "%d", nowSeq_);
	//DrawStringEx(100, 300, -1, "%d", frontDir_);
}


void Player::ChangeSeqFromWait() {

	// 次の行動が決定している時以外以下を処理しない
	// 
	if (nowSeq_ != PlayerSeq::WAIT) {
		tnl::DebugTrace("プレイヤーのシーケンスを切り替えできませんでした\n");
		return;
	}

	// 実行するシーケンスに応じて次のシーケンスに切り替える
	switch (decadedSeq) {
	case PlayerSeq::MOVING :

		seq_.change(&Player::seqMoving);
		nowSeq_ = PlayerSeq::MOVING;

		decadedSeq = PlayerSeq::WAIT;

		break;

	case PlayerSeq::ROTATING :

		seq_.change(&Player::seqRotating);
		nowSeq_ = PlayerSeq::ROTATING;

		decadedSeq = PlayerSeq::WAIT;

		break;

	}


}



// 自身を削除する関数
void Player::Destroy() {

	delete this;

}



// 待機中のシーケンス
// 基本のシーケンスとなるので、
// 他のシーケンスが終了したらこのシーケンスに戻すこと
bool Player::seqIdle(const float delta_time) {

	//----------------------------------------------------------------------
	// 正面に前進する処理

	// 前に移動するキーを押したとき
	if ( InputManager::GetInstance()->KeyDownUp() ) {

		// 次に移動する座標を計算する
		nextGridPos_ = calcMoveGrid(frontDir_);

		// 移動するシーケンスに移動
		seq_.change(&Player::seqMoveCheck);
		nowSeq_ = PlayerSeq::MOVE_CHECK;
	}


	//----------------------------------------------------------------------
	// 正面移動以外の処理

	// Aを押したとき
	else if ( InputManager::GetInstance()->KeyDownLeft() ) {

		// 左に平行移動する処理
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			// 移動先を左のマスに設定
			nextGridPos_ = calcMoveGrid(frontDir_ + Enum::eDir4::LEFT);

			// 移動するシーケンスに移動
			seq_.change(&Player::seqMoveCheck);
			nowSeq_ = PlayerSeq::MOVE_CHECK;
		}
		// 左向きに回転する処理
		else {
			// 向く方向を左に回す
			nextDir_ += Enum::eDir4::LEFT;
			// 回転するシーケンスに移動
			seq_.change(&Player::seqRotateCheck);

			nowSeq_ = PlayerSeq::ROTATE_CHECK;
		}
	}

	// Dを押したとき
	else if (InputManager::GetInstance()->KeyDownRight()) {

		// 右に平行移動する処理
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			// 移動先を右のマスに設定
			nextGridPos_ = calcMoveGrid(frontDir_ + Enum::eDir4::RIGHT);

			// 移動するシーケンスに移動
			seq_.change(&Player::seqMoveCheck);
			nowSeq_ = PlayerSeq::MOVE_CHECK;
		}
		// 右向きに回転する処理
		else {
			// 向く方向を右に回す
			nextDir_ += Enum::eDir4::RIGHT;
			// 回転するシーケンスに移動
			seq_.change(&Player::seqRotateCheck);
			nowSeq_ = PlayerSeq::ROTATE_CHECK;
		}
	}

	// Sを押したとき
	else if (InputManager::GetInstance()->KeyDownDown()) {

		// 後ろに平行移動する処理
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			// 移動先を後ろのマスに設定
			nextGridPos_ = calcMoveGrid(frontDir_ + Enum::eDir4::DOWN);

			// 移動するシーケンスに移動
			seq_.change(&Player::seqMoveCheck);
			nowSeq_ = PlayerSeq::MOVE_CHECK;
		}

		else {
			// 向く方向を後ろ向きに回す
			nextDir_ += Enum::eDir4::DOWN;
			// 回転するシーケンスに移動
			seq_.change(&Player::seqRotateCheck);
			nowSeq_ = PlayerSeq::ROTATE_CHECK;
		}
	}

	return true;
}


// 移動を準備するシーケンス
bool Player::seqMoveCheck(const float delta_time) {

	// 移動先が配列外の場合移動しないようにするための処理
	// -1がかえって来たときは確認したマスが配列外となる
	if (stage_->CheckGridPosInt(nextGridPos_) == -1) {
		tnl::DebugTrace("配列外のため移動できません\n");
		
		nowSeq_ = PlayerSeq::IDLE;		
		seq_.change(&Player::seqIdle);

		return true;
	}

	// 移動先のマスが移動できないとき
	if ( !(stage_->CheckGridPosObj(nextGridPos_)->getCanMove()) ) {

		// 次の座標を現在の座標に戻す
		nextGridPos_ = gridPos_;
		// シーケンスを待機中に戻す
		seq_.change(&Player::seqIdle);
		nowSeq_ = PlayerSeq::IDLE;
		// 処理を終了する
		return true;
	}
	// 移動できるとき
	else {
		// 移動先の座標を設定
		nextTransform_.setPos_( { nextGridPos_.x * gridSize_, gridSize_, -nextGridPos_.y * gridSize_ });

		turnManager_->ChangeSeqFromWaitPlayerInput();


		// 待機を行うシーケンスに切り替え
		seq_.change(&Player::seqWait);

		// シーケンスの切り替えを制限
		finishAction_ = false;

		// 状態を待機に切り替え
		nowSeq_ = PlayerSeq::WAIT;
		// 待機後の行動をMovingに設定
		decadedSeq = PlayerSeq::MOVING;

		return true;
	}
	
}

// 回転を準備するシーケンス
bool Player::seqRotateCheck(const float delta_time) {

	// 次の向きに応じて次の方向を変更する
	// 左周りをプラスとする
	if (nextDir_ == Enum::eDir4::LEFT) {
		// 回転させる量を90度にする
		rotValMax_ = -90;
	}
	else if (nextDir_ == Enum::eDir4::DOWN) {
		// 回転させる量を180度にする
		rotValMax_ = -180;
	}
	else if (nextDir_ == Enum::eDir4::RIGHT) {
		// 回転させる量を-90度にする
		rotValMax_ = 90;
	}

	// 次の角度を現在の角度から回転量分回転させる
	nextTransform_.setRot3D_(nextTransform_.getRot3D_() * tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(rotValMax_)));

	// 待機を行うシーケンスに切り替え
	seq_.change(&Player::seqWait);

	// シーケンスの切り替えを制限
	finishAction_ = false;

	// 現在のシーケンスをWaitに変更
	nowSeq_ = PlayerSeq::WAIT;
	// 待機後の行動をRotatingに設定
	decadedSeq = PlayerSeq::ROTATING;

	return true;
}

// 待機を行うシーケンス
// このシーケンス中にChangeSeqFromWait関数を実行することで、
// 事前に確認を行ったシーケンス(MovingかRotating)に移動する
bool Player::seqWait(const float delta_time) {

	if (nowSeq_ != PlayerSeq::WAIT) { nowSeq_ = PlayerSeq::WAIT; }

	if (decadedSeq == PlayerSeq::ROTATING) {
		seq_.change(&Player::seqRotating);
	}

	if (debugMode_) {
		ChangeSeqFromWait();
	}

	return true;
}

// 移動を行うシーケンス
bool Player::seqMoving(const float delta_time) {

	Moving(delta_time);

	if (finishAction_) {
		turnManager_->ActionEndPlayer();

		seq_.change(&Player::seqIdle);
	}

	return true;
}


// 回転を行うシーケンス
bool Player::seqRotating(const float delta_time) {

	Rotating(delta_time);

	if (finishAction_) {

		seq_.change(&Player::seqIdle);
		nowSeq_ = PlayerSeq::IDLE;
	}

	return true;
	
}


