#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include <list>


#include "../../base/ObjectBlockBase.h"

class Wall : public ObjectBlockBase{
public :
	// コンストラクタ
	// 引数：オブジェクトの座標
	Wall(tnl::Vector3 pos);
	// デストラクタ
	~Wall();

	// 
	void update(float delta_time) {};

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