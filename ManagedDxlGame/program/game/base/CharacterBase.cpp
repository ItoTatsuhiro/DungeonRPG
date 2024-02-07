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

}


void CharacterBase::draw() {

}

// �ړ����s���֐�
// Player, Enemy���̈ړ����s���ۂ͂��̊֐����g�p����
void CharacterBase::Moving( float delta_time ) {

	// �������I�����Ă���ɂ�������炸����ČĂяo���Ă��܂����ۂ̏���
	if (finishAction_) {
		tnl::DebugTrace("���ɏ����͏I�����Ă��܂�\n");
		return;
	}

	// �ړ��ʂɉ����ĕʂ̕����Ɉړ�
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


	// �ړ���̍��W�ƌ��݂̍��W�̍����\���ɏ�������(�ړ����������Ƃ�)
	if ((nextTransform_.getPos_() - nowTransform_.getPos_()).length() < FLT_EPSILON) {

		// ���݂̍��W���ړ���̍��W�ɍ��킹��
		nowTransform_.setPos_(nextTransform_.getPos_());
		// ���݂̃}�X�ڂ��X�V
		gridPos_ = nextGridPos_;
		// �ړ�����ʂ����Z�b�g
		moveGrid_ = tnl::Vector2i{ 0, 0 };

		finishAction_ = true;
	}

}


// ��]���s���֐�
// Plauer, Enemy���̉�]���s���ۂ͂��̊֐����g�p����
// ��2024/02/08 ���݁AEnemy�ł̉�]�̏����͂�����g�p���Ă��Ȃ�
void CharacterBase::Rotating(float delta_time) {

	// �������I�����Ă���ɂ�������炸����ČĂяo���Ă��܂����ۂ̏���
	if (finishAction_) {
		tnl::DebugTrace("���ɏ����͏I�����Ă��܂�\n");
		return;
	}


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

	// �c��̈ړ��ʂ��Ȃ��Ȃ����Ƃ��������I�����邽�߂̏���
	if (std::abs(rotValMax_) < FLT_EPSILON) {

		frontDir_ += nextDir_;

		nextDir_ = Enum::Dir4::UP;

		finishAction_ = true;
	}

}

// �ڑ���̃}�X���v�Z����֐�
// �ړ�����ʂ��v�Z���Ă��邽�߁A�ړ�����ۂ͂������x�Ăяo������
tnl::Vector2i CharacterBase::calcMoveGrid(Enum::Dir4 moveDir) {

	// �ړ���̍��W
	// �߂�l�Ŗ߂��p
	tnl::Vector2i nextGridPos;

	// �����ɉ����č��W���v�Z
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

	// ���̈ړ��ʂ��v�Z
	moveGrid_ = nextGridPos - gridPos_;

	return nextGridPos;
}