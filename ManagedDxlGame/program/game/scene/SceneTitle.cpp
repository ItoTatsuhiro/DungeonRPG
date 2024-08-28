#include "SceneTitle.h"
#include "ScenePlay.h"

// コンストラクタ
SceneTitle::SceneTitle() {

	// キャラクターの歩行アニメーション読み込み
	characterAnim_ = ito::ResourceManager::GetInstance()->loadAnimGraph("travellerWalkAnimLtoR.png");
	// 背景画像読み込み
	backGpc_ = ito::ResourceManager::GetInstance()->loadGraph("kaidou0331_800b.jpg");
	// タイトルロゴ用画像読み込み
	titleGpc_ = ito::ResourceManager::GetInstance()->loadGraph("DungeonCrawl_Title.png");

	// キャラクター開始位置
	characterStartPos_ = { -100, 580, 0 };
	characterDrawPosFinal_ = { DXE_WINDOW_WIDTH >> 1, 580, 0 };
	// キャラクター描画の初期位置を設定
	characterDrawPos_ = characterStartPos_;

	// BGM読み込み
	titleBGMhdl_ = ito::ResourceManager::GetInstance()->loadSoundMem("ファンタジー7-街-.mp3");
}



// デストラクタ
SceneTitle::~SceneTitle() {



}


// 毎フレームの処理
void SceneTitle::update(float delta_time) {

	// BGM再生
	if (!isPlayingBgm_) {
		PlaySoundMem(titleBGMhdl_, DX_PLAYTYPE_LOOP);
		isPlayingBgm_ = true;
	}


	if ( !isWaiting_) {
		// キャラクターの移動
		characterDrawPos_.x += characterMoveValue_;

		// 所定の位置までキャラクターが移動したときゲーム開始できる状態にする
		if (characterDrawPos_.x >= characterDrawPosFinal_.x && !canStart_) {

			characterDrawPos_ = characterDrawPosFinal_;

			isWaiting_ = true;

			canStart_ = true;

			animDisplayCount_ = 0;

			animframe_ = 1;
		}

		// アニメーション用画像切り替え
		if (animDisplayCount_ > animDisplayTime_) {

			animDisplayCount_ = 0;

			animframe_ = (animframe_ + 1) % animframeMax_;
		}
		else {
			animDisplayCount_ += delta_time;
		}

	}


	if (isWaiting_ && canStart_) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			isWaiting_ = false;

		}


	}

	// キャラクターが画面外まで移動したらシーン切り替え
	if (characterDrawPos_.x >= DXE_WINDOW_WIDTH + 120) {

		// BGM停止
		StopSoundMem(titleBGMhdl_);

		ito::GameManager::GetInstance_()->changeScene( std::shared_ptr<ScenePlay>( new ScenePlay()) );

	}

}


// 描画の処理
void SceneTitle::draw() {

	// 背景描画
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 1.8f, 0, backGpc_, true);

	SetFontSize(80);

	// タイトルロゴ画像表示
	DrawRotaGraph(titleGpcPos_.x, titleGpcPos_.y, 2,  0.05 * tnl::PI, titleGpc_, true);
	// キャラクター描画
	DrawRotaGraph(characterDrawPos_.x, characterDrawPos_.y, 8, 0, (*characterAnim_)[animframe_], true);


	if (isWaiting_) {

		SetFontSize(40);
		DrawStringEx(100, 450, 0, "Enterでゲームスタート");

	}
}