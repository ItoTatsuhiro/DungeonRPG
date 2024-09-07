#include "SceneClear.h"

#include "SceneTitle.h"

// コンストラクタ
SceneClear::SceneClear() {

	backGpc_ = ito::ResourceManager::GetInstance()->loadGraph("grass.png");

	// キャラクターの歩行アニメーション読み込み
	characterAnim_ = ito::ResourceManager::GetInstance()->loadAnimGraph("travellerWalkAnimLtoR.png");

	characterStartPos_ = { -100, 450, 0 };
	characterDrawPosFinal_ = { DXE_WINDOW_WIDTH >> 1, 450, 0 };

	characterDrawPos_ = characterStartPos_;

	// BGM読み込み
	clearBGMhdl_ = ito::ResourceManager::GetInstance()->loadSoundMem("ファンタジー-日常-.mp3");

	// 音量調整
	ChangeVolumeSoundMem(50, clearBGMhdl_);
}



// デストラクタ
SceneClear::~SceneClear() {



}


// 毎フレームの処理
void SceneClear::update(float delta_time) {

	if (!isPlayingBgm_) {

		PlaySoundMem(clearBGMhdl_, DX_PLAYTYPE_LOOP);

		isPlayingBgm_ = true;
	}


	if (characterDrawPos_.x < characterDrawPosFinal_.x) {
		// 移動
		characterDrawPos_.x += characterMoveValue_;

	}
	else if (characterDrawPos_.x >= characterDrawPosFinal_.x && !canChangeScene_) {

		characterDrawPos_ = characterDrawPosFinal_;

		canChangeScene_ = true;
	}


	// アニメーションの切り替え用の処理
	if (animDisplayCount_ > animDisplayTime_) {

		animDisplayCount_ = 0;

		animframe_ = (animframe_ + 1) % animframeMax_;
	}
	else {
		animDisplayCount_ += delta_time;
	}

	if (canChangeScene_) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			// BGM停止
			StopSoundMem(clearBGMhdl_);

			// タイトルシーンに切り替え
			ito::GameManager::GetInstance_()->changeScene(std::shared_ptr<SceneTitle>(new SceneTitle()));
		}

	}


}


// 描画の処理
void SceneClear::draw() {

	// 背景描画
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 2, 0, backGpc_, true);

	SetFontSize(80);

	DrawStringEx(450, 150, -1, "脱出成功！");

	DrawRotaGraph(characterDrawPos_.x, characterDrawPos_.y, 6.5, 0, (*characterAnim_)[animframe_], true);

	SetFontSize(50);

	DrawStringEx(450, 530, -1, "Enterでタイトルに戻る");

}