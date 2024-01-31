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

	// 壁を構成する
	for (auto floorObj : floorObjList_) {
		floorObj->get_mesh_()->render(camera);
	}

}


void Floor::CreateObj() {

	floorTexture_ = dxe::Texture::CreateFromFile("graphics/myGpc/tileStone_hibi.png");


	// 壁の1ブロック分のオブジェクト
	// これを高さ分積み重ねて使用する
	std::shared_ptr<ito::Object3D> floorObj
		= ObjectManager::GetInstance()->createPlane(tnl::Vector3 (gridSize_), "floor");

	// テクスチャの形式を変更
	floorObj->get_mesh_()->setSampleFilterMode(DX_DRAWMODE_NEAREST);
	floorObj->get_mesh_()->setTexture(floorTexture_);

	// ブロックの座標を設定
	floorObj->get_mesh_()->pos_ = { pos_.x, pos_.y - gridSize_ / 2, pos_.z };

	floorObj->get_mesh_()->rot_ *= tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));

	floorObjList_.emplace_back(floorObj);

	

}
