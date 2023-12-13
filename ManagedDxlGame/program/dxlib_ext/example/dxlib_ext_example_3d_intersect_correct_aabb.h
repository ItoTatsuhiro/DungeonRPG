#pragma once

/*



//-----------------------------------------------------------------------------------------------------------
//
//
// AABBボックス同士の衝突判定と補正サンプル
//
//
//-----------------------------------------------------------------------------------------------------------

#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"


Shared<dxe::Camera> camera = nullptr;
Shared<dxe::Mesh> boxA = nullptr;
Shared<dxe::Mesh> boxB = nullptr;

float jump_vel = 0;

const float BOX_SIZE = 100;
tnl::Vector3 box_size_v = { BOX_SIZE, BOX_SIZE, BOX_SIZE };


//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart() {
	srand(time(0));

	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
	SetBackgroundColor(32, 32, 32);
	SetDefaultLightParameter("directional_light_parameter.bin");

	camera = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	boxA = dxe::Mesh::CreateBoxMV(BOX_SIZE);
	boxA->setTexture(dxe::Texture::CreateFromFile("graphics/test.jpg"));
	boxA->pos_ = { 100, 0, 0 };

	boxB = boxA->createClone();
	boxB->pos_ = { -100, 0, 0 };

}


//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	//-------------------------------------------------------------------------------
	//
	// update
	//
	//-------------------------------------------------------------------------------

	//
	// XZ平面上の移動処理
	//
	tnl::Vector3 prev_pos = boxA->pos_;

	tnl::Input::RunIndexKeyDown(
		[&](uint32_t index) {
			tnl::Vector3 v[4] = {
				tnl::Vector3::left,
				tnl::Vector3::right,
				tnl::Vector3::forward,
				tnl::Vector3::back
			};
			boxA->pos_ += v[index] * 3.0f;
		}, eKeys::KB_LEFT, eKeys::KB_RIGHT, eKeys::KB_UP, eKeys::KB_DOWN);


	//
	// ジャンプと落下処理
	//
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z)) {
		jump_vel = 15.0f;
	}
	boxA->pos_.y += jump_vel;
	if (boxA->pos_.y <= 0) {
		boxA->pos_.y = 0;
		jump_vel = 0;
	}
	else {
		jump_vel -= 0.98f;
	}

	//
	// 衝突判定と補正処理
	//
	if (tnl::IsIntersectAABB(boxA->pos_, box_size_v, boxB->pos_, box_size_v)) {

		//----------------------------------------------------------------------------------------------
		// work... AABB (A) と AABB (B) が衝突した時の 補正座標を取得する
		// arg1... 移動前の A 座標
		// arg2... A のサイズ
		// arg4... B のサイズ
		// arg3... A の座標 ( この関数で補正されます )
		// arg5... B の座標 ( この関数で補正されます )
		// arg6... 補正タイプ ( [ 0 : A が B を完全に押す ] [ 1 : B が A を完全に押す ] [ 2 : A と B は押し合う ])
		// arg6... 補正スペース ( デフォルト 0.1f )
		// ret... A を何処に補正したか [ 下に補正 0 ] [ 右に補正 1 ] [ 上に補正 2 ] [ 左に補正 3 ] [ 奥に補正 4 ] [ 手前に補正 5 ]
		int n = tnl::GetCorrectPositionIntersectAABB(prev_pos, box_size_v, box_size_v, boxA->pos_, boxB->pos_, 0);

		// 上に補正されたらジャンプ力リセット
		if (2 == n) jump_vel = 0;
	}


	camera->update();


	//-------------------------------------------------------------------------------
	//
	// draw
	//
	//-------------------------------------------------------------------------------

	DrawGridGround(camera, 50, 20);

	boxA->render(camera);
	boxB->render(camera);

	DrawDefaultLightGuiController();

	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);

}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}


*/

