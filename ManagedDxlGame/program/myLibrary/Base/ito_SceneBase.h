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

		
	};

}