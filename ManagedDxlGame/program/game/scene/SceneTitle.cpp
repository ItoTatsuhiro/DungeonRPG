#include "SceneTitle.h"
#include "ScenePlay.h"

// �R���X�g���N�^
SceneTitle::SceneTitle() {

	// �L�����N�^�[�̕��s�A�j���[�V�����ǂݍ���
	characterAnim_ = ito::ResourceManager::GetInstance()->loadAnimGraph("travellerWalkAnimLtoR.png");
	// �w�i�摜�ǂݍ���
	backGpc_ = ito::ResourceManager::GetInstance()->loadGraph("kaidou0331_800b.jpg");
	// �^�C�g�����S�p�摜�ǂݍ���
	titleGpc_ = ito::ResourceManager::GetInstance()->loadGraph("DungeonCrawl_Title.png");

	// �L�����N�^�[�J�n�ʒu
	characterStartPos_ = { -100, 580, 0 };
	characterDrawPosFinal_ = { DXE_WINDOW_WIDTH >> 1, 580, 0 };
	// �L�����N�^�[�`��̏����ʒu��ݒ�
	characterDrawPos_ = characterStartPos_;

	// BGM�ǂݍ���
	titleBGMhdl_ = ito::ResourceManager::GetInstance()->loadSoundMem("�t�@���^�W�[7-�X-.mp3");
}



// �f�X�g���N�^
SceneTitle::~SceneTitle() {



}


// ���t���[���̏���
void SceneTitle::update(float delta_time) {

	// BGM�Đ�
	if (!isPlayingBgm_) {
		PlaySoundMem(titleBGMhdl_, DX_PLAYTYPE_LOOP);
		isPlayingBgm_ = true;
	}


	if ( !isWaiting_) {
		// �L�����N�^�[�̈ړ�
		characterDrawPos_.x += characterMoveValue_;

		// ����̈ʒu�܂ŃL�����N�^�[���ړ������Ƃ��Q�[���J�n�ł����Ԃɂ���
		if (characterDrawPos_.x >= characterDrawPosFinal_.x && !canStart_) {

			characterDrawPos_ = characterDrawPosFinal_;

			isWaiting_ = true;

			canStart_ = true;

			animDisplayCount_ = 0;

			animframe_ = 1;
		}

		// �A�j���[�V�����p�摜�؂�ւ�
		if (animDisplayCount_ > animDisplayTime_) {

			animDisplayCount_ = 0;

			animframe_ = (animframe_ + 1) % animframeMax_;
		}
		else {
			animDisplayCount_ += delta_time;
		}

	}


	if (isWaiting_ && canStart_) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			isWaiting_ = false;

		}


	}

	// �L�����N�^�[����ʊO�܂ňړ�������V�[���؂�ւ�
	if (characterDrawPos_.x >= DXE_WINDOW_WIDTH + 120) {

		// BGM��~
		StopSoundMem(titleBGMhdl_);

		ito::GameManager::GetInstance_()->changeScene( std::shared_ptr<ScenePlay>( new ScenePlay()) );

	}

}


// �`��̏���
void SceneTitle::draw() {

	// �w�i�`��
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 1.8f, 0, backGpc_, true);

	SetFontSize(80);

	// �^�C�g�����S�摜�\��
	DrawRotaGraph(titleGpcPos_.x, titleGpcPos_.y, 2,  0.05 * tnl::PI, titleGpc_, true);
	// �L�����N�^�[�`��
	DrawRotaGraph(characterDrawPos_.x, characterDrawPos_.y, 8, 0, (*characterAnim_)[animframe_], true);


	if (isWaiting_) {

		SetFontSize(40);
		DrawStringEx(100, 450, 0, "Enter�ŃQ�[���X�^�[�g");

	}
}