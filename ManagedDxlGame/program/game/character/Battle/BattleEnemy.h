#pragma once

#include "../other/BattleCharacterBase.h"

// �O���錾
// �U���̃N���X
class BattleActionBase;

// �o�g���V�[���ł̓G�L�����N�^�[�̃N���X
// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�I�u�W�F�N�g�̑傫��, std::string fileName...�\��t����e�N�X�`���̃p�X
class BattleEnemy : public BattleCharacterBase {
public :
	// �R���X�g���N�^
	// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�I�u�W�F�N�g�̑傫��, std::string fileName...�\��t����e�N�X�`���̃p�X
	// �ړ��O�̍��W�͊J�n�ʒu�ŏ�����
	// SpriteObjectBase�̈����������
	BattleEnemy(tnl::Vector3 startPos, float objSize, std::string fileName);

	// �f�X�g���N�^
	~BattleEnemy();

	// �X�V�p�̊֐�
	// �p����ł͂��̊֐���update���ŌĂяo�����ƁI
	void update(float delta_time) override;
	// �`��p�̊֐�
	void draw(std::shared_ptr<dxe::Camera> camera) override;


protected :

	//// �s�����\���̃t���O
	//bool canAction_ = true;



	// �ړ�����ڕW�n�_�̍��W
	tnl::Vector3 movePos_;


	//// �U���̑傫��
	//// �R���X�g���N�^�ŏ�����
	//float attackSize_;

	// �U���̎�ނ̃��X�g
	// �G�L�����N�^�[���s���s�������̃��X�g�ɓ���Ă������ƁI
	std::list< std::shared_ptr< BattleActionBase > > actionList_;

	// ���ݎ��s���̍s��
	// �s����I����ɂ��̕ϐ��ɑI�������s��������
	std::shared_ptr< BattleActionBase > nowAction_ = nullptr;

	// �s���̎�ސ�
	// ���s����s�������肷��ۂɎg�p����
	int actionNum_ = 0;

	// �V�[�P���X�����p�̕ϐ�
	tnl::Sequence<BattleEnemy> seq_ = tnl::Sequence<BattleEnemy>(this, &BattleEnemy::seqActDecade);

	// �s�������肷��V�[�P���X
	bool seqActDecade(const float delta_time);

	// �s�������s����V�[�P���X
	bool seqAct(const float delta_time);



};