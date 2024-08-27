#pragma once

#include "../../../../dxlib_ext/dxlib_ext.h"
#include "AttackBase.h"
#include "../../other/CharacterTypeEnum.h"


// �ʏ�̍U���̃N���X
// �ړ����̓���ȏ����͍s��Ȃ�
// �����͂قڂق�attackBase�N���X�̓��e
class Attack : public AttackBase {
public :

	// �R���X�g���N�^
	// �����F���W�A�傫���A�t�@�C�����A���ʂ̕����A�U���̃L�����N�^�[�����A�_���[�W
	Attack(const tnl::Vector3& pos, float size, std::string fileName, Enum::eDir4 front, eCharaType charaType, float damage = 1.0f );
	// �f�X�g���N�^
	virtual ~Attack();
	// �X�V�p�̊֐�
	virtual void update(float delta_time) override;
	// �`��p�̊֐�
	virtual void draw(const std::shared_ptr<dxe::Camera>& camera) override;



protected :



};
