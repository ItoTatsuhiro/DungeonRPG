#pragma once

#include "../../dxlib_ext/dxlib_ext.h"


class TransformCamera : public dxe::Camera {
public:

	TransformCamera() {};
	TransformCamera(int screen_w, int screen_h) : dxe::Camera(screen_w, screen_h) {}

	// �X�V�p�̊֐�
	// �����FnewRot...�V�����J�����̌���(�v���C���[�̃J�����̌���)
	void update(tnl::Quaternion newRot);


	//-----------------------------------------------------------------------------------
	// �͈͂̐����p�̊֐�

	inline tnl::Vector3 up() {
		up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
		return up_;
	}
	inline tnl::Vector3 down() { return -up(); }

	inline tnl::Vector3 forward() override {
		target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
		return tnl::Vector3::Normalize(target_ - pos_);
	}
	inline tnl::Vector3 back() override { return -forward(); }
	inline tnl::Vector3 left() override { return tnl::Vector3::Cross(forward(), up()); }
	inline tnl::Vector3 right() override { return tnl::Vector3::Cross(up(), forward()); }

	//-----------------------------------------------------------------------------------
	// �J�����̌���
	// 1�l�̎��_�Ŏg�p���邽�߁A�v���C���[��rot_�����̂܂ܓ����\��
	tnl::Quaternion rot_;

	// �J�����̌���(rot_)���X�V���邽�߂̊֐�
	// ���t���[���Ăяo��
	void setRot_(tnl::Quaternion newRot) { rot_ = newRot; }
};