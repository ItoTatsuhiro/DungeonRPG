#include "Wall.h"

#include "../../manager/ObjectManager.h"

Wall::Wall(float gridSize, tnl::Vector3 pos) : ObjectBlockBase(gridSize, pos) {

	CreateObj();
	canMove_ = false;
}

Wall::~Wall() {

}


void Wall::draw(std::shared_ptr<dxe::Camera> camera) {


	// 壁を構成する
	for (auto wallObj : wallObjList_) {
		wallObj->get_mesh_()->render(camera);
		
	}

}


void Wall::CreateObj() {


	//wallTexture_ = dxe::Texture::CreateFromFile("graphics/myGpc/kokeBrick_Box.png");

	wallTexture_ = ito::ResourceManager::GetInstance()->loadTexture("kokeBrick_Box.png");

	for (int h = 0; h < height_; ++h) {

		// 壁の1ブロック分のオブジェクト
		// これを高さ分積み重ねて使用する
		std::shared_ptr<ito::Object3D> wallObj
			= ObjectManager::GetInstance()->createCube(gridSize_, "wall");
		wallObj->get_mesh_()->setSampleFilterMode(DX_DRAWMODE_NEAREST);
		wallObj->get_mesh_()->setCullingMode(DX_CULLING_RIGHT);

		wallObj->get_mesh_()->setTexture(wallTexture_);

		// ブロックの座標を設定
		wallObj->get_mesh_()->pos_ = { pos_.x, pos_.y + h * gridSize_, pos_.z };

		wallObjList_.emplace_back(wallObj);

	}

}
