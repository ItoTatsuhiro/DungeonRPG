#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <vector>

#include "../map/Stage.h"
#include "../character/Dungeon/Player.h"
#include "../character/Dungeon/Enemy.h"
#include "../manager/TurnManager.h"
#include "../base/SubSceneBase.h"

#include "../other/TransformCamera.h"

// 前方宣言
class SubSceneManager;
class DungeonSubScene;
class BattleSubScene;

// 主にゲームのメインの部分の処理を実行するクラス
// 実際に動作を行うサブシーンを管理する役割を持つ
// サブシーン間でやり取りの必要なデータを保持する役割もある
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


	// サブシーンを管理する用のマネージャー
	// サブシーンはこちらに持たせる
	std::shared_ptr< SubSceneManager > subSceneManager_ = nullptr;



};
