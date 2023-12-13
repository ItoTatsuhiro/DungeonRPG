#pragma once
#include "../library/tnl_vector3.h"

namespace ito {

	// 座標を持つオブジェクトに継承するためのtransformクラス

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
		const tnl::Vector3& get_pos_() const { return pos_; }

		// 回転量を取得する関数
		// 戻り値：rotate_（回転量）
		const tnl::Vector3& get_rotate_() const { return rotate_; }

		// 大きさの倍率を取得する関数
		// 戻り値：scale_（倍率）
		const tnl::Vector3& get_scale_() const { return scale_; }

		
		//---------------------------------------------------------------
		// セッター

		// 座標を設定するための関数
		// 引数：new_pos(新しい座標、tnl::Vector3型)
		void set_pos_(const tnl::Vector3& new_pos) { pos_ = new_pos; }

		// 回転量を設定するための関数
		// 引数：new_rotate(新しい回転量、tnl::Vector3型)
		void set_rotate_(const tnl::Vector3& new_rotate) { rotate_ = new_rotate; }

		// 大きさを設定するための関数
		// 引数：new_scale(新しい大きさ、tnl::Vector3型)
		void set_scale_(const tnl::Vector3& new_scale) { scale_ = new_scale; }

	protected:

		// Transform classを継承しているクラスの座標
		// { x座標, y座標, z座標 }
		// ※2Dではz座標は使用しない
		tnl::Vector3 pos_ = { 0, 0, 0 };

		// Transform classを継承しているクラスの回転量
		// 2D：{ 回転量, なし, なし}
		// 3D：{ x方向の回転量, y方向の回転量, z方向の回転量 }
		tnl::Vector3 rotate_ = { 0, 0, 0 };

		// Transform classを継承しているクラスの大きさの倍率
		// { x方向の倍率, y方向の倍率, z方向の倍率 }
		tnl::Vector3 scale_ = { 1, 1, 1 };

	};

}