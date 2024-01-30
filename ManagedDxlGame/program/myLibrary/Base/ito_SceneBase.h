#pragma once
#include "Graphic.h"

// シーンベースクラス
// ゲーム中に実行されるシーンのクラスの親クラスとして使用する

namespace ito {

	class SceneBase {
	public:

		virtual ~SceneBase() {};

		virtual void update(float delta_time) = 0 {};
		virtual void draw() = 0 {};

		// オブジェクトとハンドル用のリストを取得する関数
		std::list<std::shared_ptr<Graphic>> get_gpcObj_()
			{ return gpcObj_; }

	protected :

		// 描画位置とハンドルをまとめたオブジェクト用のリスト
		std::list<std::shared_ptr<Graphic>> gpcObj_;

		
	};

}