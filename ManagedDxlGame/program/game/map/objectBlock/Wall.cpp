#include "Wall.h"

#include "../../manager/ObjectManager.h"


Wall::Wall(tnl::Vector3 pos) : ObjectBlockBase(pos) {

	CreateObj();

}

Wall::~Wall() {

}


void Wall::draw(std::shared_ptr<dxe::Camera> camera) {

	wallTexture_ = dxe::Texture::CreateFromFile("graphics/myGpc/wall_test.png");

	// 壁を構成する
	for (auto wallObj : wallObjList_) {
		wallObj->get_mesh_()->render(camera);
		
	}

}


void Wall::CreateObj() {

	// wallObj_ = ObjectManager::GetInstance()->createBox(size_.x, "wall");

	wallTexture_ = dxe::Texture::CreateFromFile("graphics/myGpc/wall_test.png");

	for (int h = 0; h < height_; ++h) {

		// 壁の1ブロック分のオブジェクト
		// これを高さ分積み重ねて使用する
		std::shared_ptr<ito::Object3D> wallObj
			= ObjectManager::GetInstance()->createBox(size_.x, "wall");

		wallObj->get_mesh_()->setTexture(wallTexture_);

		// ブロックの座標を設定
		wallObj->get_mesh_()->pos_ = { pos_.x, pos_.y + h * size_.y, pos_.z };

		wallObjList_.emplace_back(wallObj);

	}

}
