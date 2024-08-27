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
	// charaList...�o�g���V�[���ɑ��݂��Ă���L�����N�^�[�̃��X�g
	// �ړ��O�̍��W�͊J�n�ʒu�ŏ�����
	// SpriteObjectBase�̈����������
	BattleEnemy(tnl::Vector3 startPos, float objSize, std::string fileName, std::shared_ptr<std::list<std::shared_ptr< BattleCharacterBase >>> charaList);

	// �f�X�g���N�^
	~BattleEnemy();

	// �X�V�p�̊֐�
	// �p����ł͂��̊֐���update���ŌĂяo�����ƁI
	virtual void update(const float delta_time) override;
	// �`��p�̊֐�
	virtual void draw(const std::shared_ptr<dxe::Camera>& camera) override;




protected :

	

	// �ړ�����ڕW�n�_�̍��W
	tnl::Vector3 movePos_;


	
	
	// �L�����N�^�[�̃��X�g
	// ���������ۂɃR���X�g���N�^�Ńo�g���V�[������擾���Ă���
	std::weak_ptr<std::list<std::shared_ptr< BattleCharacterBase >>> charaList_;

	// �s���̃^�[�Q�b�g�̃L�����N�^�[
	// charaList_����Ώۂ�I�����Ē��ɓ����
	std::weak_ptr< BattleCharacterBase > targetCharacter_;



	// �s���̎�ނ̃��X�g
	// �G�L�����N�^�[���s���s�������̃��X�g�ɓ���Ă������ƁI
	std::list< std::shared_ptr< BattleActionBase > > actionList_;

	// ���ݎ��s���̍s��
	// �s����I����ɂ��̕ϐ��ɑI�������s��������
	std::shared_ptr< BattleActionBase > nowAction_ = nullptr;



	// �V�[�P���X�����p�̕ϐ�
	tnl::Sequence<BattleEnemy> seq_ = tnl::Sequence<BattleEnemy>(this, &BattleEnemy::seqActDecade);

	// �s�������肷��V�[�P���X
	bool seqActDecade(const float delta_time);

	// �s�������s����V�[�P���X
	bool seqAct(const float delta_time);



};