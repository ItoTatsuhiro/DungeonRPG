#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <vector>

#include "../map/Stage.h"
#include "../object/Player.h"
#include "../object/Enemy.h"
#include "../manager/TurnManager.h"
#include "../base/SubSceneBase.h"
#include "SubScene/DungeonSubScene.h"

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
	// 実行するサブシーン
	std::shared_ptr<SubSceneBase> nowSubScene_ = nullptr;
	// ダンジョンのシーン
	std::shared_ptr<DungeonSubScene> dungeonSubScene_ = nullptr;





};
