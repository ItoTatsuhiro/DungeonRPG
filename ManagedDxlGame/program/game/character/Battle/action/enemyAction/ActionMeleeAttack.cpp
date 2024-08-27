#include "ActionMeleeAttack.h"
#include "../../attack/Attack.h"

// �R���X�g���N�^
// �����F	actionCharacter ... �s�����s���L�����N�^�[, targetCharacter ... �U���Ώۂ̃L�����N�^�[
ActionMeleeAttack::ActionMeleeAttack(const std::shared_ptr<BattleCharacterBase>& actionCharacter, const std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>>& charaList)
	: ActionAttackBase(actionCharacter, charaList), moveRangeMax_(150), moveRangeMin_(moveRangeMax_ / 2), attackRange_(30), moveVectorMag_(1.0)
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

	// �V�[�P���X�̍X�V
	seq_.update(delta_time);


}


// �s�������s����O�ɁA���l�����������邽�߂̊֐�
void ActionMeleeAttack::setUpAction() {

	// �s�����I�����Ă��Ȃ���ԂɕύX
	BattleActionBase::isFinished_ = false;
	
	MakeAttack("attackEffect.png");

	SelectTargetCharacter();

	targetPosDecade();

	// �V�[�P���X��������Ԃɖ߂��Ă���
	seq_.change(&ActionMeleeAttack::seqComing);
}


// �ړ��Ɋւ��鏉���ݒ���s���֐�
void ActionMeleeAttack::targetPosDecade() {


	auto actionCharacter = actionCharacter_.lock();

	if ( !actionCharacter ) {
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




// �U���Ώۂ�I������֐�
// ActionAttackBase�̉��z�֐����I�[�o�[���C�h���Ďg�p
void ActionMeleeAttack::SelectTargetCharacter() {

	// �L�����N�^�[�̃��X�g�̊m�F
	auto charaList = charaList_.lock();
	// �s������L�����N�^�[�̊m�F
	auto actionCharacter = actionCharacter_.lock();

	if ( !charaList || !actionCharacter ) {
		return;
	}



	auto it = charaList->begin();

	while (it != charaList->end()) {

		// ���g�ƈقȂ��ނ̃L�����N�^�[���������Ƃ��Ώۂ̃L�����N�^�[�Ƃ���
		// ���v���C���[�L�����N�^�[�͌���1�L�����̗\��̂��߁A�������炻����U���ΏۂƂ���
		if ((*it)->getCharacterType() != actionCharacter->getCharacterType()) {

			targetCharacter_ = (*it);

			break;
		}

		++it;
	}

	return;

}




//----------------------------------------------------------------------------------------------------
// private

// �ړ�������Ɍ��݂̈ʒu���m�F���鏈��
void ActionMeleeAttack::CheckPosition() {

	auto actionCharacter = actionCharacter_.lock();

	if (actionCharacter == nullptr) {
		return;
	}


	// �U���͈͓��ɓ����Ă���Ƃ��͍U���̃V�[�P���X�ɐ؂�ւ���
	if ((actionCharacter->getPos() - targetPos_).length() <= attackRange_) {

		seq_.change(&ActionMeleeAttack::seqMeleeAttack);
	}

}


// �U���̕��������肷��֐�
void ActionMeleeAttack::SetAttackDetail() {

	auto actionCharacter = actionCharacter_.lock();

	auto attack = attack_.lock();

	if (!actionCharacter || !attack) {
		return;
	}


	//--------------------------------------------------------------------------------
	// �U������������

	// �^�[�Q�b�g�ւ̕������m�F
	tnl::Vector3 toTargetVector = tnl::Vector3::Normalize(targetPos_ - actionCharacter->getPos());


	//--------------------------------------------------------------------------------
	// ���W�̌v�Z�A�Z�b�g

	// �U���̃��b�V���̍��W���v�Z
	tnl::Vector3 attackPos = actionCharacter->getPos() + toTargetVector * attack->getMeshSize();
	// �U���̃��b�V���̍��W���Z�b�g
	attack->setPos(attackPos);
	// ��Ԃ��A�N�e�B�u�ɃZ�b�g
	attack->setIsActive(true);
}






// �ߊ���Ă���ۂ̃V�[�P���X
bool ActionMeleeAttack::seqComing( const float delta_time ) {

	auto actionCharacter = actionCharacter_.lock();

	auto targetCharacter = targetCharacter_.lock();

	if ( !actionCharacter || !targetCharacter ) {
		return true;
	}


	// �ړ���̍��W���Z�b�g
	targetPos_ = targetCharacter->getPos();

	// �ړ��������v�Z
	moveVectorNor_ = tnl::Vector3::Normalize(targetPos_ - (actionCharacter->getPos()) );

	// �L�����N�^�[���ړ�������
	actionCharacter->MoveCharacter(delta_time, moveVectorNor_, moveVectorMag_);

	// ���W���m�F
	// �U���͈͓��ɓ����Ă���Ƃ��͍U���̃V�[�P���X�ɐ؂�ւ���
	if ((actionCharacter->getPos() - targetPos_).length() <= attackRange_) {

		SetAttackDetail();

		seq_.change(&ActionMeleeAttack::seqMeleeAttack);
	}

	return true;
}


// �ߐڍU�����s���V�[�P���X
bool ActionMeleeAttack::seqMeleeAttack(const float delta_time) {


	// �x�[�X�N���X�̍X�V
	// �x�[�X�N���X�ł͍U���̃��b�V���̍X�V�̂ݍs���Ă���̂ŁA
	// �U���̏������X�V���邱�̃V�[�P���X�ōX�V���s��
	ActionAttackBase::update(delta_time);


	auto attack = attack_.lock();

	if (!attack->getIsActive()) {

		seq_.change(&ActionMeleeAttack::seqComing);

		// �s�����I�����Ă����Ԃɂ���
		// �i�G�L�����N�^�[�̃N���X�ŁA���s����s����؂�ւ��邽�߁j
		isFinished_ = true;

		return true;
	}


	// �U���̏������I�����Ă���ۂ͏������I��������
	if (attack->getIsEnd()) {
		seq_.change(&ActionMeleeAttack::seqComing);

		// �s�����I�����Ă����Ԃɂ���
		// �i�G�L�����N�^�[�̃N���X�ŁA���s����s����؂�ւ��邽�߁j
		isFinished_ = true;
	}


	return true;
}

