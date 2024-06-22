#pragma once
#include "../../../../dxlib_ext/dxlib_ext.h"
#include "../../../other/Enum.h"
#include "../../../base/SpriteObjectBase.h"


// �U���̃N���X
// �����蔻��p�̃��b�V��������
class Attack : public SpriteObjectBase {
public :

	// �R���X�g���N�^
	// �����F���W�A�傫���A�t�@�C�����A���ʂ̕����A�_���[�W
	Attack(tnl::Vector3 pos, float size, std::string fileName, Enum::Dir4 front, float damage = 1.0f );
	// �f�X�g���N�^
	~Attack();
	// �X�V�p�̊֐�
	void update(float delta_time) override;
	// �`��p�̊֐�
	void draw( std::shared_ptr<dxe::Camera> camera) override;

	//-------------------------------------------------------------
	// �Q�b�^�[

	// �_���[�W�̐��l���擾����֐�
	inline float getDamage() const { return damage_; }

	// �Q�[���̏I����Ԃ��擾����֐�
	inline bool getIsEnd() const { return isEnd_; }



protected :

	// �_���[�W
	float damage_;

	// ���[�v���邩�ǂ���
	// ���[�v���Ȃ��ꍇ�̓A�j���[�V������1���[�v�Ŋ�{�폜����
	bool isLoop_;

	// �I�����Ă��邩�ǂ���
	// �f�t�H���g��false
	// �������I��������Ƃ��͂��̃t���O��true�ɂ���
	bool isEnd_;
	
};
