#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "scene/ScenePlay.h"
#include "scene/SceneTitle.h"

#include "manager/SubSceneManager.h"

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));
	SetBackgroundColor(32, 32, 32);



	ito::GameManager::GetInstance_(std::shared_ptr<SceneTitle>(new SceneTitle()));

}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	ito::GameManager::GetInstance_()->update(delta_time);


	//DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);

}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {
	ito::GameManager::GetInstance_()->Destroy();
}