#pragma once
#include "../../../../../dxlib_ext/dxlib_ext.h"
#include "../BattleActionBase.h"
#include "../../../other/BattleCharacterBase.h"
#include "../ActionAttackBase.h"


// ����������e�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�P�P�P�P�P�P�P


// �ړ��̍s���̃N���X
// �ړ��݂̂̍s�����s���ꍇ�Ɏg�p����
// �����_���Ȉʒu�����肵�A�ړ�������
class ActionRangeAttack final : public ActionAttackBase {
public:

	// �R���X�g���N�^
	// �����F	actionCharacter ... �s�����s���L�����N�^�[,
	//			charaList...�V�[���ɑ��݂���L�����N�^�[�̃��X�g
	//			waitTimeBefore...�U���O�̑ҋ@���ԁA�f�t�H���g��1.0f
	//			waitTimeAfter...�U����̑ҋ@���ԁA�f�t�H���g��1.0f
	ActionRangeAttack(const std::shared_ptr<BattleCharacterBase>& actionCharacter,
						const std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>>& charaList,
						float waitTimeBefore = 1.0f, float waitTimeAfter = 1.0);

	// �f�X�g���N�^
	~ActionRangeAttack();

	// �s�������s����update�֐�
	void update(const float delta_time);


	// �s�������s����O�ɁA���l�����������邽�߂̊֐�
	// �ړ���̍��W�itargetPos_�j�A�ړ��ʊ֘A�imoveValue_, moveVectorNor_, moveVector_�j���ēx�v�Z
	void setUpAction() override;



	// �U���Ώۂ�I������֐�
	// ActionAttackBase�̉��z�֐����I�[�o�[���C�h���Ďg�p
	void SelectTargetCharacter() override;



private:

	// ***********************************************************
	// �������U���𐶐�����֐�
	// ���̊֐��ł͒ʏ�̍U��������쐬����݂̂��������߁A
	// �������U���𐶐����鏈���ɕύX���č�邱�ƁI�I�I�I�I�I�I�I�I�I�I�I
	//void MakeAttack(std::string fileName = "attackEffect.png", tnl::Vector3 pos = { 0, 0, 0 },
	//	float attackSize = 50, Enum::eDir4 front = Enum::eDir4::UP, float damage = 1.0f) override;



	// �U���O�̑ҋ@����
	float waitTimeBefore_;

	// �U����̑ҋ@����
	float waitTimeAfter_;

	// �������U���̖ڕW�n�_
	tnl::Vector3 targetPos_;



	tnl::Sequence<ActionRangeAttack> seq_ = tnl::Sequence<ActionRangeAttack>(this, &ActionRangeAttack::seqWaitBefore);




	// �U���O�̑ҋ@�V�[�P���X
	bool seqWaitBefore(const float delta_time);
	// �������U���̃V�[�P���X
	bool seqRangeAttack(const float delta_time);
	// �U����̑ҋ@�V�[�P���X
	bool seqWaitAfter(const float delta_time);




};