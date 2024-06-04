#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include <list>

#include "../../base/ObjectBlockBase.h"

class Goal final : public ObjectBlockBase {
public:
	// 壁クラスのコンストラクタ
	// 引数：オブジェクトの座標
	Goal(float gridSize, tnl::Vector3 pos);
	// 壁クラスのデストラクタ
	~Goal();

	// 毎フレームの処理
	void update(float delta_time) {};
	// 描画の処理
	void draw(std::shared_ptr<dxe::Camera> camera);



private:

	// 壁を構成するオブジェクトを生成する関数
	void CreateObj();


	int displayObjNum_ = 0;

	std::shared_ptr<dxe::Texture> goalTexture_ = nullptr;


	// 壁を構成するオブジェクトのリスト
	std::list<std::shared_ptr<ito::Object3D>> goalObjList_;

};