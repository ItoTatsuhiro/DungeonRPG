#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

// �����̓��͂���ɂ܂Ƃ߂邽�߂̃N���X
class InputManager final {
private :

	InputManager() {}

public :

	// �C���v�b�g�}�l�[�W���[�̃C���X�^���X���擾���邽�߂̊֐�
	static std::shared_ptr<InputManager> GetInstance();

	~InputManager(){}

	//---------------------------------------------------------------------
	// ���͂����邩�Ԃ����߂̊֐�
	// ���͂����Ƃɏ����������ۂ͈ȉ��̊֐����g�p����


	// ��������������ۂ̓���
	bool KeyDownUp();
	// ���������������ۂ̓���
	bool KeyDownDown();
	// ���������������ۂ̓���
	bool KeyDownLeft();
	// �E�������������ۂ̓���
	bool KeyDownRight();
	// Return�̃L�[�������������ۂ̓���
	bool KeyDownReturn();

	// �}�E�X�̍����N���b�N���������ۂ̓���
	bool MouseClickLeft();
	// �}�E�X�̉E���N���b�N���������ۂ̓���
	bool MouseClickRight();


	// ����������u�Ԃ̓���
	bool KeyDownTriggerUp();
	// �����������u�Ԃ̓���
	bool KeyDownTriggerDown();
	// �����������u�Ԃ̓���
	bool KeyDownTriggerLeft();
	// �E���������u�Ԃ̓���
	bool KeyDownTriggerRight();
	// Return�̃L�[���������u�Ԃ̓���
	bool KeyDownTriggerReturn();

	// �}�E�X�̍����N���b�N�����u�Ԃ̓���
	bool MouseClickTriggerLeft();
	// �}�E�X�̉E���N���b�N�����u�Ԃ̓���
	bool MouseClickTriggerRight();

	// ��𗣂����u�Ԃ̓���
	bool KeyReleaseTriggerUp();
	// ���𗣂����u�Ԃ̓���
	bool KeyReleaseTriggerDown();
	// ���𗣂����u�Ԃ̓���
	bool KeyReleaseTriggerLeft();
	// �E�𗣂����u�Ԃ̓���
	bool KeyReleaseTriggerRight();
	// Return�̃L�[�𗣂����̓���
	bool KeyReleaseTriggerReturn();

	// �}�E�X�̍��𗣂����u�Ԃ̓���
	bool MouseReleaseTriggerLeft();
	// �}�E�X�̉E�𗣂����u�Ԃ̓���
	bool MouseReleaseTriggerRight();

};