#include "ActionAttackBase.h"

#include "../attack/Attack.h"
#include "../../other/BattleCharacterBase.h"


// �R���X�g���N�^
// �����FactionCharacter ... �s�����s���L�����N�^�[, targetCharacter ... �U���Ώۂ̃L�����N�^�[ , attackSize...�U���̃T�C�Y
ActionAttackBase::ActionAttackBase(std::shared_ptr < BattleCharacterBase > actionCharacter, std::shared_ptr < BattleCharacterBase > targetCharacter) 
	: BattleActionBase(actionCharacter), targetCharacter_(targetCharacter)
{



}


// �f�X�g���N�^
ActionAttackBase::~ActionAttackBase() {

}


// �X�V�p�̊֐�
void ActionAttackBase::update(const float delta_time) {


	if (attack_ != nullptr) {

		attack_->update(delta_time);

	}

}


// �`��p�̊֐�
void ActionAttackBase::draw(std::shared_ptr<dxe::Camera> camera) {


	if (attack_ != nullptr) {

		attack_->draw(camera);

	}

}



// �U���̃N���X���쐬����֐�
// �p����̃N���X�ōU�����s���ۂɂ��̊֐��ōU���̃N���X���쐬����
// �����F���W�A�傫���A�t�@�C�����A���ʂ̕����A�_���[�W
void ActionAttackBase::MakeAttack(tnl::Vector3 pos, float attackSize, std::string fileName, Enum::Dir4 front, float damage) {


	// �U���̃N���X�̍쐬
	attack_ = std::shared_ptr<Attack>(new Attack(pos, attackSize, fileName, front, damage));

}
