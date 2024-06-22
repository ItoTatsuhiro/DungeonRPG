#include "SceneTitle.h"
#include "ScenePlay.h"

// コンストラクタ
SceneTitle::SceneTitle() {

	// キャラクターの歩行アニメーション読み込み
	characterAnim_ = ito::ResourceManager::GetInstance()->loadAnimGraph("travellerWalkAnimLtoR.png");

	backGpc_ = ito::ResourceManager::GetInstance()->loadGraph("kaidou0331_800b.jpg");

	titleGpc_ = ito::ResourceManager::GetInstance()->loadGraph("DungeonCrawl_Title.png");

	characterStartPos_ = { -100, 580, 0 };
	characterDrawPosFinal_ = { DXE_WINDOW_WIDTH >> 1, 580, 0 };

	characterDrawPos_ = characterStartPos_;

}



// デストラクタ
SceneTitle::~SceneTitle() {



}


// 毎フレームの処理
void SceneTitle::update(float delta_time) {

	if ( !isWaiting_) {
		// 移動
		characterDrawPos_.x += characterMoveValue_;


		if (characterDrawPos_.x >= characterDrawPosFinal_.x && !canStart_) {

			characterDrawPos_ = characterDrawPosFinal_;

			isWaiting_ = true;

			canStart_ = true;

			animDisplayCount_ = 0;

			animframe_ = 1;
		}


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