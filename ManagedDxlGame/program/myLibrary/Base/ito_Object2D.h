#pragma once
#include "ito_transform.h"


namespace ito {

	// オブジェクト2Dクラス
	// ゲーム内の2Dのオブジェクトに継承して使用する
	// 生成した際に、座標が有れば引数で入れる
	class Object2D :public ito::Transform {
	public :
		// コンストラクタ
		// 引数：オブジェクトの座標
		explicit Object2D(tnl::Vector3 pos = {0, 0, 0}) : Transform(pos) {}
		// デストラクタ
		virtual ~Object2D(){}
		

	protected:
		// オブジェクトのアクティブ状態を示すフラグ
		bool isActive_ = true;


	public:
		// 仮想関数：オブジェクトの更新処理用関数
		virtual void update(float delta_time) {}
		// 仮想関数：オブジェクトの描画処理用関数
		virtual void draw() {}

		// ゲッター...オブジェクトのアクティブ状態を取得する関数
		// 戻り値...isActive_(bool型、オブジェクトのアクティブ状態を示す)
		bool get_isActive_() const { return isActive_; }

		// セッター...オブジェクトのアクティブ状態を変更する関数
		// 引数：変更後のオブジェクトのアクティブ状態
		void set_isActive_(bool isActive) { isActive_ = isActive; }


	};
}