#include "ActionMeleeAttack.h"


// �U���̃N���X�𐶐����鏈�����R���X�g���N�^�Ȃ񂩂ɏ����I
// �����������������������������������������I�I�I�I�I�I�I�I�I�I�I�I�I�I�I



// �R���X�g���N�^
// �����F	actionCharacter ... �s�����s���L�����N�^�[, targetCharacter ... �U���Ώۂ̃L�����N�^�[
ActionMeleeAttack::ActionMeleeAttack(std::shared_ptr < BattleCharacterBase > actionCharacter, std::shared_ptr < BattleCharacterBase > targetCharacter)
	: ActionAttackBase(actionCharacter, targetCharacter), moveRangeMax_(150), moveRangeMin_(moveRangeMax_ / 2), attackRange_(30)
{
	// �ړ���̍��W������
	targetPosDecade();

}

// �f�X�g���N�^
ActionMeleeAttack::~ActionMeleeAttack() {

}


void ActionMeleeAttack::update(const float delta_time) {

	// �s�����I�����Ă���ꍇ�A�ȉ��̏������s��Ȃ�
	if (BattleActionBase::isFinished_) {
		return;
	}

	
	// �x�[�X�N���X�̍X�V
	ActionAttackBase::update(delta_time);

	// �V�[�P���X�̍X�V
	seq_.update(delta_time);


}


// �s�������s����O�ɁA���l�����������邽�߂̊֐�
void ActionMeleeAttack::setUpAction() {

	// �s�����I�����Ă��Ȃ���ԂɕύX
	BattleActionBase::isFinished_ = false;

	targetPosDecade();

}

// �ړ��Ɋւ��鏉���ݒ���s���֐�
void ActionMeleeAttack::targetPosDecade() {

	// �ړ��ʂ��擾
	moveValue_ = actionCharacter_->getMoveValue();

	// �ړ�����������0�ɂ���
	movedValueCount_ = 0;



	// �ړ��̊p�x�Ƌ������v�Z
	float angle = rand() % 360;
	float distance = rand() % static_cast<int>(moveRangeMax_);



	// �p�x�Ƌ���������W���v�Z
	targetPos_.x = actionCharacter_->getPos().x + distance * cos(angle);
	targetPos_.z = actionCharacter_->getPos().z + distance * sin(angle);

	// �ړ����鋗�����v�Z
	totalMoveValue_ = (targetPos_ - actionCharacter_->getPos()).length();


	// �ړ�����������v�Z
	// �i�ړ���̍��W - ���݂̍��W�j�𐳋K��
	moveVectorNor_ = tnl::Vector3::Normalize(targetPos_ - (actionCharacter_->getPos()));

	// �ړ��ʂ��v�Z
	moveVector_ = moveVectorNor_ * moveValue_;

}


// �ړ�������Ɍ��݂̈ʒu���m�F���鏈��
void ActionMeleeAttack::CheckPosition() {


	// �U���͈͓��ɓ����Ă���Ƃ��͍U���̃V�[�P���X�ɐ؂�ւ���
	if ((actionCharacter_->getPos() - targetPos_).length() <= attackRange_) {

		seq_.change(&ActionMeleeAttack::seqMeleeAttack);
	}

}


// �U���̕��������肷��֐�
void ActionMeleeAttack::AttackDirectionDecade() {


	tnl::Vector3 toTargetVector = targetPos_ - actionCharacter_->getPos();



}



// �ߊ���Ă���ۂ̃V�[�P���X
bool ActionMeleeAttack::seqComing( const float delta_time ) {

	// �ړ���̍��W���Z�b�g
	targetPos_ = targetCharacter_->getPos();

	// �ړ��������v�Z
	moveVectorNor_ = tnl::Vector3::Normalize(targetPos_ - (actionCharacter_->getPos()));;

	// �L�����N�^�[���ړ�������
	actionCharacter_->MoveCharacter(moveVectorNor_, moveVectorMag_);

	// ���W���m�F
	CheckPosition();

	return true;
}


// �ߐڍU�����s���V�[�P���X
bool ActionMeleeAttack::seqMeleeAttack(const float delta_time) {

	
	


}
