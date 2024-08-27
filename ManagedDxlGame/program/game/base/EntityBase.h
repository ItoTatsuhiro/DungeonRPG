#pragma once


#include "../../dxlib_ext/dxlib_ext.h"

#include "../other/Enum.h"

// �}�b�v��ɔz�u�����G���e�B�e�B�̌��ƂȂ�N���X
// �}�b�v��ł̍��W(���݂��Ă���}�X��)�����ɂ����̂Ɍp�����Ďg�p
// �����FstartPos...�}�b�v��ł̏����ʒu(���}�X�ڂɑ��݂��邩)�AgridSize...1�}�X�̏c���̑傫��
// �p����̗�F�v���C���[�A�G�l�~�[�A�A�C�e����
// 
class EntityBase : public ito::Object3D {
public :

	// �R���X�g���N�^
	// �����F���݂��Ă���}�X��
	EntityBase(tnl::Vector2i startPos, float gridSize);

	// �f�X�g���N�^
	virtual ~EntityBase();


	//----------------------------------------------------------------------------------------
	// �Q�b�^�[

	// gridPos_�̃Q�b�^�[
	// �߂�l�FgridPos_...�}�b�v��̃}�X�ڂ̈ʒu
	tnl::Vector2i getGridPos() { return gridPos_; }

	// dir_�̃Q�b�^�[
	// �߂�l�Fdir_...�����Ă������
	Enum::eDir4 getFrontDir() { return frontDir_; }

	//----------------------------------------------------------------------------------------
	// �Z�b�^�[

	// gridPos_�̃Z�b�^�[
	// �����FnewGridPos...�V�K�̃}�b�v��̈ʒu
	void setGridPos(tnl::Vector2i newGridPos) { gridPos_ = newGridPos; }

	// dir_�̃Z�b�^�[
	// �����FnewDir...�ύX����V��������
	void setDir(Enum::eDir4 newDir) { frontDir_ = newDir; }

protected :

	// ���݂���}�b�v��̃}�X�ڂ̈ʒu
	// ��ԍ���ɑ��݂��Ă���ꍇ, ( 0, 0 )
	// �R���X�g���N�^�ŏ�����
	tnl::Vector2i gridPos_;

	// 3D���W
	// gridPos_�ɉ��������W�ƂȂ�
	tnl::Vector3 pos_;

	// 1�}�X���̑傫��
	// �R���X�g���N�^�ŏ�����
	float gridSize_ = 0;

	// �����Ă��������\���ϐ�
	// Dir4�N���X�͕ʃt�@�C���Œ�`
	Enum::eDir4 frontDir_ = Enum::eDir4::UP;

};
