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

		
	};

}