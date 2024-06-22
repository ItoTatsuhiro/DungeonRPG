#pragma once
#include "BattleActionBase.h"
#include "../../../other/Enum.h"

// �O���錾
class Attack;
class BattleCharacterBase;


// �U�����s���s���̃x�[�X�ƂȂ�N���X
// �U���̓����蔻��������A����Ɋւ��鏈�����s��
class ActionAttackBase : public BattleActionBase {
public :

	// �R���X�g���N�^
	// �����FactionCharacter ... �s�����s���L�����N�^�[, targetCharacter ... �U���Ώۂ̃L�����N�^�[ 
	ActionAttackBase(std::shared_ptr <BattleCharacterBase> actionCharacter, std::shared_ptr <BattleCharacterBase> targetCharacter);

	// �f�X�g���N�^
	virtual ~ActionAttackBase();


	//--------------------------------------------------------------------------
	// �p����̂��ꂼ��̊֐��ł��Ăяo��

	// �X�V�p�̊֐�
	void update(const float delta_time);

	// �`��p�̊֐�
	void draw(std::shared_ptr<dxe::Camera> camera);

	//--------------------------------------------------------------------------


	// �U���̃N���X���쐬����֐�
	// �p����̃N���X�ōU�����s���ۂɂ��̊֐��ōU���̃N���X���쐬����
	// �����F���W�A�傫���A�t�@�C�����A���ʂ̕����A�_���[�W
	void MakeAttack(tnl::Vector3 pos, float attackSize, std::string fileName, Enum::Dir4 front, float damage);


protected :

	// �U���̃N���X
	std::shared_ptr< Attack > attack_ = nullptr;

	// �U���Ώۂ̃L�����N�^�[
	// �R���X�g���N�^�ŏ�����
	std::shared_ptr< BattleCharacterBase > targetCharacter_;

};
