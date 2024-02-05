#pragma once
#include "../../dxlib_ext/dxlib_ext.h"



// �I�u�W�F�N�g�̌��ɂȂ�N���X
// ���A�Ǔ��̃I�u�W�F�N�g���쐬����ۂ͂�����p������
class ObjectBlockBase : public ito::Transform {
public :
	// �R���X�g���N�^
	// �������W������ꍇ�͈�����tnl::Vector3�^�œ����
	explicit ObjectBlockBase(float gridSize = 50.0f, tnl::Vector3 pos = {0, 0, 0}) : gridSize_(gridSize), ito::Transform(pos) {}
	// �f�X�g���N�^
	virtual ~ObjectBlockBase(){}

	// �A�b�v�f�[�g�֐�
	virtual void update(float delta_time) {};
	// �`��֐�
	virtual void draw(std::shared_ptr<dxe::Camera> camera) {}

	// �\������I�u�W�F�N�g�𐶐�����֐�
	// ��������z�֐��Ƃ��ĉ񂷂��ƂŁA��C�ɃI�u�W�F�N�g���쐬�\
	virtual void CreateObj(){}


	//-----------------------------------------------------------------------
	// �Q�b�^�[

	// hasCollision�̃Q�b�^�[
	bool getHasCollision() const { return hasCollision_; }

	// canMove�̃Q�b�^�[
	bool getCanMove() const { return canMove_; }
	
	// ���W���擾����Q�b�^�[
	// �p����Ń��b�V���̍��W���擾�ł���悤�֐���p�ӂ��邱��
	// virtual tnl::Vector3 getMeshPos() = 0 { return tnl::Vector3{ -1, -1, -1 }; }

	//-----------------------------------------------------------------------
	// �Z�b�^�[

	// hasCollision_�̃Z�b�^�[
	void setHasCollision(bool setHasCollision) { hasCollision_ = setHasCollision; }

	// canMove_�̃Z�b�^�[
	void setCanMove(bool setCanMove) { canMove_ = setCanMove; }

protected :

	// �I�u�W�F�N�g�������蔻��������Ă��邩��\���ϐ�
	bool hasCollision_ = true;
	// ���̃I�u�W�F�N�g���ړ��ł��邩
	bool canMove_ = true;

	// �傫���̕ϐ�
	// �����l����{�̑傫���ƂȂ�
	// { x�����̑傫��, y�����̑傫��, z�����̑傫�� }
	float gridSize_ = 50.0f;

	// �V��܂ł̍���
	int height_ = 3;

};

