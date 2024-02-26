#pragma once
#include "ito_transform.h"


// 画像用のクラス
class Graphic : public ito::Transform{
public :

	Graphic(tnl::Vector3 pos, int hdl, int width, int height);

	virtual ~Graphic() {};

	inline const int get_hdl_() const { return hdl_; }

	inline const int get_width_() const { return width_; }

	inline const int get_height_() const { return height_; }

protected :
	// 画像ハンドル
	int hdl_ = 0;
	// 画像の横幅
	int width_ = 0;
	// 画像の縦幅
	int height_ = 0;

};