#include "ActionAttackBase.h"

#include "../attack/Attack.h"
#include "../../other/BattleCharacterBase.h"


// �R���X�g���N�^
// �����FactionCharacter ... �s�����s���L�����N�^�[, targetCharacter ... �U���Ώۂ̃L�����N�^�[ , attackSize...�U���̃T�C�Y
ActionAttackBase::ActionAttackBase(std::shared_ptr < BattleCharacterBase > actionCharacter, std::shared_ptr<std::list<std::shared_ptr< BattleCharacterBase >>> charaList)
	: BattleActionBase(actionCharacter), charaList_(charaList)
{



}


// �f�X�g���N�^
ActionAttackBase::~ActionAttackBase() {

}


// �X�V�p�̊֐�
// ************************************************************
// �U���̏����̍X�V�̂ݍs���Ă��邽�߁A�p����ł�
// �U���̏��������Ă���ӏ��ł��̊֐����X�V���邱�ƁI
// ************************************************************
void ActionAttackBase::update(const float delta_time) {



	//// �U���̍X�V
	//attack_->update(delta_time);


}


// �`��p�̊֐�
void ActionAttackBase::draw(std::shared_ptr<dxe::Camera> camera) {

	//// attack_�����݂��Ă��Ȃ��Ƃ��������Ȃ�
	//if (attack_ == nullptr) {
	//	return;
	//}
	//// attack�̏������I�����Ă���Ƃ����������s��Ȃ�
	//if (attack_->getIsEnd()) {
	//	return;
	//}

	//// �U���̕`��
	//attack_->draw(camera);

}



// �U���̃N���X���쐬����֐�
// �p����̃N���X�ōU�����s���ۂɂ��̊֐��ōU���̃N���X���쐬����
// �����F���W�A�傫���A�t�@�C�����A���ʂ̕����i�f�t�H���g�ŏ�j�A�_���[�W�i�f�t�H���g��1�j
void ActionAttackBase::MakeAttack(std::string fileName, tnl::Vector3 pos, float attackSize, Enum::eDir4 front, float damage) {


	auto actionCharacter = actionCharacter_.lock();

	if (!actionCharacter) {
		return;
	}


	// �U���̃N���X�̍쐬
	std::shared_ptr<Attack> attack = std::shared_ptr<Attack>(new Attack(pos, attackSize, fileName, front, eCharaType::ENEMY,damage));
	// ��Ԃ�false�ɂ���
	attack->setIsActive(false);

	// �����o�[�ϐ��Ƃ��ď������Ă���U���̃N���X�ɐݒ�
	attack_ = attack;

	actionCharacter->addActiveAttack(attack);

	

}
