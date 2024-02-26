#pragma once
#include "../../../../dxlib_ext/dxlib_ext.h"
#include "../../../other/Enum.h"
#include "../../../base/SpriteObjectBase.h"

class Attack : public SpriteObjectBase {
public :

	// �R���X�g���N�^
	// �����F���W�A�傫���A�t�@�C�����A���ʂ̕���
	Attack(tnl::Vector3 pos, float size, std::string fileName, Enum::Dir4 front);
	// �f�X�g���N�^
	~Attack();
	// �X�V�p�̊֐�
	void update(float delta_time) override;
	// �`��p�̊֐�
	void draw( std::shared_ptr<dxe::Camera> camera) override;

protected :



};
