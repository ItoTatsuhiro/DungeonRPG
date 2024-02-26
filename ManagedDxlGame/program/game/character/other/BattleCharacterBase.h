#pragma once

#include "../../base/SpriteObjectBase.h"
#include "StatusCharacter.h"

// �o�g���V�[���ł̃L�����N�^�[�̃x�[�X�ƂȂ�N���X
// *************************************************************
// �p����̃N���X�ł́Aupdate,draw�֐������ꂼ��Ăяo�����ƁI
// *************************************************************
// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�L�����N�^�[�̑傫��,
//		std::string objectName...�I�u�W�F�N�g(�L�����N�^�[)��
class BattleCharacterBase : public SpriteObjectBase {
public :

	// �R���X�g���N�^
	BattleCharacterBase(tnl::Vector3 startPos, float objSize, std::string objectName);
	// �f�X�g���N�^
	virtual ~BattleCharacterBase();

	// �X�V�p�̊֐�
	// *********************************************************************
	// �p�����update�֐��ł��A���̃N���X��update�֐����Ăяo������!!
	// *********************************************************************
	virtual void update(float delta_time) = 0;

	// �`��p�̊֐�
	// *********************************************************************
	// �p�����draw�֐��ł��A���̃N���X��draw�֐����Ăяo������!!
	// *********************************************************************
	void draw(std::shared_ptr<dxe::Camera> camera) = 0;

	// ******************************************************************************
	// �ȉ��Q�b�^�[

	// �ړ��O�̍��W���擾����֐�
	// ���W�̕␳���̍ۂɎg�p
	inline tnl::Vector3 getBeforePos() const { return beforePos_; }

protected :

	// �ړ��O�̍��W
	// ���W�̕␳�̍ۂɂ��̍��W���g�p����
	tnl::Vector3 beforePos_;

	// �ړ���
	float moveValue_ = 5;


	// �ʏ펞�̃X�e�[�^�X
	// �ϓ������ۂ̃X�e�[�^�X�����ɖ߂��̂Ɏg�p
	StatusCharacter baseStatus_;
	// ���炩�̗v���ŕϓ������X�e�[�^�X
	// (�o�t�A�f�o�t��)
	StatusCharacter changeStatus_;

	// �������Ă���U���̃��X�g
	std::list<std::shared_ptr<SpriteObjectBase>> attackList_;

};