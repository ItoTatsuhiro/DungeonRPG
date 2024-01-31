#include "Player.h"

// �R���X�g���N�^
// �����FcellSize...1�}�X���̑傫��, startGridPos...�}�b�v��ł̏������W
Player::Player(float gridSize, tnl::Vector2i startGridPos) : CharacterBase(gridSize, startGridPos) {

	// �����ς̃X�e�[�W�̃C���X�^���X���擾
	stage_ = Stage::GetInstance();

	// ���W��ݒ�
	nowTransform_.setPos_(tnl::Vector3(gridPos_.x, 1, gridPos_.y) * gridSize_);

	// 1�t���[���̈ړ��ʂ�������
	moveVal_ = gridSize_ / 10;
}


// �f�X�g���N�^
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


// �ҋ@���̃V�[�P���X
// ��{�̃V�[�P���X�ƂȂ�̂ŁA
// ���̃V�[�P���X���I�������炱�̃V�[�P���X�ɖ߂�����
bool Player::seqIdle(const float delta_time) {

	//----------------------------------------------------------------------
	// ���ʂɑO�i���鏈��

	// W���������Ƃ�
	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {

		// ���Ɉړ�������W���v�Z����
		nextGridPos_ = calcMoveGrid(frontDir_);

		// �ړ�����V�[�P���X�Ɉړ�
		seq_.change(&Player::seqMoveCheck);
		seqNow_ = " seqMoveCheck ";
	}


	//----------------------------------------------------------------------
	// ���ʈړ��ȊO�̏���

	// A���������Ƃ�
	else if (tnl::Input::IsKeyDown(eKeys::KB_A)) {

		// ���ɕ��s�ړ����鏈��
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			// �ړ�������̃}�X�ɐݒ�
			nextGridPos_ = calcMoveGrid(frontDir_ + Enum::Dir4::LEFT);

			// �ړ�����V�[�P���X�Ɉړ�
			seq_.change(&Player::seqMoveCheck);
			seqNow_ = " seqMoveCheck ";
		}
		// �������ɉ�]���鏈��
		else {
			// �������������ɉ�
			nextDir_ += Enum::Dir4::LEFT;
			// ��]����V�[�P���X�Ɉړ�
			seq_.change(&Player::seqRotateCheck);

			seqNow_ = " seqRotCheck ";
		}
	}

	// D���������Ƃ�
	else if (tnl::Input::IsKeyDown(eKeys::KB_D)) {

		// �E�ɕ��s�ړ����鏈��
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			// �ړ�����E�̃}�X�ɐݒ�
			nextGridPos_ = calcMoveGrid(frontDir_ + Enum::Dir4::RIGHT);

			// �ړ�����V�[�P���X�Ɉړ�
			seq_.change(&Player::seqMoveCheck);
			seqNow_ = " seqMoveCheck ";
		}
		// �E�����ɉ�]���鏈��
		else {
			// �����������E�ɉ�
			nextDir_ += Enum::Dir4::RIGHT;
			// ��]����V�[�P���X�Ɉړ�
			seq_.change(&Player::seqRotateCheck);

			seqNow_ = " seqRotCheck ";
		}
	}

	// S���������Ƃ�
	else if (tnl::Input::IsKeyDown(eKeys::KB_S)) {

		// ���ɕ��s�ړ����鏈��
		if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

			// �ړ�������̃}�X�ɐݒ�
			nextGridPos_ = calcMoveGrid(frontDir_ + Enum::Dir4::DOWN);

			// �ړ�����V�[�P���X�Ɉړ�
			seq_.change(&Player::seqMoveCheck);
			seqNow_ = " seqMoveCheck ";
		}

		else {
			// �����������������ɉ�
			nextDir_ += Enum::Dir4::DOWN;
			// ��]����V�[�P���X�Ɉړ�
			seq_.change(&Player::seqRotateCheck);

			seqNow_ = " seqRotCheck ";
		}
	}

	return true;
}


// �ړ�����������V�[�P���X
bool Player::seqMoveCheck(const float delta_time) {

	// �ړ��悪�z��O�̏ꍇ�ړ����Ȃ��悤�ɂ��邽�߂̏���
	if (stage_->CheckGridPosInt(nextGridPos_) == -1) {
		tnl::DebugTrace("�z��O�̂��߈ړ��ł��܂���\n");
		
		seqNow_ = "seqIdle";
		
		seq_.change(&Player::seqIdle);

		return true;
	}

	// �ړ���̃}�X���ړ��ł��Ȃ��Ƃ�
	if ( !(stage_->CheckGridPosObj(nextGridPos_)->getCanMove()) ) {

		// ���̍��W�����݂̍��W�ɖ߂�
		nextGridPos_ = gridPos_;
		// �V�[�P���X��ҋ@���ɖ߂�
		seq_.change(&Player::seqIdle);

		seqNow_ = " seqIdle ";
		// �������I������
		return true;
	}
	// �ړ��ł���Ƃ�
	else {
		// �ړ���̍��W��ݒ�
		nextTransform_.setPos_( { nextGridPos_.x * gridSize_, gridSize_, -nextGridPos_.y * gridSize_ });

		// ������s���V�[�P���X�ɐ؂�ւ�
		seq_.change(&Player::seqMoving);

		// �V�[�P���X�̐؂�ւ��𐧌�
		canChengeSeq_ = false;

		seqNow_ = " seqMoving ";

		return true;
	}
	
}

// ��]����������V�[�P���X
bool Player::seqRotateCheck(const float delta_time) {

	// ���̌����ɉ����Ď��̕�����ύX����
	// ��������v���X�Ƃ���
	if (nextDir_ == Enum::Dir4::LEFT) {
		// ��]������ʂ�90�x�ɂ���
		rotValMax_ = -90;
	}
	else if (nextDir_ == Enum::Dir4::DOWN) {
		// ��]������ʂ�180�x�ɂ���
		rotValMax_ = -180;
	}
	else if (nextDir_ == Enum::Dir4::RIGHT) {
		// ��]������ʂ�-90�x�ɂ���
		rotValMax_ = 90;
	}

	// ���̊p�x�����݂̊p�x�����]�ʕ���]������
	nextTransform_.setRot3D_(nextTransform_.getRot3D_() * tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(rotValMax_)));

	// ��]���s���V�[�P���X�ɐ؂�ւ�
	seq_.change(&Player::seqRotating);

	// �V�[�P���X�̐؂�ւ��𐧌�
	canChengeSeq_ = false;

	seqNow_ = " seqRotating ";

	return true;
}

// �ړ����s���V�[�P���X
bool Player::seqMoving(const float delta_time) {

	Moving(delta_time);

	if (canChengeSeq_) {
		seq_.change(&Player::seqIdle);
	}

	return true;
}


// ��]���s���V�[�P���X
bool Player::seqRotating(const float delta_time) {

	Rotating(delta_time);

	if (canChengeSeq_) {

		seq_.change(&Player::seqIdle);
		seqNow_ = " seqIdle ";

	}

	return true;
	
}


