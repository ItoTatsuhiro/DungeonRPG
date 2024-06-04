#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../other/Enum.h"

// �����蔻��p��Box�ƁA�e�N�X�`����\��t���ĉ�ʂɕ\������p��plane�̔z������N���X
// �g�p�ӏ��F�L�����N�^�[�A�U���̃G�t�F�N�g��
// ���������ɗp�r�ɉ����Čp�����Ďg�p
class SpriteObjectBase {
public :

	// �R���X�g���N�^
	// �����FstartPos...�J�n�ʒu, meshSize...�����蔻���Box�̑傫��, objName...���̃I�u�W�F�N�g�̖��O
	SpriteObjectBase(tnl::Vector3 startPos, float meshSize, std::string objName);

	// �f�X�g���N�^
	virtual ~SpriteObjectBase();


	// �X�V�p�̊֐�
	// *********************************************************************
	// �p�����update�֐��ł��A���̃N���X��update�֐����Ăяo������!!
	// *********************************************************************
	virtual void update(float delta_time) = 0;

	// �`��p�̊֐�
	// �����F�`��p�̃J�����A�f�t�H���g��nullptr�ɐݒ肵�Ă��邪��{����邱��
	// *********************************************************************
	// �p�����draw�֐��ł��A���̃N���X��draw�֐����Ăяo������!!
	// *********************************************************************
	virtual void draw(std::shared_ptr<dxe::Camera> camera = nullptr) = 0;

	// spriteObjArray_�̒��g�𐶐�����֐�
	// �����FtextureFileName...�\��t����e�N�X�`���̃t�@�C����
	void CreateSpriteObjArray(std::string textureFileName);

	// ******************************************************************************
	// �ȉ��Q�b�^�[

	// isActive_�̃Q�b�^�[
	inline bool getIsActive() const { return isActive_; }

	// transform_���擾����Q�b�^�[
	inline ito::Transform getTransform() const { return transform_; }

	// transform_��pos_�v�f���擾����Q�b�^�[
	inline tnl::Vector3 getPos() const { return transform_.getPos_(); }

	// hitBox_�̃Q�b�^�[
	inline std::shared_ptr<ito::Object3D> getHitBox() const { return hitBox_; }

	// frontDir_�̃Q�b�^�[
	inline Enum::Dir4 getFrontDir() const { return frontDir_; }

	// meshSize_�̃Q�b�^�[
	inline float getMeshSize() const { return meshSize_; }

	// ******************************************************************************
	// �ȉ��Z�b�^�[

	// transform�̃Z�b�^�[
	inline void setTransform(ito::Transform transform) { transform_ = transform; }

	// transform��pos_�v�f�̃Z�b�^�[
	inline void setPos(tnl::Vector3 newPos) { transform_.setPos_(newPos); }

	// frontDir�̃Z�b�^�[
	inline void setFrontDir(Enum::Dir4 frontDir) { frontDir_ = frontDir; }


protected :

	// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ̃t���O
	bool isActive_ = true;

	// �I�u�W�F�N�g�̖��O
	std::string objName_;

	// �I�u�W�F�N�g�̍��W���̏��
	// �����ύX����ƁAhitBox_��spriteObj_�̍��W���ύX�ł���悤�ɂ���
	ito::Transform transform_;

	// �����蔻��p��Box
	// �e�N�X�`���͊�{�I�ɖ���
	// �R���X�g���N�^�Ő���
	std::shared_ptr<ito::Object3D> hitBox_ = nullptr;

	// �e�N�X�`����\��t����plane�p�̔z��
	std::vector<std::vector<std::shared_ptr<ito::Object3D>>> spriteObjArray_;
	// �e�N�X�`���p
	// CreateSpriteObjArray�֐��œǂݍ���
	std::shared_ptr<dxe::Texture> texture_ = nullptr;
	// �e�N�X�`���̕�����
	// CreateSpriteObjArray�֐��œǂݍ���
	tnl::Vector2i textureCutNum_ = { 0, 0 };

	// �A�j���[�V�����p�̃��b�V����؂�ւ��鎞��
	const float animChangeTime_ = 0.15;
	// ���݂̃A�j���[�V�������Đ����Ă��鎞��
	// �ړ����̃A�j���[�V�����͎~�߂��ۂ�0�Ƀ��Z�b�g����
	float animChangeCount_ = 0;
	// �\�����̃I�u�W�F�N�g�̔ԍ�
	tnl::Vector2i displayObj_ = { 0, 0 };

	// ���b�V���̑傫��
	float meshSize_ = 50;

	// �����Ă�������̕ϐ�
	Enum::Dir4 frontDir_ = Enum::Dir4::UP;
	// �A�j���[�V�����̕���
	// �A�j���[�V���������E�̊G�����Ȃ��ꍇ���A����ŊǗ�����
	Enum::Dir4 animFrontDir_ = Enum::Dir4::UP;



};