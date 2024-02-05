#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

#include "../object/Enemy.h"

// �^�[���̏������Ǘ�����p�̃N���X
// �v���C���[�A�G�̏�����Ԃ��m�F���A���������
class TurnManager {
private :

	// �R���X�g���N�^
	TurnManager();

public :

	// �^�[���}�l�[�W���[�̃C���X�^���X���擾����֐�
	static std::shared_ptr<TurnManager> GetInstance();

	// �f�X�g���N�^
	~TurnManager();

	// �X�V�p�̊֐�
	void update();


private :



	// �Ǘ����s���G���X�g
	// �s�����s���G�L�����N�^�[(�I�u�W�F�N�g)�͂��̃��X�g�ɓ����
	std::list< Enemy > enemyList_;


	


};