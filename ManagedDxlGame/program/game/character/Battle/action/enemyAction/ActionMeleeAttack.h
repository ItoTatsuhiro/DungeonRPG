#pragma once
#include "../../../../../dxlib_ext/dxlib_ext.h"
#include "../BattleActionBase.h"
#include "../../../other/BattleCharacterBase.h"
#include "../ActionAttackBase.h"


// �ړ��̍s���̃N���X
// �ړ��݂̂̍s�����s���ꍇ�Ɏg�p����
// �����_���Ȉʒu�����肵�A�ړ�������
class ActionMeleeAttack final : public ActionAttackBase {
public:

	// �R���X�g���N�^
	// �����FactionCharacter ... �s�����s���L�����N�^�[, charaList...�V�[���ɑ��݂���L�����N�^�[�̃��X�g
	ActionMeleeAttack(const std::shared_ptr<BattleCharacterBase>& actionCharacter, const std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>>& charaList);

	// �f�X�g���N�^
	~ActionMeleeAttack();

	// �s�������s����update�֐�
	void update(const float delta_time);


	// �s�������s����O�ɁA���l�����������邽�߂̊֐�
	// �ړ���̍��W�itargetPos_�j�A�ړ��ʊ֘A�imoveValue_, moveVectorNor_, moveVector_�j���ēx�v�Z
	void setUpAction() override;


	// �ړ���̍��W�����肷��
	void targetPosDecade();


	// �U���Ώۂ�I������֐�
	// ActionAttackBase�̉��z�֐����I�[�o�[���C�h���Ďg�p
	void SelectTargetCharacter() override;


private:




	// �ڕW�n�_�̍��W
	// �֐��ňړ��n�_�̕ύX���ɕύX
	tnl::Vector3 targetPos_;

	// �U�����s���͈�
	// ���͈͓̔��܂ňړ������ۂɍU�������s����
	float attackRange_;

	// �ړ��ʂ̔{��
	// �U���O�ɋ߂Â����x��ʏ�̈ړ����x��葬���������ꍇ�ɕύX
	// �ʏ��1.0f
	float moveVectorMag_;




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

	// �ړ�������Ɍ��݂̈ʒu���m�F���鏈��
	void CheckPosition();


	// �U���̕��������肷��֐�
	void SetAttackDetail();



	tnl::Sequence<ActionMeleeAttack> seq_ = tnl::Sequence<ActionMeleeAttack>(this, &ActionMeleeAttack::seqComing);


	// �ߊ���Ă���ۂ̃V�[�P���X
	bool seqComing(const float delta_time);
	// �ߐڍU�����s���V�[�P���X
	bool seqMeleeAttack(const float delta_time);


};