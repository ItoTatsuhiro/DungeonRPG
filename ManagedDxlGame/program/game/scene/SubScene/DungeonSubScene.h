#pragma once
#include "../../base/SubSceneBase.h"



// --------------------------------------------------------------
// �O���錾
class Stage;
class Player;
class Enemy;
class TurnManager;
class SubSceneManager;
class TransformCamera;
class TurnManager;


// �_���W������ł̑�����s���T�u�V�[��
// �V�[���v���C���ŕK�v�ɉ�����update,draw����
class DungeonSubScene final : public SubSceneBase {
public :


	// �R���X�g���N�^
	DungeonSubScene(/* std::shared_ptr<SubSceneManager> subSceneManager */);

	// �f�X�g���N�^
	~DungeonSubScene();

	// �X�V�p�̊֐�
	void update(float delta_time) override;

	// �`��p�̊֐�
	void draw() override;

	// �G�������֐�
	void DeleteEnemy( std::shared_ptr<Enemy> deleteEnemy );


	// �X�e�[�W���擾����֐�
	std::shared_ptr<Stage> getStage() const { return stage_; }
	// �v���C���[���擾����֐�
	std::shared_ptr<Player> getPlayer() const { return player_; }
	// �G�L�����N�^�[���擾����֐�
	std::shared_ptr<Enemy> getEnemy() const { return enemy_; }

private:

	//// �T�u�V�[�����Ǘ�����}�l�[�W���[
	//std::shared_ptr< SubSceneManager > subSceneManager_;

	// �^�[�����Ǘ�����}�l�[�W���[
	std::shared_ptr< TurnManager > turnManager_;

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

	// �G�L�����N�^�[�̃��X�g
	std::list<std::shared_ptr<Enemy>> enemyList_;


	// 1�}�X�̏c���̑傫��
	float gridSize_ = 50;

	// �����������摜�̃n���h��
	int directionGpcHdl_ = 0;

	// �����\���p�摜�̕\��������傫���̔{��
	float directionGpcSize_ = 3.0f;

	// �����\���p�摜�̍��W
	tnl::Vector3 directionGpcPos_ = { 100, 100, 0 };

	// �����摜�̕\������p�x
	// �v���C���[�L�����N�^�[�̌����ɉ����ĉ�]������̂ŁA�v���C���[����]�����ۂɂ�������炷
	double directionGpcAngle_ = 0;

};