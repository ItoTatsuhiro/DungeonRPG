#pragma once
#include "../../base/SubSceneBase.h"

// バトルシーンのサブクラス
// ScenePlay内で必要に応じてupdate, drawする
class BattleSubScene : public SubSceneBase {
public :
	// コンストラクタ
	BattleSubScene();
	// デストラクタ
	~BattleSubScene();
	// 更新用の関数
	void update(float delta_time) override;
	// 描画用の関数
	void draw() override;


private :


};