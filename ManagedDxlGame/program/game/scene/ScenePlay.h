#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <vector>

#include "../map/Stage.h"
#include "../object/Player.h"
#include "../object/Enemy.h"

#include "../other/TransformCamera.h"


class ScenePlay final: public ito::SceneBase {
public :
	// コンストラクタ
	ScenePlay();
	// デストラクタ
	~ScenePlay();
	// 毎フレームの処理
	void update(float delta_time) override;
	// 描画の処理
	void draw() override;



private :

	// プレイヤー、エネミーを生成する関数
	void CreateCharacter();

	// 一人称のカメラ
	std::shared_ptr< TransformCamera > FPCamera_;


	// ステージを管理するクラス
	std::shared_ptr<Stage> stage_ = nullptr;

	// プレイヤーのクラス
	std::shared_ptr<Player> player_ = nullptr;

	// 敵キャラクターのクラス
	std::shared_ptr<Enemy> enemy_ = nullptr;


	// 1マスの縦横の大きさ
	float gridSize_ = 50;

	// 壁のオブジェクト
	std::shared_ptr< ito::Object3D > wall_ = nullptr;
	// 床のオブジェクト
	std::shared_ptr< ito::Object3D > floor_ = nullptr;

};
