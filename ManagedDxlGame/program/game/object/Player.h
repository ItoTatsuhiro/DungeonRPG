#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

#include "../other/Enum.h"
#include "../base/EntityBase.h"
#include "../map/Stage.h"

// ������s���v���C���[�̃N���X
// �����F
class Player final : public EntityBase {
public :

	// �v���C���[�N���X�̃R���X�g���N�^
	// cellSize_(�}�b�v��1�}�X���̑傫��)��gridPos_(���݂��Ă�����W)��������
	// �����FcellSize, startGridPos
	Player( float gridSize, tnl::Vector2i startGridPos );

	// �v���C���[�N���X�̃f�X�g���N�^
	~Player();

	void update(float delta_time);

	// �v���C���[��Transform���擾����֐�
	const ito::Transform& getTransform() { return nowTransform_; }

	// ���Ɉړ�����ړ�����v�Z����֐�
	// moveGrid_�i�}�X�ڂ��ړ���������x�N�g���j���v�Z
	// �����F�ړ�����(Enum::Dir4�^)
	// �߂�l�F�ړ���̃}�X�̍��W(nextGridPos_�ɓ����p)
	tnl::Vector2i calcMoveGrid( Enum::Dir4 moveDir );
	
private :

	// �X�e�[�W�̃|�C���^
	// �V�[���Ő������Ă���Stage�N���X����A�X�e�[�W�̔z��̏��������Ă��邽�߂Ɏg�p
	std::shared_ptr<Stage> stage_;

	// ���݂�transform���
	// ���W(pos_)�Ɖ�]�̏��(rot_)���g�p
	ito::Transform nowTransform_;

	// ����transform���
	// ���W(pos_)�Ɖ�]�̏��(rot_)���g�p
	ito::Transform nextTransform_;

	// ���Ɉړ�������W(�X�e�[�W�̔z���)
	tnl::Vector2i nextGridPos_;

	// �}�X�ڏ���ړ���������̃x�N�g��
	// nextGridPos_ - gridPos_�ňړ��O�Ɍv�Z
	tnl::Vector2i moveGrid_;

	// �`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
	// tnl::Vector2i gridPos_;
	// �����݂̔z���ł̍��W��EntityBase�N���X�ɂ���
	// �擾����֐��FgetGridPos()
	// �`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

	// 1�t���[���ňړ������
	float moveVal_ = 0;

	// 1�t���[�����ŉ�]�������
	float rotValFrame_ = 3.0f;

	// ��]������ő��
	// seqRotateCheck�Œl�����A���t���[����]�����閈�ɒl������
	float rotValMax_ = 0;

	// ���̈ʒu�Ɉړ��ł��邩�ǂ����̃t���O
	bool isMove_ = true;

	// ���ʂ̌����̕ϐ���EntityBase�N���X�ɑ���

	// ���Ɍ��������̕ϐ�
	// Dir4�N���X�͕ʃt�@�C���Œ�`
	Enum::Dir4 nextDir_ = Enum::Dir4::UP;

	std::string seqNow_ = "seqIdle";

	// �v���C���[�̏�ԗp�̃V�[�P���X
	tnl::Sequence<Player> seq_ = tnl::Sequence<Player>(this, &Player::seqIdle);

	// �ҋ@���̃V�[�P���X
	bool seqIdle(const float delta_time);
	// �ړ�����������V�[�P���X
	bool seqMoveCheck(const float delta_time);
	// ��]����������V�[�P���X
	bool seqRotateCheck(const float delta_time);
	// �ړ����s���V�[�P���X
	bool seqMoving(const float delta_time);
	// ��]���s���V�[�P���X
	bool seqRotating(const float delta_time);
};
