#pragma once

#include "../../dxlib_ext/dxlib_ext.h"


class TransformCamera : public dxe::Camera {
public:

	TransformCamera() {};
	TransformCamera(int screen_w, int screen_h) : dxe::Camera(screen_w, screen_h) {}

	// 更新用の関数
	// 引数：newRot...新しいカメラの向き(プレイヤーのカメラの向き)
	void update(tnl::Quaternion newRot);


	//-----------------------------------------------------------------------------------
	// 範囲の制限用の関数

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
	// カメラの向き
	// 1人称視点で使用するため、プレイヤーのrot_をそのまま入れる予定
	tnl::Quaternion rot_;

	// カメラの向き(rot_)を更新するための関数
	// 毎フレーム呼び出す
	void setRot_(tnl::Quaternion newRot) { rot_ = newRot; }
};