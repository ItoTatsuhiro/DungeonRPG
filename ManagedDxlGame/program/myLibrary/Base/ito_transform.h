#pragma once
#include "../library/tnl_vector3.h"
#include "../../library/tnl_quaternion.h"

namespace ito {

	// ���W�����I�u�W�F�N�g�Ɍp�����邽�߂�transform�N���X
	// �����Ă���ϐ�
	// pos_...���W(tnl::Vector3�^)
	// rotate_...
	class Transform {
	public :


		// �R���X�g���N�^
		// ���W�ipos_�j��������
		explicit Transform(tnl::Vector3 pos = {0, 0, 0}) : pos_(pos) {}
		virtual ~Transform(){}

		//---------------------------------------------------------------
		// �Q�b�^�[

		// ���W���擾���邽�߂̊֐�
		// �߂�l�Fpos_(���W)
		const tnl::Vector3& getPos_() const { return pos_; }

		// ��]��(2D�p)���擾����֐�
		// �߂�l�Frot2D_�i��]�ʁj
		const tnl::Vector3& getRot2D_() const { return rot2D_; }

		// ��]��(3D�p)���擾����֐�
		// �߂�l�Frot3D_(3D�p��]��)
		const tnl::Quaternion& getRot3D_() const { return rot3D_; }

		// �傫���̔{�����擾����֐�
		// �߂�l�Fscale_�i�{���j
		const tnl::Vector3& getScale_() const { return scale_; }

		//---------------------------------------------------------------
		// �Z�b�^�[

		// ���W��ݒ肷�邽�߂̊֐�
		// �����Fnew_pos(�V�������W�Atnl::Vector3�^)
		void setPos_(const tnl::Vector3& new_pos) { pos_ = new_pos; }

		// ��]��(2D�p)��ݒ肷�邽�߂̊֐�
		// �����Fnew_rotate(�V������]�ʁAtnl::Vector3�^)
		void setRot2D_(const tnl::Vector3& newRot2D) { rot2D_ = newRot2D; }

		// ��]��(3D�p)��ݒ肷�邽�߂̊֐�
		// �����Fnew_rotate(�V������]�ʁAtnl::Vector3�^)
		void setRot3D_(const tnl::Quaternion& newRotate3D) { rot3D_ = newRotate3D; }

		// �傫����ݒ肷�邽�߂̊֐�
		// �����Fnew_scale(�V�����傫���Atnl::Vector3�^)
		void setScale_(const tnl::Vector3& new_scale) { scale_ = new_scale; }

	protected:

		// Transform class���p�����Ă���N���X�̍��W
		// { x���W, y���W, z���W }
		// ��2D�ł�z���W�͎g�p���Ȃ�
		tnl::Vector3 pos_ = { 0, 0, 0 };

		// Transform class���p�����Ă���N���X�̉�]��(2D�p)
		// { ��]��, �Ȃ�, �Ȃ�}
		tnl::Vector3 rot2D_ = { 0, 0, 0 };

		// Transform class���p�����Ă���N���X�̉�]��(3D�p)
		// �g�p���@�F(��]�������)
		// rot3D_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }/* ��]�� */, tnl::ToRadian(2)/* �p�x(degree)�����W�A���ɕϊ� */)
		tnl::Quaternion rot3D_;

		// Transform class���p�����Ă���N���X�̑傫���̔{��
		// { x�����̔{��, y�����̔{��, z�����̔{�� }
		tnl::Vector3 scale_ = { 1, 1, 1 };

	};

}