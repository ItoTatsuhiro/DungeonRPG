#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include <list>


#include "../../base/ObjectBlockBase.h"

class Floor : public ObjectBlockBase {
public:
	// 壁クラスのコンストラクタ
	// 引数：オブジェクトの座標
	Floor(float gridSize, tnl::Vector3 pos);
	// 壁クラスのデストラクタ
	~Floor();

	// 毎フレームの処理
	void update(float delta_time) {};
	// 描画の処理
	void draw(std::shared_ptr<dxe::Camera> camera);



private:

	// 床を構成するオブジェクトを生成する関数
	void CreateObj();


	std::shared_ptr<dxe::Texture> floorTexture_ = nullptr;


	// 床を構成するオブジェクトのリスト
	std::list<std::shared_ptr<ito::Object3D>> floorObjList_;



};