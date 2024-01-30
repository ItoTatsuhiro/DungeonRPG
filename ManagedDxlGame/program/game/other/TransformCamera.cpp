#include "TransformCamera.h"

void TransformCamera::update(tnl::Quaternion newRot) {

	// 姿勢パラメータからターゲット座標とアッパーベクトルを計算

	target_ = pos_ + tnl::Vector3::TransformCoord({ 0, 0, 1 }, rot_);
	up_ = tnl::Vector3::TransformCoord({ 0, 1, 0 }, rot_);
	dxe::Camera::update();

	setRot_(newRot);
}
