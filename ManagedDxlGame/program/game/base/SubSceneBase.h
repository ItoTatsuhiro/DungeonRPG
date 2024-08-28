#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

// �T�u�V�[���x�[�X�N���X
// �V�[�����ł���ɃV�[����������ۂɍ쐬����T�u�V�[���̍쐬�ɗp����N���X
// �ȉ��͏������z�֐�
// �P�Dvoid update(float delta_time) ... �X�V�p�̊֐�
// �Q�Dvoid draw() ... �`��p�̊֐�
class SubSceneBase {
public :
	// �R���X�g���N�^
	SubSceneBase(){}
	// �f�X�g���N�^
	virtual ~SubSceneBase(){}

	// �X�V�p�̊֐�
	// �������z�֐�
	virtual void update(float delta_time){};
	// �`��p�̊֐�
	// �������z�֐�
	virtual void draw(){};

	// �T�u�V�[����؂�ւ���ۂɌĂяo���֐�
	virtual void ChangeSubScene() = 0;
};