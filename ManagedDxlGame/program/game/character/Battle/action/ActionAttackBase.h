#pragma once
#include "BattleActionBase.h"
#include "../../../other/Enum.h"




// �O���錾
class Attack;
class BattleCharacterBase;
class BattlePlayer;


// �U�����s���s���̃x�[�X�ƂȂ�N���X
// �U���̓����蔻��������A����Ɋւ��鏈�����s��
//
// ************************************************************
// �����L
// ����update�֐��ł͍U�����X�V���鏈���̂ݍs���Ă��邽�߁A
// �p����ł͍U���̏������s���ӏ��ōX�V���s�����ƁI
// ************************************************************
class ActionAttackBase : public BattleActionBase {
public :

	// �R���X�g���N�^
	// �����FactionCharacter ... �s�����s���L�����N�^�[, targetCharacter ... �U���Ώۂ̃L�����N�^�[ 
	ActionAttackBase(std::shared_ptr <BattleCharacterBase> actionCharacter, std::shared_ptr<std::list<std::shared_ptr< BattleCharacterBase >>> charaList);

	// �f�X�g���N�^
	virtual ~ActionAttackBase();


	//--------------------------------------------------------------------------
	// �p����̂��ꂼ��̊֐��ł��Ăяo��

	// �X�V�p�̊֐�
	// ************************************************************
	// �U���̏����̍X�V�̂ݍs���Ă��邽�߁A�p����ł�
	// �U���̏��������Ă���ӏ��ł��̊֐����X�V���邱�ƁI
	// ************************************************************
	void update(const float delta_time);

	// �`��p�̊֐�
	void draw(std::shared_ptr<dxe::Camera> camera);

	//--------------------------------------------------------------------------


	// �U���Ώۂ̃L�����N�^�[�����X�g������I�����鏈��
	// ���z�֐��Ƃ��Ă���̂ŁA�K�v�Ȍp����̃N���X�ł͍쐬���邱��
	virtual void SelectTargetCharacter() {};


	// �U���̃N���X���쐬����֐�
	// �p����̃N���X�ōU�����s���ۂɂ��̊֐��ōU���̃N���X���쐬����
	// ��������̂͒ʏ�̍U���N���X�Ȃ̂ŁA���̏������K�v�ȏꍇ�̓I�[�o�[���C�h���Ďg�p���邱��
	// �����F���W�A�傫���A�t�@�C�����A���ʂ̕����A�_���[�W
	virtual void MakeAttack(std::string fileName = "attackKari.png", tnl::Vector3 pos = {0, 0, 0}, 
							float attackSize = 50, Enum::eDir4 front = Enum::eDir4::UP, float damage = 1.0f);


protected :


	// �U���̃N���X
	std::weak_ptr< Attack > attack_;



	// �L�����N�^�[�̃��X�g
	// ���̒�����Ώۂ̃L�����N�^�[��I������
	std::weak_ptr<std::list<std::shared_ptr< BattleCharacterBase >>> charaList_;


	// �U���Ώۂ̃L�����N�^�[
	// �R���X�g���N�^�ŏ�����
	std::weak_ptr< BattleCharacterBase > targetCharacter_;

};
