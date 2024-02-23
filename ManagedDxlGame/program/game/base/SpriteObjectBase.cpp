#include "SpriteObjectBase.h"
#include "../manager/ObjectManager.h"

// �R���X�g���N�^
// �����FstartPos...�J�n�ʒu, meshSize...�����蔻���Box�̑傫��, objName...���̃I�u�W�F�N�g�̖��O
SpriteObjectBase::SpriteObjectBase(tnl::Vector3 startPos, float meshSize, std::string objName) : meshSize_(meshSize), objName_(objName){

	// hitBox + �傫���Ŗ��O��t����
	std::string hitBoxName = objName + "hitBox";
	// �����蔻��p�̃��b�V������
	hitBox_ = ObjectManager::GetInstance()->createCube(meshSize_, hitBoxName);


}

// �f�X�g���N�^
SpriteObjectBase::~SpriteObjectBase() {



}


// spriteObjArray_�̒��g�𐶐�����֐�
// �����FtextureFileName...�\��t����e�N�X�`���̃t�@�C����
void SpriteObjectBase::CreateSpriteObjArray(std::string textureFileName) {

	// �e�N�X�`���֘A�ǂݍ���
	texture_ = ito::ResourceManager::GetInstance()->loadTexture(textureFileName);
	textureCutNum_ = ito::ResourceManager::GetInstance()->getTextureCutNum(textureFileName);

	// �e�N�X�`���̈���̑傫�����v�Z
	float sizeU = 1.0 / textureCutNum_.x;
	float sizeV = 1.0 / textureCutNum_.y;

	// �f�o�b�O�p�\��
	tnl::DebugTrace("sizeU = %f, sizeV = %f\n", sizeU, sizeV);

	// �e�N�X�`����\��t����p�̃��b�V���𐶐�
	for (int v = 0; v < textureCutNum_.y; ++v) {

		std::vector<std::shared_ptr<ito::Object3D>> objArray;

		for (int u = 0; u < textureCutNum_.x; ++u) {

			std::string objName = objName_ + std::to_string(u) + std::to_string(v);

			std::shared_ptr<ito::Object3D> playerObj
				= ObjectManager::GetInstance()->createPlane(tnl::Vector3{ meshSize_, meshSize_, meshSize_ }, objName, { u * sizeU, v * sizeV, 0 }, { (u + 1) * sizeU, (v + 1) * sizeV, 0 });

			// �f�o�b�O�p�\��
			tnl::DebugTrace(" (%d, %d) = �O(%f, %f), ��(%f, %f)\n", u, v, u * sizeU, v * sizeV, (u + 1) * sizeU, (v + 1) * sizeV);


			// �\���ݒ��ύX
			playerObj->get_mesh_()->setBlendMode(DX_BLENDMODE_ALPHA);
			playerObj->get_mesh_()->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			playerObj->get_mesh_()->setCullingMode(DX_CULLING_RIGHT);

			// �e�N�X�`���̓\��t��
			playerObj->get_mesh_()->setTexture(texture_);

			objArray.emplace_back(playerObj);
		}
		spriteObjArray_.emplace_back(objArray);
	}

}