#include "InputManager.h"



std::shared_ptr<InputManager> InputManager::GetInstance() {

	// InputManager�N���X�̃C���X�^���X
	static std::shared_ptr<InputManager> instance = nullptr;

	// ���ɐ�������Ă��Ȃ��Ƃ��̂ݐV��������
	if (!instance) {
		instance = std::shared_ptr<InputManager>(new InputManager());
	}

	return instance;
}


//---------------------------------------------------------------------
// �L�[�������������Ă��鎞�̏����̊֐�

// ��̓��͂�\���L�[��������Ă���ۂ�true��Ԃ��֐�
bool InputManager::KeyDownUp() {

	// �ȉ��̃L�[��������Ă��鎞true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyDown(eKeys::KB_UP) ||
		tnl::Input::IsKeyDown(eKeys::KB_W)) {
		return true;
	}
	return false;
}


// ���̓��͂�\���L�[��������Ă���ۂ�true��Ԃ��֐�
bool InputManager::KeyDownDown() {

	// �ȉ��̃L�[��������Ă��鎞true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyDown(eKeys::KB_DOWN) ||
		tnl::Input::IsKeyDown(eKeys::KB_S)) {
		return true;
	}
	return false;
}


// ���̓��͂�\���L�[��������Ă���ۂ�true��Ԃ��֐�
bool InputManager::KeyDownLeft() {

	// �ȉ��̃L�[��������Ă��鎞true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT) ||
		tnl::Input::IsKeyDown(eKeys::KB_A)) {
		return true;
	}
	return false;
}


// �E�̓��͂�\���L�[��������Ă���ۂ�true��Ԃ��֐�
bool InputManager::KeyDownRight() {

	// �ȉ��̃L�[��������Ă��鎞true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT) ||
		tnl::Input::IsKeyDown(eKeys::KB_D)) {
		return true;
	}
	return false;
}

// Return�̓��͂�\���L�[��������Ă���ۂ�true��Ԃ��֐�
bool InputManager::KeyDownReturn() {
	
	// �ȉ��̃L�[��������Ă��鎞true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyDown(eKeys::KB_RETURN)) {
		return true;
	}
	return false;

}


// �}�E�X�̍����N���b�N���������ۂ̓���
bool InputManager::MouseClickLeft() {

	// �ȉ��̃L�[��������Ă��鎞true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsMouseDown(eMouse::LEFT)) {
		return true;
	}
	return false;

}
// �}�E�X�̉E���N���b�N���������ۂ̓���
bool InputManager::MouseClickRight() {

	// �ȉ��̃L�[��������Ă��鎞true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsMouseDown(eMouse::RIGHT)) {
		return true;
	}
	return false;

}


//---------------------------------------------------------------------
// �L�[�������ꂽ���̏����̊֐�

// ��̓��͂�\���L�[�������ꂽ�ۂ�true��Ԃ��֐�
bool InputManager::KeyDownTriggerUp() {

	// �ȉ��̃L�[�������ꂽ��true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) ||
		tnl::Input::IsKeyDownTrigger(eKeys::KB_W)) {
		return true;
	}
	return false;
}


// ���̓��͂�\���L�[�������ꂽ�ۂ�true��Ԃ��֐�
bool InputManager::KeyDownTriggerDown() {

	// �ȉ��̃L�[�������ꂽ��true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) ||
		tnl::Input::IsKeyDownTrigger(eKeys::KB_S)) {
		return true;
	}
	return false;
}

// ���̓��͂�\���L�[�������ꂽ�ۂ�true��Ԃ��֐�
bool InputManager::KeyDownTriggerLeft() {

	// �ȉ��̃L�[�������ꂽ��true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT) ||
		tnl::Input::IsKeyDownTrigger(eKeys::KB_A)) {
		return true;
	}
	return false;
}

// �E�̓��͂�\���L�[�������ꂽ�ۂ�true��Ԃ��֐�
bool InputManager::KeyDownTriggerRight() {

	// �ȉ��̃L�[�������ꂽ��true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT) ||
		tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) {
		return true;
	}
	return false;
}


// Return�̓��͂�\���L�[�������ꂽ�ۂ�true��Ԃ��֐�
bool InputManager::KeyDownTriggerReturn() {

	// �ȉ��̃L�[�������ꂽ��true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		return true;
	}
	return false;
}


// �}�E�X�̍����N���b�N�����u�Ԃ̓���
bool InputManager::MouseClickTriggerLeft() {

	// �ȉ��̃L�[��������Ă��鎞true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		return true;
	}
	return false;

}

// �}�E�X�̉E���N���b�N�����u�Ԃ̓���
bool InputManager::MouseClickTriggerRight() {

	// �ȉ��̃L�[��������Ă��鎞true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::IN_RIGHT)) {
		return true;
	}
	return false;

}


//---------------------------------------------------------------------
// �L�[�������ꂽ���̏����̊֐�

// ��̓��͂�\���L�[�������ꂽ�ۂ�true��Ԃ��֐�
bool InputManager::KeyReleaseTriggerUp() {

	// �ȉ��̃L�[�������ꂽ��true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_UP) ||
		tnl::Input::IsKeyReleaseTrigger(eKeys::KB_W)) {
		return true;
	}
	return false;
}

// ���̓��͂�\���L�[�������ꂽ�ۂ�true��Ԃ��֐�
bool InputManager::KeyReleaseTriggerDown() {

	// �ȉ��̃L�[�������ꂽ��true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_DOWN) ||
		tnl::Input::IsKeyReleaseTrigger(eKeys::KB_S)) {
		return true;
	}
	return false;
}

// ���̓��͂�\���L�[�������ꂽ�ۂ�true��Ԃ��֐�
bool InputManager::KeyReleaseTriggerLeft() {

	// �ȉ��̃L�[�������ꂽ��true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_LEFT) ||
		tnl::Input::IsKeyReleaseTrigger(eKeys::KB_A)) {
		return true;
	}
	return false;
}

// �E�̓��͂�\���L�[�������ꂽ�ۂ�true��Ԃ��֐�
bool InputManager::KeyReleaseTriggerRight() {

	// �ȉ��̃L�[�������ꂽ��true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_RIGHT) ||
		tnl::Input::IsKeyReleaseTrigger(eKeys::KB_D)) {
		return true;
	}
	return false;
}

// Return�̓��͂�\���L�[�������ꂽ�ۂ�true��Ԃ��֐�
bool InputManager::KeyReleaseTriggerReturn() {

	// �ȉ��̃L�[�������ꂽ��true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_RETURN)) {
		return true;
	}
	return false;
}


// �}�E�X�̍��𗣂����u�Ԃ̓���
bool InputManager::MouseReleaseTriggerLeft() {

	// �ȉ��̃L�[��������Ă��鎞true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::OUT_LEFT)) {
		return true;
	}
	return false;

}

// �}�E�X�̉E�𗣂����u�Ԃ̓���
bool InputManager::MouseReleaseTriggerRight() {

	// �ȉ��̃L�[��������Ă��鎞true
	// �����L�[�𑝂₷�ۂ͉��̏����𑝂₷
	if (tnl::Input::IsMouseTrigger(eMouseTrigger::OUT_RIGHT)) {
		return true;
	}
	return false;

}