#include "BattleCharacterBase.h"

// �R���X�g���N�^
// �����FstartPos...�J�n�ʒu, objSize...�쐬����L�����N�^�[�̑傫��, objName...���O
// �ړ��O�̍��W�͊J�n�ʒu�ŏ�����
BattleCharacterBase::BattleCharacterBase(tnl::Vector3 startPos, float objSize, std::string objName)
	: beforePos_(startPos), SpriteObjectBase(startPos, objSize, objName) {


	// SpriteObjectBase�N���X�̊֐�
	// �e�N�X�`����\������p��plane�̔z����쐬����
	CreateSpriteObjArray("travellerAnim.png");


	displayObj_ = tnl::Vector2i(1, textureCutNum_.y - 2);


	return;
}

// �f�X�g���N�^
BattleCharacterBase::~BattleCharacterBase() {

}

// �X�V�p�̊֐�
// *********************************************************************
// �p�����update�֐��ł��A���̃N���X��update�֐����Ăяo������!!
// *********************************************************************
void BattleCharacterBase::update(float delta_time) {

	// �U���̏��������s
	auto it = attackList_.begin();
	while (it != attackList_.end()) {
		(*it)->update(delta_time);

		if (!((*it)->getIsActive())) {

			it = attackList_.erase(it);

		}
		else {
			++it;
		}
	}
}


// �`��p�̊֐�
// *********************************************************************
// �p�����draw�֐��ł��A���̃N���X��draw�֐����Ăяo������!!
// *********************************************************************
void BattleCharacterBase::draw(std::shared_ptr<dxe::Camera> camera ) {

	SpriteObjectBase::draw(camera);

	// �U���̃��b�V����`��
	auto it = attackList_.begin();
	while (it != attackList_.end()) {
		(*it)->draw(camera);

		++it;
	}

	return;

}