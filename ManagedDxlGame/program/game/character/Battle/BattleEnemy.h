#pragma once

#include "../other/BattleCharacterBase.h"

// �o�g���V�[���ł̓G�L�����N�^�[�̃N���X
// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�I�u�W�F�N�g�̑傫��, std::string objectName...�I�u�W�F�N�g��
class BattleEnemy : public BattleCharacterBase {
public :
	// �R���X�g���N�^
	// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�I�u�W�F�N�g�̑傫��, std::string objectName...�I�u�W�F�N�g��
	// �ړ��O�̍��W�͊J�n�ʒu�ŏ�����
	// SpriteObjectBase�̈����������
	BattleEnemy(tnl::Vector3 startPos, float objSize, std::string objName);

	// �f�X�g���N�^
	~BattleEnemy();

	// �X�V�p�̊֐�
	void update(float delta_time) override;
	// �`��p�̊֐�
	void draw(std::shared_ptr<dxe::Camera> camera) override;


protected :

	// �ړ����s���֐�
	void Move(float delta_time);

	// �U���̏����ɓ��邽�߂̊֐�
	// �U���̂��߂̃L�[���͂��������Ƃ��V�[�P���X��؂�ւ��鏈�����s��
	void OnAttackKey();

	// �ړ�����ڕW�n�_�̍��W
	tnl::Vector3 moveTargetPos_;


	// �U���̑傫��
	// �R���X�g���N�^�ŏ�����
	float attackSize_;

	// �V�[�P���X�����p�̕ϐ�
	tnl::Sequence<BattleEnemy> seq_ = tnl::Sequence<BattleEnemy>(this, &BattleEnemy::seqActDecade);

	// �s�������肷��V�[�P���X
	bool seqActDecade(const float delta_time);
	// �ړ����s���V�[�P���X
	bool seqMove(const float delta_time);
	// �U���̃V�[�P���X
	bool seqAttack(const float delta_time);

};