#pragma once
#include "../../dxlib_ext/dxlib_ext.h"




// 主にゲームのメインの部分の処理を実行するクラス
// 実際に動作を行うサブシーンを管理する役割を持つ
// サブシーン間でやり取りの必要なデータを保持する役割もある
class SceneClear final : public ito::SceneBase {
public:
	// コンストラクタ
	SceneClear();
	// デストラクタ
	~SceneClear();
	// 毎フレームの処理
	void update(float delta_time) override;
	// 描画の処理
	void draw() override;




private:
	// タイトルに戻ることができるかどうかの関数
	bool canChangeScene_ = false;

	// 背景画像
	int backGpc_;

	// 以下アニメーション関係

	// キャラクターのアニメーション用画像
	std::shared_ptr< std::vector<int> > characterAnim_;

	// キャラクターの描画位置
	tnl::Vector3 characterDrawPos_;

	// 最終的にキャラクターが来る位置
	tnl::Vector3 characterDrawPosFinal_;

	// キャラクターが移動し始める位置
	tnl::Vector3 characterStartPos_;

	// キャラクターが移動してくる移動量
	float characterMoveValue_ = 5;

	// 表示するアニメーションの画像
	int animframe_ = 0;
	// アニメーションの最大フレーム
	int animframeMax_ = 4;

	// 表示時間のカウント
	float animDisplayCount_ = 0;
	// アニメーションを切り替える時間
	float animDisplayTime_ = 0.15f;
};
