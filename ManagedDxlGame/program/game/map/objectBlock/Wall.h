#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include <list>

#include "../../base/ObjectBlockBase.h"

class Wall : public ObjectBlockBase{
public :
	// 壁クラスのコンストラクタ
	// 引数：オブジェクトの座標
	Wall(float gridSize, tnl::Vector3 pos);
	// 壁クラスのデストラクタ
	~Wall();

	// 毎フレームの処理
	void update(float delta_time) {};
	// 描画の処理
	void draw(std::shared_ptr<dxe::Camera> camera);



private :

	// 壁を構成するオブジェクトを生成する関数
	void CreateObj();


	std::shared_ptr<dxe::Texture> wallTexture_ = nullptr;


	// 壁を構成するオブジェクトのリスト
	std::list<std::shared_ptr<ito::Object3D>> wallObjList_;

	// 壁の1ブロック分のオブジェクト
	// これを高さ分積み重ねて使用する
	// std::shared_ptr<ito::Object3D> wallObj_ = nullptr;



};