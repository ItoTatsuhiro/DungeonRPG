#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <vector>

#include "../map/Stage.h"
#include "../object/Player.h"
#include "../object/Enemy.h"
#include "../manager/TurnManager.h"
#include "../base/SubSceneBase.h"
#include "SubScene/DungeonSubScene.h"

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
	// ���s����T�u�V�[��
	std::shared_ptr<SubSceneBase> nowSubScene_ = nullptr;
	// �_���W�����̃V�[��
	std::shared_ptr<DungeonSubScene> dungeonSubScene_ = nullptr;





};
