#pragma once
#include "../library/tnl_vector3.h"
#include "../../library/tnl_quaternion.h"

namespace ito {

	// 座標を持つオブジェクトに継承するためのtransformクラス
	// 持っている変数
	// pos_...座標(tnl::Vector3型)
	// rotate_...
	class Transform {
	public :


		// コンストラクタ
		// 座標（pos_）を初期化
		explicit Transform(tnl::Vector3 pos = {0, 0, 0}) : pos_(pos) {}
		virtual ~Transform(){}

		//---------------------------------------------------------------
		// ゲッター

		// 座標を取得するための関数
		// 戻り値：pos_(座標)
		const tnl::Vector3& getPos_() const { return pos_; }

		// 回転量(2D用)を取得する関数
		// 戻り値：rot2D_（回転量）
		const tnl::Vector3& getRot2D_() const { return rot2D_; }

		// 回転量(3D用)を取得する関数
		// 戻り値：rot3D_(3D用回転量)
		const tnl::Quaternion& getRot3D_() const { return rot3D_; }

		// 大きさの倍率を取得する関数
		// 戻り値：scale_（倍率）
		const tnl::Vector3& getScale_() const { return scale_; }

		//---------------------------------------------------------------
		// セッター

		// 座標を設定するための関数
		// 引数：new_pos(新しい座標、tnl::Vector3型)
		void setPos_(const tnl::Vector3& new_pos) { pos_ = new_pos; }

		// 回転量(2D用)を設定するための関数
		// 引数：new_rotate(新しい回転量、tnl::Vector3型)
		void setRot2D_(const tnl::Vector3& newRot2D) { rot2D_ = newRot2D; }

		// 回転量(3D用)を設定するための関数
		// 引数：new_rotate(新しい回転量、tnl::Vector3型)
		void setRot3D_(const tnl::Quaternion& newRotate3D) { rot3D_ = newRotate3D; }

		// 大きさを設定するための関数
		// 引数：new_scale(新しい大きさ、tnl::Vector3型)
		void setScale_(const tnl::Vector3& new_scale) { scale_ = new_scale; }

	protected:

		// Transform classを継承しているクラスの座標
		// { x座標, y座標, z座標 }
		// ※2Dではz座標は使用しない
		tnl::Vector3 pos_ = { 0, 0, 0 };

		// Transform classを継承しているクラスの回転量(2D用)
		// { 回転量, なし, なし}
		tnl::Vector3 rot2D_ = { 0, 0, 0 };

		// Transform classを継承しているクラスの回転量(3D用)
		// 使用方法：(回転させる際)
		// rot3D_ *= tnl::Quaternion::RotationAxis({ 0, 1, 0 }/* 回転軸 */, tnl::ToRadian(2)/* 角度(degree)をラジアンに変換 */)
		tnl::Quaternion rot3D_;

		// Transform classを継承しているクラスの大きさの倍率
		// { x方向の倍率, y方向の倍率, z方向の倍率 }
		tnl::Vector3 scale_ = { 1, 1, 1 };

	};

}