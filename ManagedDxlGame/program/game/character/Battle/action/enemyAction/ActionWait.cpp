#include "ActionWait.h"
#include "../BattleActionBase.h"



// �R���X�g���N�^
// �����F	actionCharacter ... �s�����s���L�����N�^�[
ActionWait::ActionWait(std::shared_ptr < BattleCharacterBase > actionCharacter) 
	: BattleActionBase(actionCharacter), waitTimeMax_(3), waitTimeMin_(waitTimeMax_ / 2)
{
	setUpAction();
}

// �f�X�g���N�^
ActionWait::~ActionWait() {

}

// �s�������s����update�֐�
void ActionWait::update(const float delta_time) {

	// �o�ߎ��Ԃ����Z
	waitCount_ += delta_time;

	// �o�ߎ��Ԃ������_���Ɍ��肵���ҋ@���Ԃ𒴂����Ƃ�
	if (waitCount_ >= waitTime_) {

		// �s�����I�����Ă��邩�̃t���O��true�ɂ���
		BattleActionBase::isFinished_ = true;

	}
}


// �s�������s����O�ɁA���l�����������邽�߂̊֐�
void ActionWait::setUpAction() {

	// �ҋ@���Ԃ̌���
	float waitTimeRange = waitTimeMax_ - waitTimeMin_;
	float randTime = (rand() % static_cast<int>(waitTimeRange));
	waitTime_ = waitTimeMin_ + randTime;

	// �o�ߎ��Ԃ����Z�b�g
	waitCount_ = 0;


	auto actionCharacter = actionCharacter_.lock();

	if (actionCharacter == nullptr) {
		return;
	}

	// ��Ԃ�ҋ@��Ԃɂ���
	actionCharacter->setNowSituation(BattleCharacterBase::Situation::WAITING);

}


