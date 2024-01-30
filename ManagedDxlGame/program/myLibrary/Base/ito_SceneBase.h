#pragma once
#include "Graphic.h"

// �V�[���x�[�X�N���X
// �Q�[�����Ɏ��s�����V�[���̃N���X�̐e�N���X�Ƃ��Ďg�p����

namespace ito {

	class SceneBase {
	public:

		virtual ~SceneBase() {};

		virtual void update(float delta_time) = 0 {};
		virtual void draw() = 0 {};

		// �I�u�W�F�N�g�ƃn���h���p�̃��X�g���擾����֐�
		std::list<std::shared_ptr<Graphic>> get_gpcObj_()
			{ return gpcObj_; }

	protected :

		// �`��ʒu�ƃn���h�����܂Ƃ߂��I�u�W�F�N�g�p�̃��X�g
		std::list<std::shared_ptr<Graphic>> gpcObj_;

		
	};

}