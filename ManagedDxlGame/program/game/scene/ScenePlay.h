#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <vector>

#include "../map/Stage.h"
#include "../character/Dungeon/Player.h"
#include "../character/Dungeon/Enemy.h"
#include "../manager/TurnManager.h"
#include "../base/SubSceneBase.h"

#include "../other/TransformCamera.h"


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

	// 一旦未使用
	// サブシーンを切り替える関数
	void ChangeSubScene( std::shared_ptr<SubSceneBase> nextSubScene );

	// ダンジョンのサブシーンに切り替え
	void ChangeSubSceneToDungeon();
	// バトルのサブシーンに切り替え
	void ChangeSubSceneToBattle();

	// サブシーンのゲッター
	// 上の関数で切り替える際に引数として使用

	std::shared_ptr<DungeonSubScene> getDungeonSubScene() { return dungeonSubScene_; }
	std::shared_ptr<BattleSubScene> getBattleSubScene() { return battleSubScene_; }

private :
	// 実行するサブシーン
	// この変数に入れているサブシーンを実行する
	std::shared_ptr<SubSceneBase> nowSubScene_ = nullptr;
	// ダンジョンのサブシーン
	std::shared_ptr<DungeonSubScene> dungeonSubScene_ = nullptr;
	// バトルのサブシーン
	std::shared_ptr<BattleSubScene> battleSubScene_ = nullptr;



};
