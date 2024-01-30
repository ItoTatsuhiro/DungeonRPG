#pragma once

#include "EntityBase.h"


//---------------------------------------------------
// �O���錾

class Stage;


class CharacterBase : public EntityBase {
public :

	// �R���X�g���N�^
	// �����FgridSize...�X�e�[�W�̃}�X�̑傫��
	// startPos...�������ꂽ�ۂ̃}�b�v��ł̈ʒu
	CharacterBase( float gridSize, tnl::Vector2i startPos );

	// �f�X�g���N�^
	virtual ~CharacterBase();

	// ���t���[���������s���֐�
	void update( float delta_time );

	// �`�揈���̊֐�
	void draw();


	const ito::Transform getTransform(){ }


protected :

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

	// �V�[�P���X����p�ϐ�
	tnl::Sequence<CharacterBase> seq_ = tnl::Sequence<CharacterBase>(this, &CharacterBase::seqIdle);

	// �ҋ@���̃V�[�P���X
	// �v���C���[�ƓG���ꂼ��Ōʂ�
	virtual bool seqIdle(const float delta_time);
	// �ړ�����������V�[�P���X
	bool seqMoveCheck(const float delta_time);
	// ��]����������V�[�P���X
	bool seqRotateCheck(const float delta_time);
	// �ړ����s���V�[�P���X
	bool seqMoving(const float delta_time);
	// ��]���s���V�[�P���X
	bool seqRotating(const float delta_time);
};