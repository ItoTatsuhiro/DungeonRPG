#include "CharacterBase.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include "../map/Stage.h"


CharacterBase::CharacterBase(float gridSize, tnl::Vector2i startPos) : EntityBase(startPos, gridSize) {

	// �����ς̃X�e�[�W�̃C���X�^���X���擾
	stage_ = Stage::GetInstance();

	// ���W��ݒ�
	nowTransform_.setPos_(tnl::Vector3(gridPos_.x, 1, gridPos_.y) * gridSize_);

	// 1�t���[���̈ړ��ʂ�������
	moveVal_ = gridSize_ / 10;

}


CharacterBase::~CharacterBase() {

}


void CharacterBase::update(float delta_time) {

	seq_.update(delta_time);

}


void CharacterBase::draw() {

}

// �ҋ@���̃V�[�P���X
// ��{�̃V�[�P���X�ƂȂ�̂ŁA���̃V�[�P���X���I�������炱�̃V�[�P���X�ɖ߂�
// ���p����ł��ꂼ��I�[�o�[���C�h���Ďg�p���邱��
bool CharacterBase::seqIdle(const float delta_time) {

	return true;
}


// �ړ�����������V�[�P���X
bool CharacterBase::seqMoveCheck(const float delta_time) {

	// �ړ��悪�z��O�̏ꍇ�ړ����Ȃ��悤�ɂ��邽�߂̏���
	if (stage_->CheckGridPosInt(nextGridPos_) == -1) {
		tnl::DebugTrace("�z��O�̂��߈ړ��ł��܂���\n");

		// seqNow_ = "seqIdle";

		seq_.change(&CharacterBase::seqIdle);

		return true;
	}

	// �ړ���̃}�X���ړ��ł��Ȃ��Ƃ�
	if (!(stage_->CheckGridPosObj(nextGridPos_)->getCanMove())) {

		// ���̍��W�����݂̍��W�ɖ߂�
		nextGridPos_ = gridPos_;
		// �V�[�P���X��ҋ@���ɖ߂�
		seq_.change(&CharacterBase::seqIdle);

		// seqNow_ = " seqIdle ";
		// �������I������
		return true;
	}
	// �ړ��ł���Ƃ�
	else {

		nextTransform_.setPos_({ nextGridPos_.x * gridSize_, gridSize_, -nextGridPos_.y * gridSize_ });

		// ������s���V�[�P���X�ɐ؂�ւ�
		seq_.change(&CharacterBase::seqMoving);

		// seqNow_ = " seqMoving ";

		return true;
	}

}

// ��]����������V�[�P���X
bool CharacterBase::seqRotateCheck(const float delta_time) {

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
	seq_.change(&CharacterBase::seqRotating);

	// seqNow_ = " seqRotating ";

	return true;
}

// �ړ����s���V�[�P���X
bool CharacterBase::seqMoving(const float delta_time) {

	// �ړ��ʂɉ����ĕʂ̕����Ɉړ�
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


	// �ړ���̍��W�ƌ��݂̍��W�̍����\���ɏ�������(�ړ����������Ƃ�)
	if ((nextTransform_.getPos_() - nowTransform_.getPos_()).length() < FLT_EPSILON) {

		// ���݂̍��W���ړ���̍��W�ɍ��킹��
		nowTransform_.setPos_(nextTransform_.getPos_());
		// ���݂̃}�X�ڂ��X�V
		gridPos_ = nextGridPos_;
		// �ړ�����ʂ����Z�b�g
		moveGrid_ = tnl::Vector2i{ 0, 0 };

		// �ҋ@���̃V�[�P���X�ɐ؂�ւ�
		seq_.change(&CharacterBase::seqIdle);

		// seqNow_ = " seqIdle ";

		return true;
	}


}

// ��]���s���V�[�P���X
bool CharacterBase::seqRotating(const float delta_time) {

	if (rotValMax_ > 0) {

		// ��]�ʕ���
		nowTransform_.setRot3D_(nowTransform_.getRot3D_() * tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(rotValFrame_)));
		// �񂵂����A�c��̉�]�ʂ������
		rotValMax_ -= rotValFrame_;

		// ��肷�����Ƃ�
		if (rotValMax_ < 0) {
			// ��肷��������߂�
			nowTransform_.setRot3D_(nextTransform_.getRot3D_());

			rotValMax_ = 0;
		}

	}
	else if (rotValMax_ < 0) {

		// ��]�ʕ���
		nowTransform_.setRot3D_(nowTransform_.getRot3D_() * tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(-rotValFrame_)));
		// �񂵂����c��̉�]�ʂɉ��Z����
		// (��]�ʂ��}�C�i�X����̃X�^�[�g�̂���)
		rotValMax_ += rotValFrame_;
		// ��肷������
		if (rotValMax_ > 0) {
			// ��肷��������߂�
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