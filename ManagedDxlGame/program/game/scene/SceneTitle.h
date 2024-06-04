#pragma once
#include "../../dxlib_ext/dxlib_ext.h"


// タイトル画面用のクラス
class SceneTitle final : public ito::SceneBase {
public:
	// コンストラクタ
	SceneTitle();
	// デストラクタ
	~SceneTitle();
	// 毎フレームの処理
	void update(float delta_time) override;
	// 描画の処理
	void draw() override;



private:

	// キャラクターのアニメーション用画像
	std::shared_ptr< std::vector<int> > characterAnim_;

	// 背景画像
	int backGpc_;

	// タイトルの画像
	int titleGpc_;

	// タイトル画像の表示位置
	tnl::Vector3 titleGpcPos_ = { 800, 400, 0 };

	// 待機中かどうかのフラグ
	bool isWaiting_ = false;

	// 開始できるかどうかのフラグ
	bool canStart_ = false;

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
