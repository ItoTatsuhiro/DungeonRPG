#pragma once
#include "../../../../../dxlib_ext/dxlib_ext.h"
#include "../BattleActionBase.h"
#include "../../../other/BattleCharacterBase.h"

// �ړ��̍s���̃N���X
// �ړ��݂̂̍s�����s���ꍇ�Ɏg�p����
// �����_���Ȉʒu�����肵�A�ړ�������
class ActionWait final : public BattleActionBase {
public:

	// �R���X�g���N�^
	// �����F	actionCharacter ... �s�����s���L�����N�^�[
	ActionWait(std::shared_ptr < BattleCharacterBase > actionCharacter);

	// �f�X�g���N�^
	~ActionWait();

	// �s�������s����update�֐�
	void update(const float delta_time);


	// �s�������s����O�ɁA���l�����������邽�߂̊֐�
	void setUpAction() override;


	//// �ҋ@���鎞�Ԃ����肷��֐�
	//void waitTimeDecade();

private:


	// �ҋ@���鎞�Ԃ̍ő�l
	float waitTimeMax_;

	// �ҋ@���鎞�Ԃ̍ŏ��l
	float waitTimeMin_;

	// �ҋ@���鎞��
	float waitTime_;

	// �ҋ@���n�߂Ă���o�߂�������
	float waitCount_;

};