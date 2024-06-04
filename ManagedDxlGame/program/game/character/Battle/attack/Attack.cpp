#include "Attack.h"
#include "../../../manager/ObjectManager.h"



// �R���X�g���N�^
// �����F���W�A�傫���A�t�@�C�����A���ʂ̕���(LEFT��RIGHT), �_���[�W
// Object3D�̃��b�V���𓖂��蔻��p�̃��b�V���Ƃ��č쐬����
Attack::Attack(tnl::Vector3 pos, float size, std::string fileName, Enum::Dir4 front, float damage)
	: SpriteObjectBase(pos, size, fileName) , damage_(damage)
{

	CreateSpriteObjArray(fileName);

	// �����蔻����쐬
	hitBox_ = ObjectManager::GetInstance()->createCube(size, fileName);
	hitBox_->get_mesh_()->pos_ = pos;
	

	displayObj_.y = (frontDir_ == Enum::Dir4::LEFT) ? 1 : 0;

}

// �f�X�g���N�^
Attack::~Attack() {

}


// �X�V�p�̊֐�
void Attack::update(float delta_time) {

	if (animChangeCount_ > animChangeTime_ / 3) {
		// ���̉摜�̃��b�V���ɐ؂�ւ�
		++displayObj_.x;
		// �\�����Ԃ�0�Ƀ��Z�b�g����
		animChangeCount_ = 0;

		// �U�����I������ۂɕ\�����Ȃ���Ԃɂ���
		if (displayObj_.x >= textureCutNum_.x) {

			isActive_ = false;

		}

	}
	else {
		animChangeCount_ += delta_time;
	}

}

// �`��p�̊֐�
void Attack::draw(std::shared_ptr<dxe::Camera> camera) {

	SpriteObjectBase::draw(camera);

}


