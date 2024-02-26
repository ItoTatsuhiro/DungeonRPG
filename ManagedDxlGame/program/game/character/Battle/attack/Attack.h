#pragma once
#include "../../../../dxlib_ext/dxlib_ext.h"
#include "../../../other/Enum.h"
#include "../../../base/SpriteObjectBase.h"

class Attack : public SpriteObjectBase {
public :

	// コンストラクタ
	// 引数：座標、大きさ、ファイル名、正面の方向
	Attack(tnl::Vector3 pos, float size, std::string fileName, Enum::Dir4 front);
	// デストラクタ
	~Attack();
	// 更新用の関数
	void update(float delta_time) override;
	// 描画用の関数
	void draw( std::shared_ptr<dxe::Camera> camera) override;

protected :



};
