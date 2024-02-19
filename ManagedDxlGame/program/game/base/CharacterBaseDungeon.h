#pragma once

#include "EntityBase.h"


//---------------------------------------------------
// �O���錾

class Stage;


// �v���C���[�E�G�L�����N�^�[�Ɍp������x�[�X�N���X
// �����FgridSize...�X�e�[�W�̃}�X�̑傫��
// startPos...�������ꂽ�ۂ̃}�b�v��ł̈ʒu
class CharacterBaseDungeon : public EntityBase {
public :

	// �R���X�g���N�^
	// �����FgridSize...�X�e�[�W�̃}�X�̑傫��
	// startPos...�������ꂽ�ۂ̃}�b�v��ł̈ʒu
	CharacterBaseDungeon( float gridSize, tnl::Vector2i startPos );

	// �f�X�g���N�^
	virtual ~CharacterBaseDungeon();

	// ���t���[���������s���֐�
	virtual void update( float delta_time );

	// �`�揈���̊֐�
	virtual void draw();

	// �v���C���[��Transform���擾����֐�
	 ito::Transform getTransform() const { return nowTransform_; }

	

protected :

	// �ړ����s���֐�
	// Player, Enemy���̈ړ����s���ۂ͂��̊֐����g�p����
	void Moving(float delta_time);

	// ��]���s���֐�
	// Plauer, Enemy���̉�]���s���ۂ͂��̊֐����g�p����
	void Rotating(float delta_time);

	// �s�����I�����Ă��邩�ǂ����̃t���O
	// Move, Rotate���̏�������false�ɂ��邱��
	bool finishAction_ = true;

	// ���Ɉړ�����ړ�����v�Z����֐�
	// moveGrid_�i�}�X�ڂ��ړ���������x�N�g���j���v�Z
	// �����F�ړ�����(Enum::Dir4�^)
	// �߂�l�F�ړ���̃}�X�̍��W(nextGridPos_�ɓ����p)
	tnl::Vector2i calcMoveGrid(Enum::Dir4 moveDir);

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




};