#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <vector>

#include "../map/Stage.h"
#include "../object/Player.h"
#include "../object/Enemy.h"

#include "../other/TransformCamera.h"


class ScenePlay final: public ito::SceneBase {
public :
	// �R���X�g���N�^
	ScenePlay();
	// �f�X�g���N�^
	~ScenePlay();
	// ���t���[���̏���
	void update(float delta_time) override;
	// �`��̏���
	void draw() override;



private :

	// �v���C���[�A�G�l�~�[�𐶐�����֐�
	void CreateCharacter();

	// ��l�̂̃J����
	std::shared_ptr< TransformCamera > FPCamera_;


	// �X�e�[�W���Ǘ�����N���X
	std::shared_ptr<Stage> stage_ = nullptr;

	// �v���C���[�̃N���X
	std::shared_ptr<Player> player_ = nullptr;

	// �G�L�����N�^�[�̃N���X
	std::shared_ptr<Enemy> enemy_ = nullptr;


	// 1�}�X�̏c���̑傫��
	float gridSize_ = 50;

	// �ǂ̃I�u�W�F�N�g
	std::shared_ptr< ito::Object3D > wall_ = nullptr;
	// ���̃I�u�W�F�N�g
	std::shared_ptr< ito::Object3D > floor_ = nullptr;

};
