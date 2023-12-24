#pragma once
#include "../../dxlib_ext/dxlib_ext.h"



// オブジェクトの元になるクラス
// 床、壁等のオブジェクトを作成する際はこれを継承する
class ObjectBlockBase : public ito::Transform {
public :
	// コンストラクタ
	explicit ObjectBlockBase( tnl::Vector3 pos = {0, 0, 0}) : ito::Transform(pos){}
	// デストラクタ
	virtual ~ObjectBlockBase(){}

	// アップデート関数
	virtual void update(float delta_time) {};
	// 描画関数
	virtual void draw(std::shared_ptr<dxe::Camera> camera) {}

	// 構成するオブジェクトを生成する関数
	// これを仮想関数として回すことで、一気にオブジェクトを作成可能
	virtual void CreateObj(){}

protected :
	// 大きさの変数
	// 初期値が基本の大きさとなる
	// { x方向の大きさ, y方向の大きさ, z方向の大きさ }
	tnl::Vector3 size_ = { 50, 50, 50 };

	// 天井までの高さ
	int height_ = 3;

};

