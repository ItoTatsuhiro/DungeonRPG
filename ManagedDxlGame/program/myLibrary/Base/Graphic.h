#pragma once
#include "ito_transform.h"



class Graphic : public ito::Transform{
public :

	Graphic(tnl::Vector3 pos, int hdl, int width, int height);

	const int get_hdl_() const { return hdl_; }

	const int get_width_() const { return width_; }

	const int get_height_() const { return height_; }

protected :
	// �摜�n���h��
	int hdl_ = 0;
	// �摜�̉���
	int width_ = 0;
	// �摜�̏c��
	int height_ = 0;

};