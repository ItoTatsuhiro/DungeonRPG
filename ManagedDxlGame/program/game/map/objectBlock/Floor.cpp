#include "Floor.h"

#include "../../manager/ObjectManager.h"


Floor::Floor(float gridSize, tnl::Vector3 pos) : ObjectBlockBase(gridSize, pos) {

	CreateObj();
	canMove_ = true;
}

Floor::~Floor() {

}


void Floor::draw(std::shared_ptr<dxe::Camera> camera) {

	// floorTexture_ = dxe::Texture::CreateFromFile("graphics/myGpc/floor_test.png");

	// �ǂ��\������
	for (auto floorObj : floorObjList_) {
		floorObj->get_mesh_()->render(camera);
	}

}


void Floor::CreateObj() {

	floorTexture_ = dxe::Texture::CreateFromFile("graphics/myGpc/tileStone_hibi.png");


	// �ǂ�1�u���b�N���̃I�u�W�F�N�g
	// ������������ςݏd�˂Ďg�p����
	std::shared_ptr<ito::Object3D> floorObj
		= ObjectManager::GetInstance()->createPlane(tnl::Vector3 (gridSize_), "floor");

	// �e�N�X�`���̌`����ύX
	floorObj->get_mesh_()->setSampleFilterMode(DX_DRAWMODE_NEAREST);
	floorObj->get_mesh_()->setTexture(floorTexture_);

	// �u���b�N�̍��W��ݒ�
	floorObj->get_mesh_()->pos_ = { pos_.x, pos_.y - gridSize_ / 2, pos_.z };

	floorObj->get_mesh_()->rot_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));

	floorObjList_.emplace_back(floorObj);

	

}
