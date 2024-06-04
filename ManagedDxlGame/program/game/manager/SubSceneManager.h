#pragma once
#include "../../dxlib_ext/dxlib_ext.h"


// �O���錾
class SubSceneBase;
class DungeonSubScene;
class BattleSubScene;
class Enemy;


class SubSceneManager final{

private :

	SubSceneManager();

public :

	// ���̊֐��ŃC���X�^���X���擾
	// �C���X�^���X���擾����ۂ͈����Ȃ���OK
	// �ŏ��ɃC���X�^���X�𐶐�����ۂ͈���������
	static std::shared_ptr<SubSceneManager> GetInstance();

	~SubSceneManager();

	// �X�V�p�̊֐�
	// ���݂̃T�u�V�[�������̊֐��ōX�V����
	void update(float delta_time);
	// �`��p�̊֐�
	// ���݂̃T�u�V�[�������̊֐��ŕ`�悷��
	void draw();

	// �V�[���v���C�̃T�u�V�[��
	enum class ScenePlaySubScene {
		DUNGEON,
		BATTLE
	};


	// �T�u�V�[����؂�ւ���֐�
	// battlingEnemy...�o�g������G�L�����N�^�[
	// �o�g���V�[���Ɉڍs����Ƃ��͓����
	void ChangeSubScene(ScenePlaySubScene nextSubScene, std::shared_ptr<Enemy> battlingEnemy = nullptr);


	// �o�g���V�[����V���ɍ쐬����֐�
	// �_���W��������J�ڂ���ۂ̓T�u�V�[���؂�ւ��O�ɂ���Ńo�g���V�[�����쐬����
	void ChangeBattleScene( std::shared_ptr<Enemy> battlingEnemy);

	// �C���X�^���X���폜����֐�
	void Destroy();

private:
	// ���s����T�u�V�[��
	// ���̕ϐ��ɓ���Ă���T�u�V�[�������s����
	std::shared_ptr<SubSceneBase> nowSubScene_ = nullptr;

	// �o�g�����̓G�L�����N�^�[
	// �o�g���V�[���Ɉړ������Ƃ��Z�b�g���A�o�g���V�[�����炩�����ė����ۂɊY���̃L�����N�^�[������
	std::shared_ptr<Enemy> battlingEnemy_ = nullptr;

	// �_���W�����̃T�u�V�[��
	std::shared_ptr<DungeonSubScene> dungeonSubScene_ = nullptr;

	// �o�g���̃T�u�V�[��
	std::shared_ptr<BattleSubScene> battleSubScene_ = nullptr;

};