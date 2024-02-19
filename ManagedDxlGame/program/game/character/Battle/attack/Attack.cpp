#include "Attack.h"
#include "../../../manager/ObjectManager.h"



// �R���X�g���N�^
// �����F���W�A�傫���A�t�@�C�����A���ʂ̕���(LEFT��RIGHT)
// Object3D�̃��b�V���𓖂��蔻��p�̃��b�V���Ƃ��č쐬����
Attack::Attack(tnl::Vector3 pos, float size, std::string fileName, Enum::Dir4 front) : frontDir_(front) {

	// �����蔻����쐬
	hitBox_ = ObjectManager::GetInstance()->createCube(size, fileName);
	hitBox_->get_mesh_()->pos_ = pos;
	
	// �e�N�X�`���֌W�ǂݍ���
	texture_ = ito::ResourceManager::GetInstance()->loadTexture(fileName);
	textureCutNum_ = ito::ResourceManager::GetInstance()->getTextureCutNum(fileName);

	// �e�N�X�`���̈���̑傫�����v�Z
	float sizeU = 1.0 / textureCutNum_.x;
	float sizeV = 1.0 / textureCutNum_.y;


	// �e�N�X�`����\��t����p�̃��b�V���𐶐�
	for (int v = 0; v < textureCutNum_.y; ++v) {

		std::vector<std::shared_ptr<ito::Object3D>> objArray;

		for (int u = 0; u < textureCutNum_.x; ++u) {

			std::string objName = fileName + std::to_string(u) + std::to_string(v);

			std::shared_ptr<ito::Object3D> playerObj
				= ObjectManager::GetInstance()->createPlane(tnl::Vector3{ size, size, size }, objName, { u * sizeU, v * sizeV, 0 }, { (u + 1) * sizeU, (v + 1) * sizeV, 0 });


			// �\���ݒ��ύX
			playerObj->get_mesh_()->setBlendMode(DX_BLENDMODE_ALPHA);
			playerObj->get_mesh_()->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			playerObj->get_mesh_()->setCullingMode(DX_CULLING_RIGHT);

			// �e�N�X�`���̓\��t��
			playerObj->get_mesh_()->setTexture(texture_);

			objArray.emplace_back(playerObj);
		}
		displayObjArray_.emplace_back(objArray);
	}

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

void Attack::draw(std::shared_ptr<dxe::Camera> camera) {

	// ��\����Ԃ̎��ȉ��̕`��̏������s��Ȃ�
	if (!isActive_) { return; }

	// �\������摜�p�̃��b�V���̍��W�𓖂��蔻��p�̃��b�V���̈ʒu�ɍX�V
	displayObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->pos_ = hitBox_->get_mesh_()->pos_;

	displayObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->render(camera);

}


