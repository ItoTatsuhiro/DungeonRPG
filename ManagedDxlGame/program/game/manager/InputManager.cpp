#include "InputManager.h"



std::shared_ptr<InputManager> InputManager::GetInstance() {

	// InputManagerクラスのインスタンス
	static std::shared_ptr<InputManager> instance = nullptr;

	// 既に生成されていないときのみ新しく生成
	if (!instance) {
		instance = std::shared_ptr<InputManager>(new InputManager());
	}

	return instance;
}


//---------------------------------------------------------------------
// キーが押し続けられている時の処理の関数

// 上の入力を表すキーが押されている際にtrueを返す関数
bool InputManager::KeyDownUp() {

	// 以下のキーが押されている時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyDown(eKeys::KB_UP) ||
		tnl::Input::IsKeyDown(eKeys::KB_W)) {
		return true;
	}
	return false;
}


// 下の入力を表すキーが押されている際にtrueを返す関数
bool InputManager::KeyDownDown() {

	// 以下のキーが押されている時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyDown(eKeys::KB_DOWN) ||
		tnl::Input::IsKeyDown(eKeys::KB_S)) {
		return true;
	}
	return false;
}


// 左の入力を表すキーが押されている際にtrueを返す関数
bool InputManager::KeyDownLeft() {

	// 以下のキーが押されている時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT) ||
		tnl::Input::IsKeyDown(eKeys::KB_A)) {
		return true;
	}
	return false;
}


// 右の入力を表すキーが押されている際にtrueを返す関数
bool InputManager::KeyDownRight() {

	// 以下のキーが押されている時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT) ||
		tnl::Input::IsKeyDown(eKeys::KB_D)) {
		return true;
	}
	return false;
}

// Returnの入力を表すキーが押されている際にtrueを返す関数
bool InputManager::KeyDownReturn() {
	
	// 以下のキーが押されている時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {
		return true;
	}
	return false;

}


// マウスの左をクリックし続けた際の入力
bool InputManager::MouseClickLeft() {

	// 以下のキーが押されている時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsMouseDown(eMouse::LEFT)) {
		return true;
	}
	return false;

}
// マウスの右をクリックし続けた際の入力
bool InputManager::MouseClickRight() {

	// 以下のキーが押されている時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsMouseDown(eMouse::RIGHT)) {
		return true;
	}
	return false;

}


//---------------------------------------------------------------------
// キーが押された時の処理の関数

// 上の入力を表すキーが押された際にtrueを返す関数
bool InputManager::KeyDownTriggerUp() {

	// 以下のキーが押された時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) ||
		tnl::Input::IsKeyDownTrigger(eKeys::KB_W)) {
		return true;
	}
	return false;
}


// 下の入力を表すキーが押された際にtrueを返す関数
bool InputManager::KeyDownTriggerDown() {

	// 以下のキーが押された時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) ||
		tnl::Input::IsKeyDownTrigger(eKeys::KB_S)) {
		return true;
	}
	return false;
}

// 左の入力を表すキーが押された際にtrueを返す関数
bool InputManager::KeyDownTriggerLeft() {

	// 以下のキーが押された時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT) ||
		tnl::Input::IsKeyDownTrigger(eKeys::KB_A)) {
		return true;
	}
	return false;
}

// 右の入力を表すキーが押された際にtrueを返す関数
bool InputManager::KeyDownTriggerRight() {

	// 以下のキーが押された時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT) ||
		tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) {
		return true;
	}
	return false;
}


// Returnの入力を表すキーが押された際にtrueを返す関数
bool InputManager::KeyDownTriggerReturn() {

	// 以下のキーが押された時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		return true;
	}
	return false;
}


// マウスの左をクリックした瞬間の入力
bool InputManager::MouseClickTriggerLeft() {

	// 以下のキーが押されている時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		return true;
	}
	return false;

}

// マウスの右をクリックした瞬間の入力
bool InputManager::MouseClickTriggerRight() {

	// 以下のキーが押されている時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT)) {
		return true;
	}
	return false;

}


//---------------------------------------------------------------------
// キーが離された時の処理の関数

// 上の入力を表すキーが離された際にtrueを返す関数
bool InputManager::KeyReleaseTriggerUp() {

	// 以下のキーが離された時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_UP) ||
		tnl::Input::IsKeyReleaseTrigger(eKeys::KB_W)) {
		return true;
	}
	return false;
}

// 下の入力を表すキーが離された際にtrueを返す関数
bool InputManager::KeyReleaseTriggerDown() {

	// 以下のキーが離された時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_DOWN) ||
		tnl::Input::IsKeyReleaseTrigger(eKeys::KB_S)) {
		return true;
	}
	return false;
}

// 左の入力を表すキーが離された際にtrueを返す関数
bool InputManager::KeyReleaseTriggerLeft() {

	// 以下のキーが離された時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_LEFT) ||
		tnl::Input::IsKeyReleaseTrigger(eKeys::KB_A)) {
		return true;
	}
	return false;
}

// 右の入力を表すキーが離された際にtrueを返す関数
bool InputManager::KeyReleaseTriggerRight() {

	// 以下のキーが離された時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_RIGHT) ||
		tnl::Input::IsKeyReleaseTrigger(eKeys::KB_D)) {
		return true;
	}
	return false;
}

// Returnの入力を表すキーが離された際にtrueを返す関数
bool InputManager::KeyReleaseTriggerReturn() {

	// 以下のキーが離された時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_RETURN)) {
		return true;
	}
	return false;
}


// マウスの左を離した瞬間の入力
bool InputManager::MouseReleaseTriggerLeft() {

	// 以下のキーが押されている時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::OUT_LEFT)) {
		return true;
	}
	return false;

}

// マウスの右を離した瞬間の入力
bool InputManager::MouseReleaseTriggerRight() {

	// 以下のキーが押されている時true
	// もしキーを増やす際は下の条件を増やす
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::OUT_RIGHT)) {
		return true;
	}
	return false;

}