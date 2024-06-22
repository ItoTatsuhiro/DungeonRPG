#pragma once

#include "../../base/SpriteObjectBase.h"
#include "StatusCharacter.h"
#include "../Battle/attack/Attack.h"


// �o�g���V�[���ł̃L�����N�^�[�̃x�[�X�ƂȂ�N���X
// *************************************************************
// �p����̃N���X�ł́Aupdate,draw�֐������ꂼ��Ăяo�����ƁI
// *************************************************************
// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�L�����N�^�[�̑傫��,
//		std::string objectName...�I�u�W�F�N�g(�L�����N�^�[)��
class BattleCharacterBase : public SpriteObjectBase {
public :

	// �R���X�g���N�^
	BattleCharacterBase(tnl::Vector3 startPos, float objSize, std::string objectName);
	// �f�X�g���N�^
	virtual ~BattleCharacterBase();

	// �X�V�p�̊֐�
	// *********************************************************************
	// �p�����update�֐��ł��A���̃N���X��update�֐����Ăяo������!!
	// *********************************************************************
	virtual void update(float delta_time) = 0;

	// �`��p�̊֐�
	// *********************************************************************
	// �p�����draw�֐��ł��A���̃N���X��draw�֐����Ăяo������!!
	// *********************************************************************
	// �������e
	// 1.�`�悷�郁�b�V���̍��W���X�V
	// 2.�U���̃��b�V���̕`��
	void draw(std::shared_ptr<dxe::Camera> camera) = 0;


	// �L�����N�^�[�̃x�[�X�X�e�[�^�X
	// �R���X�g���N�^�Ő���
	std::shared_ptr< StatusCharacter > status_;


	// �L�����N�^�[���ړ�������֐�
	// �p����̂��ꂼ��̃L�����N�^�[�N���X�ŃL�����N�^�[�𓮂����ۂɂ��̊֐���p���ē�����
	void MoveCharacter(tnl::Vector3 moveVector, float moveVectorMag = 1.0f);

	// �_���[�W���󂯂�֐�
	// �����Fdamage...�󂯂�_���[�W
	void TakeDamage(float damage);





	// ******************************************************************************
	// �ȉ��Q�b�^�[

	// �ړ��O�̍��W���擾����֐�
	// ���W�̕␳���̍ۂɎg�p
	inline tnl::Vector3 getBeforePos() const { return beforePos_; }

	// �ړ��ʂ��擾���邽�߂̊֐�
	inline float getMoveValue() const { return moveValue_; }

	// �_���[�W�������Ԃ��ǂ����擾����֐�
	inline bool getCanTakeDamage() const { return canTakeDamage_; }

	// �U���̃��X�g���擾����֐�
	inline const std::list<std::shared_ptr<Attack>>& getActiveAttackList() const { return activeAttackList_; }

protected :

	// �ړ��O�̍��W
	// ���W�̕␳�̍ۂɂ��̍��W���g�p����
	tnl::Vector3 beforePos_;


	// �ړ���
	float moveValue_ = 5;


	// �U���̑傫��
	// �R���X�g���N�^�ŏ�����
	// ��{�L�����N�^�[��1.5�{�Ƃ���(��)
	float attackSize_;

	// �_���[�W���󂯂��Ԃ��ǂ����̃t���O
	bool canTakeDamage_ = true;

	// ���G���Ԃ̃J�E���g
	float invincibleTimeCount_ = 0.0f;
	// ���G���Ԃ̍ő厞��
	// �_���[�W���󂯂��Ƃ��J�E���g�����̎��Ԃɂ���
	float invincibleTimeMax_ = 1.0f;

	// �_�Ŏ��Ԃ̃J�E���g
	float invincibleBlinkCount_ = 0.0f;
	// �_�ŊԊu
	float invincibleBlinkInterval_ = 0.15f;
	// �_�ł����邽�߂̕`�悷�邩�ǂ����̃t���O
	bool isDisplay_ = true;


	// �������Ă���U���̃��X�g
	std::list<std::shared_ptr<Attack>> activeAttackList_;

};