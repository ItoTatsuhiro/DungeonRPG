#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <vector>

#include "../map/Stage.h"

class ScenePlay final: public ito::SceneBase {
public :
	// コンストラクタ
	ScenePlay();
	// デストラクタ
	~ScenePlay();

	void update(float delta_time);

	void draw();


private :

	// ScenePlay用のカメラ
	std::shared_ptr<dxe::Camera> camera_;

	// ステージを管理するクラス
	std::shared_ptr<Stage> stage_ = nullptr;



	// 壁のオブジェクト
	std::shared_ptr< ito::Object3D > wall_ = nullptr;
	// 床のオブジェクト
	std::shared_ptr< ito::Object3D > floor_ = nullptr;

};
