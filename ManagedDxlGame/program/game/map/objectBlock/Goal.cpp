#include "Goal.h"

#include "../../manager/ObjectManager.h"

Goal::Goal(float gridSize, tnl::Vector3 pos) : ObjectBlockBase(gridSize, pos) {

	CreateObj();
	canMove_ = true;
}

Goal::~Goal() {

}


void Goal::draw(std::shared_ptr<dxe::Camera> camera) {


	// �ǂ��\������
	for (auto goalObj : goalObjList_) {
		goalObj->get_mesh_()->render(camera);

	}

}


void Goal::CreateObj() {


	goalTexture_ = ito::ResourceManager::GetInstance()->loadTexture("GoalTexture.png");

	for (int h = 0; h < height_; ++h) {

		// �ǂ�1�u���b�N���̃I�u�W�F�N�g
		// ������������ςݏd�˂Ďg�p����
		std::shared_ptr<ito::Object3D> goalObj
			= ObjectManager::GetInstance()->createCube(gridSize_, "goal");
		goalObj->get_mesh_()->setBlendMode(DX_BLENDMODE_ALPHA);
		goalObj->get_mesh_()->setSampleFilterMode(DX_DRAWMODE_NEAREST);
		goalObj->get_mesh_()->setCullingMode(DX_CULLING_RIGHT);

		goalObj->get_mesh_()->setTexture(goalTexture_);

		// �u���b�N�̍��W��ݒ�
		goalObj->get_mesh_()->pos_ = { pos_.x, pos_.y + h * gridSize_, pos_.z };

		goalObjList_.emplace_back(goalObj);

	}

}
