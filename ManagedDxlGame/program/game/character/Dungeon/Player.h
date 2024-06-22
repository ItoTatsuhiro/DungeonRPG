#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"

#include "../../other/Enum.h"
#include "../../base/CharacterBaseDungeon.h"
#include "../../map/Stage.h"
#include "../../manager/TurnManager.h"

// ������s���v���C���[�̃N���X
// �����F
class Player final : public CharacterBaseDungeon {
public :

	// �v���C���[�N���X�̃R���X�g���N�^
	// cellSize_(�}�b�v��1�}�X���̑傫��)��gridPos_(���݂��Ă�����W)��������
	// �����FgridSize...�}�X�̑傫��, startGridPos...�J�n�}�X, startPos...�J�n���W, turnManager...�^�[���Ǘ��p�}�l�[�W���[
	Player( float gridSize, tnl::Vector2i startGridPos, tnl::Vector3 startPos, std::shared_ptr< TurnManager > turnManager);

	// �v���C���[�N���X�̃f�X�g���N�^
	~Player();

	void update(float delta_time);

	// �V�[�P���X��Wait���玟�̏����ɐ؂�ւ��鏈��
	void ChangeSeqFromWait();
	
	// ���g���폜����֐�
	void Destroy();

	enum class PlayerSeq {
		IDLE,			// �ҋ@��Ԃ̃V�[�P���X
		MOVE_CHECK,		// �ړ��̊m�F�̃V�[�P���X
		ROTATE_CHECK,	// ��]�̊m�F�̃V�[�P���X
		WAIT,			// �ҋ@���̃V�[�P���X
		MOVING,			// �ړ����s���V�[�P���X
		ROTATING		// ��]���s���V�[�P���X

	};

	PlayerSeq getNowSeq() const { return nowSeq_; }

private :

	// �f�o�b�O�p�̏��
	// true�̂Ƃ��G�l�~�[�̏�����҂����ɓ�����
	bool debugMode_ = false;

	// �^�[���Ǘ��p�̃}�l�[�W���[
	// �T�u�V�[���ō쐬�������̂����Ă���
	std::shared_ptr< TurnManager > turnManager_;

	// ���s���̃V�[�P���X
	PlayerSeq nowSeq_ = PlayerSeq::IDLE;

	// ���s����s��
	// WAIT�Ɉړ�����ۂɌ��肵���V�[�P���X������
	// WAIT����؂�ւ���ۂɂ�����Q�Ƃ��Đ؂�ւ���
	// �s�������肵�Ă��Ȃ��Ƃ���WAIT�ɂ��Ă���
	PlayerSeq decadedSeq = PlayerSeq::WAIT;

	// �v���C���[�̏�ԗp�̃V�[�P���X
	tnl::Sequence<Player> seq_ = tnl::Sequence<Player>(this, &Player::seqIdle);

	// �ҋ@���̃V�[�P���X
	bool seqIdle(const float delta_time);
	// �ړ�����������V�[�P���X
	bool seqMoveCheck(const float delta_time);
	// ��]����������V�[�P���X
	bool seqRotateCheck(const float delta_time);
	// �ҋ@����V�[�P���X
	bool seqWait(const float delta_time);
	// �ړ����s���V�[�P���X
	bool seqMoving(const float delta_time);
	// ��]���s���V�[�P���X
	bool seqRotating(const float delta_time);
};
