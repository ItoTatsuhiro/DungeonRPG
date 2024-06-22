#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <vector>

#include "../map/Stage.h"
#include "../character/Dungeon/Player.h"
#include "../character/Dungeon/Enemy.h"
#include "../manager/TurnManager.h"
#include "../base/SubSceneBase.h"

#include "../other/TransformCamera.h"

// �O���錾
class SubSceneManager;
class DungeonSubScene;
class BattleSubScene;

// ��ɃQ�[���̃��C���̕����̏��������s����N���X
// ���ۂɓ�����s���T�u�V�[�����Ǘ��������������
// �T�u�V�[���Ԃł����̕K�v�ȃf�[�^��ێ��������������
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


	// �T�u�V�[�����Ǘ�����p�̃}�l�[�W���[
	// �T�u�V�[���͂�����Ɏ�������
	std::shared_ptr< SubSceneManager > subSceneManager_ = nullptr;



};
