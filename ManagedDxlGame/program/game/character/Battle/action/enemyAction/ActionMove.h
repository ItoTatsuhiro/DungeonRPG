#pragma once
#include "../../../../../dxlib_ext/dxlib_ext.h"
#include "../BattleActionBase.h"
#include "../../../other/BattleCharacterBase.h"

// �ړ��̍s���̃N���X
// �ړ��݂̂̍s�����s���ꍇ�Ɏg�p����
// �����_���Ȉʒu�����肵�A�ړ�������
class ActionMove final: public BattleActionBase {
public :

	// �R���X�g���N�^
	// �����F	actionCharacter ... �s�����s���L�����N�^�[
	ActionMove(std::shared_ptr < BattleCharacterBase > actionCharacter);

	// �f�X�g���N�^
	~ActionMove();

	// �s�������s����update�֐�
	void update(const float delta_time);


	// �s�������s����O�ɁA���l�����������邽�߂̊֐�
	// �ړ���̍��W�itargetPos_�j�A�ړ��ʊ֘A�imoveValue_, moveVectorNor_, moveVector_�j���ēx�v�Z
	void setUpAction() override;


	// �ړ���̍��W�����肷��
	void targetPosDecade();

private :


	// �ڕW�n�_�̍��W
	// �֐��ňړ��n�_�̕ύX���ɕύX
	tnl::Vector3 targetPos_;

	// �ړ��͈͂̍ő�̑傫��
	// �i�L�����N�^�[����̔��a�j
	// �֐��ňړ��n�_�̕ύX���ɕύX
	float moveRangeMax_;

	// �ړ��͈͂̍ŏ��̑傫��
	// �i�L�����N�^�[����̔��a�j
	// �֐��ňړ��n�_�̕ύX���ɕύX
	float moveRangeMin_;

	//// �ړ���
	// �֐��ňړ��n�_�̕ύX���ɕύX
	float moveValue_;

	// �ړ������������J�E���g����ϐ�
	// ���̒l��totalMoveValue_�𒴂����Ƃ��ړ��̏������I��������
	float movedValueCount_;

	// �ŏI�I�Ɉړ����鋗���̕ϐ�
	// �ړ��̍ۂɁA�ŏI�I�ɂ��̋�����i�ނ悤�ɂ���
	float totalMoveValue_;

	// �ړ������̃x�N�g��
	// �R���X�g���N�^���Ōv�Z��������
	tnl::Vector3 moveVectorNor_;

	// �ړ��̃x�N�g��
	// �R���X�g���N�^���Ōv�Z��������
	tnl::Vector3 moveVector_;

};