#pragma once
#include "../../base/SubSceneBase.h"

// �o�g���V�[���̃T�u�N���X
// ScenePlay���ŕK�v�ɉ�����update, draw����
class BattleSubScene : public SubSceneBase {
public :
	// �R���X�g���N�^
	BattleSubScene();
	// �f�X�g���N�^
	~BattleSubScene();
	// �X�V�p�̊֐�
	void update(float delta_time) override;
	// �`��p�̊֐�
	void draw() override;


private :


};