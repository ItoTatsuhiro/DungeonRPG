#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

// 複数の入力を一つにまとめるためのクラス
class InputManager final {
private :

	InputManager() {}

public :

	// インプットマネージャーのインスタンスを取得するための関数
	static std::shared_ptr<InputManager> GetInstance();

	~InputManager(){}

	//---------------------------------------------------------------------
	// 入力があるか返すための関数
	// 入力をもとに処理したい際は以下の関数を使用する


	// 上を押し続けた際の入力
	bool KeyDownUp();
	// 下を押し続けた際の入力
	bool KeyDownDown();
	// 左を押し続けた際の入力
	bool KeyDownLeft();
	// 右を押し続けた際の入力
	bool KeyDownRight();
	// Returnのキーを押し続けた際の入力
	bool KeyDownReturn();

	// マウスの左をクリックし続けた際の入力
	bool MouseClickLeft();
	// マウスの右をクリックし続けた際の入力
	bool MouseClickRight();


	// 上を押した瞬間の入力
	bool KeyDownTriggerUp();
	// 下を押した瞬間の入力
	bool KeyDownTriggerDown();
	// 左を押した瞬間の入力
	bool KeyDownTriggerLeft();
	// 右を押した瞬間の入力
	bool KeyDownTriggerRight();
	// Returnのキーを押した瞬間の入力
	bool KeyDownTriggerReturn();

	// マウスの左をクリックした瞬間の入力
	bool MouseClickTriggerLeft();
	// マウスの右をクリックした瞬間の入力
	bool MouseClickTriggerRight();

	// 上を離した瞬間の入力
	bool KeyReleaseTriggerUp();
	// 下を離した瞬間の入力
	bool KeyReleaseTriggerDown();
	// 左を離した瞬間の入力
	bool KeyReleaseTriggerLeft();
	// 右を離した瞬間の入力
	bool KeyReleaseTriggerRight();
	// Returnのキーを離したの入力
	bool KeyReleaseTriggerReturn();

	// マウスの左を離した瞬間の入力
	bool MouseReleaseTriggerLeft();
	// マウスの右を離した瞬間の入力
	bool MouseReleaseTriggerRight();

};