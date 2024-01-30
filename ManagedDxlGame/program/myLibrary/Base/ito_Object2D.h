#pragma once
#include "ito_transform.h"


namespace ito {

	// �I�u�W�F�N�g2D�N���X
	// �Q�[������2D�̃I�u�W�F�N�g�Ɍp�����Ďg�p����
	// ���������ۂɁA���W���L��Έ����œ����
	class Object2D :public ito::Transform {
	public :
		// �R���X�g���N�^
		// �����F�I�u�W�F�N�g�̍��W
		explicit Object2D(tnl::Vector3 pos = {0, 0, 0}) : Transform(pos) {}
		// �f�X�g���N�^
		virtual ~Object2D(){}
		

	protected:
		// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ������t���O
		bool isActive_ = true;


	public:
		// ���z�֐��F�I�u�W�F�N�g�̍X�V�����p�֐�
		virtual void update(float delta_time) {}
		// ���z�֐��F�I�u�W�F�N�g�̕`�揈���p�֐�
		virtual void draw() {}

		// �Q�b�^�[...�I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾����֐�
		// �߂�l...isActive_(bool�^�A�I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�����)
		bool get_isActive_() const { return isActive_; }

		// �Z�b�^�[...�I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�ύX����֐�
		// �����F�ύX��̃I�u�W�F�N�g�̃A�N�e�B�u���
		void set_isActive_(bool isActive) { isActive_ = isActive; }


	};
}