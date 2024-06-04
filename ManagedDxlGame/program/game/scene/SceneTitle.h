#pragma once
#include "../../dxlib_ext/dxlib_ext.h"


// �^�C�g����ʗp�̃N���X
class SceneTitle final : public ito::SceneBase {
public:
	// �R���X�g���N�^
	SceneTitle();
	// �f�X�g���N�^
	~SceneTitle();
	// ���t���[���̏���
	void update(float delta_time) override;
	// �`��̏���
	void draw() override;



private:

	// �L�����N�^�[�̃A�j���[�V�����p�摜
	std::shared_ptr< std::vector<int> > characterAnim_;

	// �w�i�摜
	int backGpc_;

	// �^�C�g���̉摜
	int titleGpc_;

	// �^�C�g���摜�̕\���ʒu
	tnl::Vector3 titleGpcPos_ = { 800, 400, 0 };

	// �ҋ@�����ǂ����̃t���O
	bool isWaiting_ = false;

	// �J�n�ł��邩�ǂ����̃t���O
	bool canStart_ = false;

	// �L�����N�^�[�̕`��ʒu
	tnl::Vector3 characterDrawPos_;

	// �ŏI�I�ɃL�����N�^�[������ʒu
	tnl::Vector3 characterDrawPosFinal_;

	// �L�����N�^�[���ړ����n�߂�ʒu
	tnl::Vector3 characterStartPos_;

	// �L�����N�^�[���ړ����Ă���ړ���
	float characterMoveValue_ = 5;

	// �\������A�j���[�V�����̉摜
	int animframe_ = 0;
	// �A�j���[�V�����̍ő�t���[��
	int animframeMax_ = 4;

	// �\�����Ԃ̃J�E���g
	float animDisplayCount_ = 0;
	// �A�j���[�V������؂�ւ��鎞��
	float animDisplayTime_ = 0.15f;
};
