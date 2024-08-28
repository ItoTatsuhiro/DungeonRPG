#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

// サブシーンベースクラス
// シーン内でさらにシーン分けする際に作成するサブシーンの作成に用いるクラス
// 以下は純粋仮想関数
// １．void update(float delta_time) ... 更新用の関数
// ２．void draw() ... 描画用の関数
class SubSceneBase {
public :
	// コンストラクタ
	SubSceneBase(){}
	// デストラクタ
	virtual ~SubSceneBase(){}

	// 更新用の関数
	// 純粋仮想関数
	virtual void update(float delta_time){};
	// 描画用の関数
	// 純粋仮想関数
	virtual void draw(){};

	// サブシーンを切り替える際に呼び出す関数
	virtual void ChangeSubScene() = 0;
};