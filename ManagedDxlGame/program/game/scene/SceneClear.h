#pragma once
#include "../../dxlib_ext/dxlib_ext.h"




// ��ɃQ�[���̃��C���̕����̏��������s����N���X
// ���ۂɓ�����s���T�u�V�[�����Ǘ��������������
// �T�u�V�[���Ԃł����̕K�v�ȃf�[�^��ێ��������������
class SceneClear final : public ito::SceneBase {
public:
	// �R���X�g���N�^
	SceneClear();
	// �f�X�g���N�^
	~SceneClear();
	// ���t���[���̏���
	void update(float delta_time) override;
	// �`��̏���
	void draw() override;




private:
	// �^�C�g���ɖ߂邱�Ƃ��ł��邩�ǂ����̊֐�
	bool canChangeScene_ = false;

	// �w�i�摜
	int backGpc_;

	// �ȉ��A�j���[�V�����֌W

	// �L�����N�^�[�̃A�j���[�V�����p�摜
	std::shared_ptr< std::vector<int> > characterAnim_;

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
