#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <vector>


class ScenePlay final: public ito::SceneBase {
public :
	// コンストラクタ
	ScenePlay();
	// デストラクタ
	~ScenePlay() override;

	void update(float delta_time);

	void draw();


private :


	// マップ用の2重vector
	std::vector<std::vector<int>> map;

	std::vector<std::vector<>>

	// 壁のオブジェクト
	std::shared_ptr< ito::Object3D > wall_ = nullptr;
	// 床のオブジェクト
	std::shared_ptr< ito::Object3D > floor_ = nullptr;

};
