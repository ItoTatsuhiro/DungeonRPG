#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include <vector>

#include "../map/Stage.h"
#include "../character/Dungeon/Player.h"
#include "../character/Dungeon/Enemy.h"
#include "../manager/TurnManager.h"
#include "../base/SubSceneBase.h"

#include "../other/TransformCamera.h"


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

	// ��U���g�p
	// �T�u�V�[����؂�ւ���֐�
	void ChangeSubScene( std::shared_ptr<SubSceneBase> nextSubScene );

	// �_���W�����̃T�u�V�[���ɐ؂�ւ�
	void ChangeSubSceneToDungeon();
	// �o�g���̃T�u�V�[���ɐ؂�ւ�
	void ChangeSubSceneToBattle();

	// �T�u�V�[���̃Q�b�^�[
	// ��̊֐��Ő؂�ւ���ۂɈ����Ƃ��Ďg�p

	std::shared_ptr<DungeonSubScene> getDungeonSubScene() { return dungeonSubScene_; }
	std::shared_ptr<BattleSubScene> getBattleSubScene() { return battleSubScene_; }

private :
	// ���s����T�u�V�[��
	// ���̕ϐ��ɓ���Ă���T�u�V�[�������s����
	std::shared_ptr<SubSceneBase> nowSubScene_ = nullptr;
	// �_���W�����̃T�u�V�[��
	std::shared_ptr<DungeonSubScene> dungeonSubScene_ = nullptr;
	// �o�g���̃T�u�V�[��
	std::shared_ptr<BattleSubScene> battleSubScene_ = nullptr;



};
