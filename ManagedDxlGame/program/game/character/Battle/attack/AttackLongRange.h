#pragma once

#include "AttackBase.h"

// *****************************************************************
//	���ꑱ�������I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I
// ******************************************************************

// �������U���̃N���X
// �U���̓����蔻����ړ�����悤�ɂ����N���X
class AttackLongRange : public AttackBase{
public :

	// �R���X�g���N�^
	// �����F
	// targetPos...�ڕW�n�_�̍��W
	// moveValue...�ړ������
	// startPos...�J�n�n�_�̍��W
	// size...�傫��
	// fileName...�t�@�C����
	// front...���ʂ̕���
	// charaType...�U���̃L�����N�^�[����
	// damage...�_���[�W
	AttackLongRange(const tnl::Vector3& targetPos, float moveValue, const tnl::Vector3& startPos, float size, std::string fileName, Enum::eDir4 front, eCharaType charaType, float damage = 1.0f);

	// �f�X�g���N�^
	~AttackLongRange();


	// �X�V�p�̊֐�
	void update(const float delta_time);

	// �`��p�̊֐�
	void draw(const std::shared_ptr<dxe::Camera>& camera);


	// �V�����ڕW�n�_���Z�b�g����֐�
	// �ǔ�����e�����쐬����ۂɎg�p
	// targetPos_�̃Z�b�g�݂̂łȂ��AmoveDir_���ēx�v�Z���s��
	void SetNewTargetPos(const tnl::Vector3& newTargetPos);


protected :


	// �ړ���ƂȂ�ڕW�n�_
	// �R���X�g���N�^�ŏ�����
	tnl::Vector3 targetPos_;


	// �P�ʉ����ꂽ�ړ������̃x�N�g��
	// �R���X�g���N�^���Ōv�Z
	tnl::Vector3 moveDir_;


	// �ړ��O�̍��W
	tnl::Vector3 beforePos_;

	// �ړ������
	// �R���X�g���N�^�ŏ�����
	float moveValue_;

};