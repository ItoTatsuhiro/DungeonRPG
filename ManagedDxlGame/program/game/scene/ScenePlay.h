#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <vector>

#include "../map/Stage.h"
#include "../character/Dungeon/Player.h"
#include "../character/Dungeon/Enemy.h"
#include "../manager/TurnManager.h"
#include "../base/SubSceneBase.h"
#include "../manager/SubSceneManager.h"

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




private :

	// 以下のサブシーンは、サブシーン内でサブシーンを切り替えるため、
	// シングルトンで生成している
	// ScenePlayが持ってはいるが、
	// インスタンスを取得する際はGetInstance()関数で取得する

	//// サブシーンを管理する用のマネージャー
	//// サブシーンはこちらに持たせる
	//std::shared_ptr< SubSceneManager > subSceneManager_ = nullptr;



};
