#pragma once
#include "../library/tnl_util.h"
#include "../library/tnl_csv.h"
#include "../library/tnl_font_texture.h"
#include "../library/tnl_hierarchy_tree.h"
#include "../library/tnl_input.h"
#include "../library/tnl_intersect.h"
#include "../library/tnl_link_linear.h"
#include "../library/tnl_math.h"
#include "../library/tnl_matrix.h"
#include "../library/tnl_quaternion.h"
#include "../library/tnl_sequence.h"
#include "../library/tnl_shared_factory.h"
#include "../library/tnl_timer_fluct.h"
#include "../library/tnl_vector2i.h"
#include "../library/tnl_vector3.h"
#include "../library/tnl_seek_unit.h"
#include "../library/stb_image.h"
#include "../library/json11.hpp"
#include "DxLib.h"
#include "dxlib_ext_camera.h"
#include "dxlib_ext_mesh.h"
#include "dxlib_ext_texture.h"
#include "dxlib_ext_gui_value_slider.h"
#include "dxlib_ext_gui_menu_selector.h"
//---------------------------------------------------------------------------------
// myLibrary
#include "../myLibrary/Manager/ito_GameManager.h"
#include "../myLibrary/Manager/ito_ResourceManager.h"
#include "../myLibrary/Base/ito_transform.h"
#include "../myLibrary/Base/ito_Object3D.h"
#include "../myLibrary/Base/ito_Object2D.h"
#include "../myLibrary/Base/ito_SceneBase.h"
//---------------------------------------------------------------------------------

// ウィンドウの幅
const int DXE_WINDOW_WIDTH = 1280;
// ウィンドウの高さ
const int DXE_WINDOW_HEIGHT = 720;
// 固定フレームレート
const float DXE_FIX_FPS = 60.0f;

// 文字描画
void DrawStringEx(float x, float y, int color, const char* _str, ...);
void DrawStringEx(int x, int y, int color, const char* _str, ...);
void DrawStringToHandleEx(const float x, const float y, const int color, const int hdl, const char* _str, ...);

// ライン描画
void DrawLineEx(const tnl::Vector3& p, const tnl::Vector3& v, const float length, const int color = -1);
// 矩形描画
void DrawBoxEx(const tnl::Vector3& p, const float width, const float height, const bool fill = true, const int color = -1);
void DrawRotaBox(const tnl::Vector3& pos, float w, float h, float rad, int color = -1);

// FPS インジケータ描画
void DrawFpsIndicator(const tnl::Vector3& pos, float delta_time);

// デバッグ用のグリッド地面
// arg1... カメラ
// arg2... グリッドマスのサイズ
// arg3... グリッドを並べる個数 ( 偶数個で指定 )
// arg4... 16進数カラー
// tips... この関数を使用する前にカメラを生成して update 関数を実行してください
void DrawGridGround( const Shared<dxe::Camera> camera, const float square_size, int row_num, int color = 0x99999999 );

// デフォルトライトパラメータをリソースから設定
// arg1... DrawDefaultLightGuiController で出力したバイナリファイルパス
void SetDefaultLightParameter(const std::string& file_path);

// デフォルトライトパラメータをコントロールするGUIを描画
void DrawDefaultLightGuiController();






//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
void DrawAxis(const Shared<dxe::Camera> camera, const tnl::Vector3& pos, const tnl::Quaternion& rot, const float length);
void DrawOBB(const Shared<dxe::Camera> camera, const tnl::Vector3& pos, const tnl::Quaternion& rot, const tnl::Vector3& size, const int color = 0x00ff00ff);
void DrawAABB(const Shared<dxe::Camera> camera, const tnl::Vector3& pos, const tnl::Vector3& size, const int color = 0x0000ffff);
void DrawBdSphere(const Shared<dxe::Camera> camera, const tnl::Vector3& pos, const float radius);
void DrawLine3DEx(const Shared<dxe::Camera> camera, const tnl::Vector3& st, const tnl::Vector3& en, const int color = -1);
std::string GetDragFilePathReadTrigger();

namespace dxe {
	inline DxLib::VECTOR ToDxlibVector3(const tnl::Vector3& v) { return { v.x, v.y, v.z }; }
	inline tnl::Vector3 ToTnlVector3(const DxLib::VECTOR& v) { return { v.x, v.y, v.z }; }
}








































/*
test


float A = 100;
float B = 600;
float t = 0;
for (int i = 0; i <= 20; ++i) {
	t = ( i / 20.0f ) * 180.0f ;
	float si = sinf(tnl::ToRadian(-90) + tnl::ToRadian(t)) ;
	float x = A + (B - A) * ( 1.0f + si ) / 2.0f ;
	DrawLine(x, 100, x, 105, -1);
}

*/

