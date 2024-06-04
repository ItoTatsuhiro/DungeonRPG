#pragma once
#include "ito_transform.h"

namespace ito {

	// �摜�p�̃N���X
	class Graphic : public ito::Transform {
	public:

		// �R���X�g���N�^
		// �p�����Ă���Transform�̍��W�͑��΍��W�Ƃ��ėp����
		Graphic(int hdl, float sizeMag = 1, tnl::Vector3 pos = { 0, 0, 0 });

		virtual ~Graphic() {};

		// �`��p�̊֐�
		// �����FbasePos...�x�[�X�ƂȂ���W�B���̍��W�����ɂ��ĕ`�悷��
		void draw(tnl::Vector3 basePos );


		//-----------------------------------------------------------------------
		// �Q�b�^�[

		// �摜�n���h�����擾
		inline int getHdl() const { return hdl_; }

		// �摜�̑傫���̔{�����擾
		inline float getSizeMag() const { return sizeMag_; }

		//-----------------------------------------------------------------------
		// �Z�b�^�[

		// �摜�n���h�����Z�b�g����
		inline void setHdl(int hdl) { hdl_ = hdl; }

		// �摜�̑傫���̔{�����Z�b�g����
		inline void setSizeMag(float sizeMag) { sizeMag_ = sizeMag; }



	protected:
		// �摜�n���h��
		int hdl_ = 0;
		// �摜�̑傫���̔{��
		float sizeMag_ = 1.0f;

	};

}