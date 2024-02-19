#pragma once
#include "../../../../dxlib_ext/dxlib_ext.h"
#include "../../../other/Enum.h"

class Attack : public ito::Object3D {
public :

	// �R���X�g���N�^
	// �����F���W�A�傫���A�t�@�C�����A���ʂ̕���
	Attack(tnl::Vector3 pos, float size, std::string fileName, Enum::Dir4 front);
	// �f�X�g���N�^
	~Attack();
	// �X�V�p�̊֐�
	void update(float delta_time) override;
	// �`��p�̊֐�
	void draw( std::shared_ptr<dxe::Camera> camera) override;

private :

	// �����蔻��p
	std::shared_ptr<ito::Object3D> hitBox_;

	// �`�悷��I�u�W�F�N�g��vector
	std::vector<std::vector<std::shared_ptr<ito::Object3D>>> displayObjArray_;
	// �`�悷��I�u�W�F�N�g
	tnl::Vector2i displayObj_ = { 0, 0 };
	// �e�N�X�`��
	std::shared_ptr<dxe::Texture> texture_;
	// �e�N�X�`���̕�����
	// �R���X�g���N�^�œǂݍ���
	tnl::Vector2i textureCutNum_ = { 0, 0 };
	
	// �A�j���[�V�����p�̃��b�V����؂�ւ��鎞��
	const float animChangeTime_ = 0.15;
	// ���݂̃A�j���[�V�������Đ����Ă��鎞��
	// �ړ����̃A�j���[�V�����͎~�߂��ۂ�0�Ƀ��Z�b�g����
	float animChangeCount_ = 0;

	// ���ʂ̕���
	// �R���X�g���N�^�ŏ�����
	// LEFT��RIGHT�����邱��
	Enum::Dir4 frontDir_ = Enum::Dir4::LEFT;

};
