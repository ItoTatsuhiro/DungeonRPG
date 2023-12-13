#include "ObjectManager.h"

// コンストラクタ
ObjectManager::ObjectManager() {

}

// デストラクタ
ObjectManager::~ObjectManager() {

}

// ObjectManagerをインスタンス化する用の関数
// ObjectManagerはこの関数を通して取得する
ObjectManager* ObjectManager::GetInstance() {
	static ObjectManager* instance = nullptr;

	if (instance == nullptr) {
		instance = new ObjectManager;
	}

	return instance;
}


// Boxのメッシュを持つオブジェクトのクローンを作成する関数
// 同名のオリジナルが作成されていればクローンを返し、
// 作成されていなければ作成してからクローンを返す
// 引数：size...Boxの大きさ, name...オブジェクト名
std::shared_ptr<ito::Object3D> ObjectManager::createBox(float size, std::string name) {

	// 同名のオリジナルオブジェクトを探す
	auto it = originObjList_.find(name);

	// 保存されていた場合、それのクローンを持つオブジェクトを作成し、returnする
	if (it != originObjList_.end()) {
		std::shared_ptr<ito::Object3D> boxObj = std::make_shared< ito::Object3D >();
		boxObj->set_mesh_(originObjList_[name]->get_mesh_()->createClone());
		return boxObj;
	}

	// 保存されていなかった場合、オリジナルのオブジェクトを作成する
	std::shared_ptr<ito::Object3D> boxObj = std::make_shared< ito::Object3D >();
	boxObj->set_mesh_(dxe::Mesh::CreateBoxMV(size));
	originObjList_.insert(std::make_pair(name, boxObj));

	// オリジナルのクローンのメッシュを持つオブジェクトを作成する
	std::shared_ptr<ito::Object3D> boxObj_clone = std::make_shared< ito::Object3D >();
	boxObj_clone->set_mesh_(boxObj->get_mesh_()->createClone());

	// 作成したオブジェクトを返す
	return boxObj_clone;

}


// Planeのメッシュを持つオブジェクトのオリジナルを作成する関数
// 同名のオリジナルが作成されていればクローンを返し、
// 作成されていなければ作成してからクローンを返す
// 引数：size...Planeの大きさ(z方向は不使用), name...オブジェクト名
std::shared_ptr<ito::Object3D> ObjectManager::createPlane(tnl::Vector3 size, std::string name) {

	// 同名のオリジナルオブジェクトを探す
	auto it = originObjList_.find(name);

	// 保存されていた場合、それのクローンを持つオブジェクトを作成し、returnする
	if (it != originObjList_.end()) {
		std::shared_ptr<ito::Object3D> planeObj = std::make_shared< ito::Object3D >();
		planeObj->set_mesh_(originObjList_[name]->get_mesh_()->createClone());
		return planeObj;
	}

	// 保存されていなかった場合、オリジナルのオブジェクトを作成する
	std::shared_ptr<ito::Object3D> planeObj = std::make_shared< ito::Object3D >();
	planeObj->set_mesh_(dxe::Mesh::CreatePlaneMV(size));
	originObjList_.insert(std::make_pair(name, planeObj));

	// オリジナルのクローンのメッシュを持つオブジェクトを作成する
	std::shared_ptr<ito::Object3D> planeObj_clone = std::make_shared< ito::Object3D >();
	planeObj_clone->set_mesh_(planeObj->get_mesh_()->createClone());

	// 作成したオブジェクトを返す
	return planeObj_clone;

}
