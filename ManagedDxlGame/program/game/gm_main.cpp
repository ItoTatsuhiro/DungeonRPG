#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "scene/ScenePlay.h"

#include "manager/SubSceneManager.h"

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart() {
	srand(time(0));
	SetBackgroundColor(32, 32, 32);

	std::shared_ptr<ScenePlay> scene = std::shared_ptr<ScenePlay>( new ScenePlay() );
	SubSceneManager::GetInstance()->setScenePlay(scene);

	// ito::GameManager::GetInstance_(new ScenePlay());
	ito::GameManager::GetInstance_(scene);

}


//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	ito::GameManager::GetInstance_()->update(delta_time);


	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);

}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {
	ito::GameManager::GetInstance_()->
}