#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

#include "../character/Dungeon/Enemy.h"

// �O���錾
class Player;
class Enemy;
class SubSceneManager;


// �^�[���̏������Ǘ�����p�̃N���X
// �v���C���[�A�G�̏�����Ԃ��m�F���A���������
class TurnManager final{
public :

	// �R���X�g���N�^
	TurnManager();


	// �f�X�g���N�^
	~TurnManager();

	// �X�V�p�̊֐�
	void update(float delta_time);

	// �v���C���[���Z�b�g����֐�
	// �V�[���ŌĂяo���ăZ�b�g����
	// �����F�v���C���[
	void setPlayer(std::shared_ptr<Player> player) { player_ = player; };
	// �G�̃��X�g���Z�b�g����֐�
	// �V�[���ŌĂяo���ăZ�b�g����
	// �����F�G�̃��X�g
	void setEnemyList(std::list<std::shared_ptr<Enemy>> enemyList);

	//// �T�u�V�[���}�l�[�W���[���Z�b�g����֐�
	//// �V�[���ŌĂяo���ăZ�b�g
	//// �����F�T�u�V�[���}�l�[�W���[
	//void setSubSceneManager(std::shared_ptr<SubSceneManager> subSceneManager) { subSceneManager_ = subSceneManager; }

	// �v���C���[�����͂��s��ꂽ�ۂɌĂяo���֐�
	// �G�̏������s���V�[�P���X�ɑJ�ڂ��邽�߂̊֐�
	void ChangeSeqFromWaitPlayerInput();

	// �v���C���[�̍s�����I�������ۂɌĂяo���֐�
	// actionEndPlayer_��true�ɂ���
	void ActionEndPlayer();

	// �G�̍s�����I�������ۂɌĂяo���֐�
	// actionEndEnemyList�̂����Afalse�����true�ɂ���֐�
	void ActionEndEnemy();

	// ���g���폜����֐�
	void Destroy();

private :

	// �L�����N�^�[�̈ʒu���m�F����֐�
	void CheckCharacterPos();

	//// �T�u�V�[���}�l�[�W���[�̃C���X�^���X
	//// �^�[���}�l�[�W���[���������ꂽ�ۂɈ����œ����
	//std::shared_ptr<SubSceneManager> subSceneManager_ = nullptr;

	// �v���C���[
	// �V�[����setPlayer�֐���p���ăZ�b�g����
	// ���W���擾�ɕK�v
	std::weak_ptr<Player> player_;

	// �G�L�����N�^�[�̃��X�g
	// �V�[����setEnemyList�֐��ŃZ�b�g����
	// ���W�擾�ɕK�v
	// ***************************************************
	// �C������I
	// ***************************************************
	std::list<std::shared_ptr<Enemy>> enemyList_;

	// �v���C���[�̍s�����I�����Ă��邩�ǂ����̃t���O
	bool actionEndPlayer_ = false;


	std::list<bool> actionEndEnemyList_;

	// �G�L�����N�^�[���������ǂ����̃t���O
	bool canMoveEnemy_ = true;




	// �^�[���}�l�[�W���[�̃V�[�P���X��\���萔
	enum class TurnManagerSeq {
		WAIT_PLAYER_INPUT,
		ENEMY_ACTION_DICADE,
		CHECK_ACTION,
		ACTION
	};

	// �^�[����؂�ւ���ۂ̃t���O
	bool isSceneChange_ = false;

	// �V�[����؂�ւ���ۂ̈Ó]����
	float transTime_ = 0.5f;
	// �V�[����؂�ւ���ۂ̈Ó]�p
	int transGpc_ = 0;

	tnl::Vector2i goalPos_;

	std::weak_ptr< Enemy > battlingEnemy_;

	// ���݂̃V�[�P���X
	TurnManagerSeq nowSeq_ = TurnManagerSeq::WAIT_PLAYER_INPUT;

	// ������Ǘ�����p�̃V�[�P���X
	tnl::Sequence<TurnManager> seq_ = tnl::Sequence<TurnManager>(this, &TurnManager::seqWaitPlayerInput);

	// �v���C���[�̓��͑҂��̃V�[�P���X
	bool seqWaitPlayerInput(const float delta_time);
	// �G�L�����N�^�[�̍s�������肷��V�[�P���X
	bool seqEnemyActionDecade(const float delta_time);
	// ���ꂼ��̃L�����N�^�[�̍s�����m�F����V�[�P���X
	bool seqCheckAction(const float delta_time);
	// �s�����s���V�[�P���X
	bool seqAction(const float delta_time);
	// �T�u�V�[����؂�ւ���V�[�P���X
	bool seqChangeSubScene(const float delta_time);
};