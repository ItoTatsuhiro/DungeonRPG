#include "TurnManager.h"



// �R���X�g���N�^
TurnManager::TurnManager() {

}

// �^�[���}�l�[�W���[�̃C���X�^���X���擾����֐�
std::shared_ptr<TurnManager> TurnManager::GetInstance() {

	// TurnManager�N���X�̃C���X�^���X
	static std::shared_ptr<TurnManager> instance = nullptr;

	// ���ɐ�������Ă��Ȃ��Ƃ��̂ݐV��������
	if (!instance) {
		instance = std::shared_ptr<TurnManager>(new TurnManager());
	}

	return instance;

}


TurnManager::~TurnManager() {

}


void TurnManager::update() {



}


