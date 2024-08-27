#include "Player.h"
#include "../../manager/TurnManager.h"
#include "../../manager/InputManager.h"

// �R���X�g���N�^
// �����FcellSize...1�}�X���̑傫��, startGridPos...�}�b�v��ł̏������W
Player::Player(float gridSize, tnl::Vector2i startGridPos, tnl::Vector3 startPos, std::shared_ptr< TurnManager > turnManager)
	: CharacterBaseDungeon(gridSize, startGridPos), turnManager_(turnManager)
{

	// �����ς̃X�e�[�W�̃C���X�^���X���擾
	stage_ = Stage::GetInstance();


	// ���W��ݒ�
	nowTransform_.setPos_(startPos + tnl::Vector3{0, gridSize_, 0});

	// 1�t���[���̈ړ��ʂ�������
	moveVal_ = gridSize_ / 10;
}


// �f�X�g���N�^
Player::~Player() {

}


void Player::update(float delta_time) {



	if (tnl::Input::IsKeyDown(eKeys::KB_LCONTROL) && tnl::Input::IsKeyDownTrigger(eKeys::KB_Q)) {
		debugMode_ = !debugMode_;
		tnl::DebugTrace("debugMode_ = %d", debugMode_);
	}

	seq_.update(delta_time);

	// �f�o�b�O�p
	//DrawStringEx(900, 100, -1, " nowPos =  %d, %d", gridPos_.x, gridPos_.y);
	//DrawStringEx(900, 200, -1, " nextPos =  %d, %d", nextGridPos_.x, nextGridPos_.y);

	//DrawStringEx(900, 300, -1, " nowPos =  %f, %f, %f", nowTransform_.getPos_().x, nowTransform_.getPos_().y, nowTransform_.getPos_().z);
	//DrawStringEx(900, 400, -1, " nextPos =  %f, %f, %f", nextTransform_.getPos_().x, nextTransform_.getPos_().y, nextTransform_.getPos_().z);

	//DrawStringEx(100, 200, -1, "%d", nowSeq_);
	//DrawStringEx(100, 300, -1, "%d", frontDir_);
}


void Player::ChangeSeqFromWait() {

	// ���̍s�������肵�Ă��鎞�ȊO�ȉ����������Ȃ�
	// 
	if (nowSeq_ != PlayerSeq::WAIT) {
		tnl::DebugTrace("�v���C���[�̃V�[�P���X��؂�ւ��ł��܂���ł���\n");
		return;
	}

	// ���s����V�[�P���X�ɉ����Ď��̃V�[�P���X�ɐ؂�ւ���
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



// ���g���폜����֐�
void Player::Destroy() {

	delete this;

}



// �ҋ@���̃V�[�P���X
// ��{�̃V�[�P���X�ƂȂ�̂ŁA
// ���̃V�[�P���X���I�������炱�̃V�[�P���X�ɖ߂�����
bool Player::seqIdle(const float delta_time) {

	//----------------------------------------------------------------------
	// ���ʂɑO�i���鏈��

	// �O�Ɉړ�����L�[���������Ƃ�
	if ( InputManager::GetInstance()->KeyDownUp() ) {

		// ���Ɉړ�������W���v�Z����
		nextGridPos_ = calcMoveGrid(frontDir_);

		// �ړ�����V�[�P���X�Ɉړ�
		seq_.change(&Player::seqMoveCheck);
		nowSeq_ = PlayerSeq::MOVE_CHECK;
	}


	//----------------------------------------------------------------------
	// ���ʈړ��ȊO�̏���

	// A���������Ƃ�
	else if ( InputManager::GetInstance()->KeyDownLeft() ) {

		// ���ɕ��s�ړ����鏈��
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			// �ړ�������̃}�X�ɐݒ�
			nextGridPos_ = calcMoveGrid(frontDir_ + Enum::eDir4::LEFT);

			// �ړ�����V�[�P���X�Ɉړ�
			seq_.change(&Player::seqMoveCheck);
			nowSeq_ = PlayerSeq::MOVE_CHECK;
		}
		// �������ɉ�]���鏈��
		else {
			// �������������ɉ�
			nextDir_ += Enum::eDir4::LEFT;
			// ��]����V�[�P���X�Ɉړ�
			seq_.change(&Player::seqRotateCheck);

			nowSeq_ = PlayerSeq::ROTATE_CHECK;
		}
	}

	// D���������Ƃ�
	else if (InputManager::GetInstance()->KeyDownRight()) {

		// �E�ɕ��s�ړ����鏈��
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			// �ړ�����E�̃}�X�ɐݒ�
			nextGridPos_ = calcMoveGrid(frontDir_ + Enum::eDir4::RIGHT);

			// �ړ�����V�[�P���X�Ɉړ�
			seq_.change(&Player::seqMoveCheck);
			nowSeq_ = PlayerSeq::MOVE_CHECK;
		}
		// �E�����ɉ�]���鏈��
		else {
			// �����������E�ɉ�
			nextDir_ += Enum::eDir4::RIGHT;
			// ��]����V�[�P���X�Ɉړ�
			seq_.change(&Player::seqRotateCheck);
			nowSeq_ = PlayerSeq::ROTATE_CHECK;
		}
	}

	// S���������Ƃ�
	else if (InputManager::GetInstance()->KeyDownDown()) {

		// ���ɕ��s�ړ����鏈��
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			// �ړ�������̃}�X�ɐݒ�
			nextGridPos_ = calcMoveGrid(frontDir_ + Enum::eDir4::DOWN);

			// �ړ�����V�[�P���X�Ɉړ�
			seq_.change(&Player::seqMoveCheck);
			nowSeq_ = PlayerSeq::MOVE_CHECK;
		}

		else {
			// �����������������ɉ�
			nextDir_ += Enum::eDir4::DOWN;
			// ��]����V�[�P���X�Ɉړ�
			seq_.change(&Player::seqRotateCheck);
			nowSeq_ = PlayerSeq::ROTATE_CHECK;
		}
	}

	return true;
}


// �ړ�����������V�[�P���X
bool Player::seqMoveCheck(const float delta_time) {

	// �ړ��悪�z��O�̏ꍇ�ړ����Ȃ��悤�ɂ��邽�߂̏���
	// -1���������ė����Ƃ��͊m�F�����}�X���z��O�ƂȂ�
	if (stage_->CheckGridPosInt(nextGridPos_) == -1) {
		tnl::DebugTrace("�z��O�̂��߈ړ��ł��܂���\n");
		
		nowSeq_ = PlayerSeq::IDLE;		
		seq_.change(&Player::seqIdle);

		return true;
	}

	// �ړ���̃}�X���ړ��ł��Ȃ��Ƃ�
	if ( !(stage_->CheckGridPosObj(nextGridPos_)->getCanMove()) ) {

		// ���̍��W�����݂̍��W�ɖ߂�
		nextGridPos_ = gridPos_;
		// �V�[�P���X��ҋ@���ɖ߂�
		seq_.change(&Player::seqIdle);
		nowSeq_ = PlayerSeq::IDLE;
		// �������I������
		return true;
	}
	// �ړ��ł���Ƃ�
	else {
		// �ړ���̍��W��ݒ�
		nextTransform_.setPos_( { nextGridPos_.x * gridSize_, gridSize_, -nextGridPos_.y * gridSize_ });

		turnManager_->ChangeSeqFromWaitPlayerInput();


		// �ҋ@���s���V�[�P���X�ɐ؂�ւ�
		seq_.change(&Player::seqWait);

		// �V�[�P���X�̐؂�ւ��𐧌�
		finishAction_ = false;

		// ��Ԃ�ҋ@�ɐ؂�ւ�
		nowSeq_ = PlayerSeq::WAIT;
		// �ҋ@��̍s����Moving�ɐݒ�
		decadedSeq = PlayerSeq::MOVING;

		return true;
	}
	
}

// ��]����������V�[�P���X
bool Player::seqRotateCheck(const float delta_time) {

	// ���̌����ɉ����Ď��̕�����ύX����
	// ��������v���X�Ƃ���
	if (nextDir_ == Enum::eDir4::LEFT) {
		// ��]������ʂ�90�x�ɂ���
		rotValMax_ = -90;
	}
	else if (nextDir_ == Enum::eDir4::DOWN) {
		// ��]������ʂ�180�x�ɂ���
		rotValMax_ = -180;
	}
	else if (nextDir_ == Enum::eDir4::RIGHT) {
		// ��]������ʂ�-90�x�ɂ���
		rotValMax_ = 90;
	}

	// ���̊p�x�����݂̊p�x�����]�ʕ���]������
	nextTransform_.setRot3D_(nextTransform_.getRot3D_() * tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(rotValMax_)));

	// �ҋ@���s���V�[�P���X�ɐ؂�ւ�
	seq_.change(&Player::seqWait);

	// �V�[�P���X�̐؂�ւ��𐧌�
	finishAction_ = false;

	// ���݂̃V�[�P���X��Wait�ɕύX
	nowSeq_ = PlayerSeq::WAIT;
	// �ҋ@��̍s����Rotating�ɐݒ�
	decadedSeq = PlayerSeq::ROTATING;

	return true;
}

// �ҋ@���s���V�[�P���X
// ���̃V�[�P���X����ChangeSeqFromWait�֐������s���邱�ƂŁA
// ���O�Ɋm�F���s�����V�[�P���X(Moving��Rotating)�Ɉړ�����
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

// �ړ����s���V�[�P���X
bool Player::seqMoving(const float delta_time) {

	Moving(delta_time);

	if (finishAction_) {
		turnManager_->ActionEndPlayer();

		seq_.change(&Player::seqIdle);
	}

	return true;
}


// ��]���s���V�[�P���X
bool Player::seqRotating(const float delta_time) {

	Rotating(delta_time);

	if (finishAction_) {

		seq_.change(&Player::seqIdle);
		nowSeq_ = PlayerSeq::IDLE;
	}

	return true;
	
}


