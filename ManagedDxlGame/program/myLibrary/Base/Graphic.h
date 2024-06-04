#pragma once
#include "ito_transform.h"

namespace ito {

	// 画像用のクラス
	class Graphic : public ito::Transform {
	public:

		// コンストラクタ
		// 継承しているTransformの座標は相対座標として用いる
		Graphic(int hdl, float sizeMag = 1, tnl::Vector3 pos = { 0, 0, 0 });

		virtual ~Graphic() {};

		// 描画用の関数
		// 引数：basePos...ベースとなる座標。この座標を元にして描画する
		void draw(tnl::Vector3 basePos );


		//-----------------------------------------------------------------------
		// ゲッター

		// 画像ハンドルを取得
		inline int getHdl() const { return hdl_; }

		// 画像の大きさの倍率を取得
		inline float getSizeMag() const { return sizeMag_; }

		//-----------------------------------------------------------------------
		// セッター

		// 画像ハンドルをセットする
		inline void setHdl(int hdl) { hdl_ = hdl; }

		// 画像の大きさの倍率をセットする
		inline void setSizeMag(float sizeMag) { sizeMag_ = sizeMag; }



	protected:
		// 画像ハンドル
		int hdl_ = 0;
		// 画像の大きさの倍率
		float sizeMag_ = 1.0f;

	};

}