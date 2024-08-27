#include "ActionRangeAttack.h"
#include "../../attack/Attack.h"
#include "../../../other/BattleCharacterBase.h"

// �R���X�g���N�^
// �����F	actionCharacter ... �s�����s���L�����N�^�[,
//			charaList...�V�[���ɑ��݂���L�����N�^�[�̃��X�g
//			waitTimeBefore...�U���O�̑ҋ@���ԁA�f�t�H���g��1.0f
//			waitTimeAfter...�U����̑ҋ@���ԁA�f�t�H���g��1.0f
ActionRangeAttack::ActionRangeAttack(const std::shared_ptr<BattleCharacterBase>& actionCharacter,
		const std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>>& charaList,
		float waitTimeBefore, float waitTimeAfter)
	: ActionAttackBase(actionCharacter, charaList)
{
	//// �ړ���̍��W������
	//targetPosDecade();


}

// �f�X�g���N�^
ActionRangeAttack::~ActionRangeAttack() {

}


void ActionRangeAttack::update(const float delta_time) {

	// �s�����I�����Ă���ꍇ�A�ȉ��̏������s��Ȃ�
	if (BattleActionBase::isFinished_) {
		return;
	}

	// �V�[�P���X�̍X�V
	seq_.update(delta_time);


}


// �s�������s����O�ɁA���l�����������邽�߂̊֐�
void ActionRangeAttack::setUpAction() {

	// �s�����I�����Ă��Ȃ���ԂɕύX
	BattleActionBase::isFinished_ = false;

	MakeAttack();

	SelectTargetCharacter();

	//targetPosDecade();

	// �V�[�P���X��������Ԃɖ߂��Ă���
	seq_.change(&ActionRangeAttack::seqWaitBefore);
}




// �U���Ώۂ�I������֐�
// ActionAttackBase�̉��z�֐����I�[�o�[���C�h���Ďg�p
void ActionRangeAttack::SelectTargetCharacter() {

	// �L�����N�^�[�̃��X�g�̊m�F
	auto charaList = charaList_.lock();
	// �s������L�����N�^�[�̊m�F
	auto actionCharacter = actionCharacter_.lock();

	if (!charaList || !actionCharacter) {
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




// �U���O�̑ҋ@�V�[�P���X
bool ActionRangeAttack::seqWaitBefore(const float delta_time) {

	// **********************************************
	// �ҋ@���̏������L��Ώ���
	// *********************************************



	// �V�[�P���X�̌o�ߎ��Ԃ��U���O�̑ҋ@���Ԃ𒴂����Ƃ�
	if (seq_.getProgressTime() > waitTimeBefore_) {


		// �ڕW�n�_������
		targetPos_ = targetCharacter_.lock()->getPos();


		// �������U���̃V�[�P���X�Ɉڂ�
		seq_.change(&ActionRangeAttack::seqRangeAttack);

	}

	return true;
}


// �������U���̃V�[�P���X
bool ActionRangeAttack::seqRangeAttack(const float delta_time) {


	


	return true;


}


// �U����̑ҋ@�V�[�P���X
bool ActionRangeAttack::seqWaitAfter(const float delta_time) {






	return true;

}


