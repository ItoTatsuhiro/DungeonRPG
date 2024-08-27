#include "ActionMove.h"

// �R���X�g���N�^
// �����F	actionCharacter ... �s�����s���L�����N�^�[
ActionMove::ActionMove(std::shared_ptr < BattleCharacterBase > actionCharacter)
	: BattleActionBase(actionCharacter), moveRangeMax_(150), moveRangeMin_(moveRangeMax_ / 2)
{
	// �ړ���̍��W������
	targetPosDecade();



}

// �f�X�g���N�^
ActionMove::~ActionMove() {

}


void ActionMove::update(const float delta_time) {

	// �s�����I�����Ă���ꍇ�A�ȉ��̏������s��Ȃ�
	if (BattleActionBase::isFinished_) {
		return;
	}

	auto actionCharacter = actionCharacter_.lock();

	if (actionCharacter == nullptr) {
		return;
	}


	// �ړ��ʕ��ړ��̏������s��
	actionCharacter->MoveCharacter(delta_time, moveVectorNor_);

	// �ړ������������J�E���g
	movedValueCount_ += actionCharacter->getMoveValue() * delta_time;


	// �������ړ����؂����Ƃ��s�����I��������
	if (movedValueCount_ >= totalMoveValue_) {

		// �L�����N�^�[�̍��W��ڕW�n�_�̍��W�ɕ␳
		actionCharacter->setPos(targetPos_);

		movedValueCount_ = 0;

		// �s�����I�����Ă��邩�̃t���O��true�ɂ���
		BattleActionBase::isFinished_ = true;

		return;
	}
}


// �s�������s����O�ɁA���l�����������邽�߂̊֐�
void ActionMove::setUpAction() {

	// �s�����I�����Ă��Ȃ���ԂɕύX
	BattleActionBase::isFinished_ = false;

	targetPosDecade();

}

// �ړ��Ɋւ��鏉���ݒ���s���֐�
void ActionMove::targetPosDecade() {

	auto actionCharacter = actionCharacter_.lock();

	if (actionCharacter == nullptr) {
		return;
	}


	// �ړ��ʂ��擾
	moveValue_ = actionCharacter->getMoveValue();

	// �ړ�����������0�ɂ���
	movedValueCount_ = 0;

	// �ړ��̊p�x�Ƌ������v�Z
	float angle = rand() % 360;
	float distance = rand() % static_cast<int>(moveRangeMax_);


	// �p�x�Ƌ���������W���v�Z
	targetPos_.x = actionCharacter->getPos().x + distance * cos(angle);
	targetPos_.z = actionCharacter->getPos().z + distance * sin(angle);

	// �ړ����鋗�����v�Z
	totalMoveValue_ = (targetPos_ - actionCharacter->getPos()).length();


	// �ړ�����������v�Z
	// �i�ړ���̍��W - ���݂̍��W�j�𐳋K��
	moveVectorNor_ = tnl::Vector3::Normalize(targetPos_ - (actionCharacter->getPos()));

	// �ړ��ʂ��v�Z
	moveVector_ = moveVectorNor_ * moveValue_;
}
