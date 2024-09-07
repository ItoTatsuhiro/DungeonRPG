#include "SceneClear.h"

#include "SceneTitle.h"

// �R���X�g���N�^
SceneClear::SceneClear() {

	backGpc_ = ito::ResourceManager::GetInstance()->loadGraph("grass.png");

	// �L�����N�^�[�̕��s�A�j���[�V�����ǂݍ���
	characterAnim_ = ito::ResourceManager::GetInstance()->loadAnimGraph("travellerWalkAnimLtoR.png");

	characterStartPos_ = { -100, 450, 0 };
	characterDrawPosFinal_ = { DXE_WINDOW_WIDTH >> 1, 450, 0 };

	characterDrawPos_ = characterStartPos_;

	// BGM�ǂݍ���
	clearBGMhdl_ = ito::ResourceManager::GetInstance()->loadSoundMem("�t�@���^�W�[-����-.mp3");

	// ���ʒ���
	ChangeVolumeSoundMem(50, clearBGMhdl_);
}



// �f�X�g���N�^
SceneClear::~SceneClear() {



}


// ���t���[���̏���
void SceneClear::update(float delta_time) {

	if (!isPlayingBgm_) {

		PlaySoundMem(clearBGMhdl_, DX_PLAYTYPE_LOOP);

		isPlayingBgm_ = true;
	}


	if (characterDrawPos_.x < characterDrawPosFinal_.x) {
		// �ړ�
		characterDrawPos_.x += characterMoveValue_;

	}
	else if (characterDrawPos_.x >= characterDrawPosFinal_.x && !canChangeScene_) {

		characterDrawPos_ = characterDrawPosFinal_;

		canChangeScene_ = true;
	}


	// �A�j���[�V�����̐؂�ւ��p�̏���
	if (animDisplayCount_ > animDisplayTime_) {

		animDisplayCount_ = 0;

		animframe_ = (animframe_ + 1) % animframeMax_;
	}
	else {
		animDisplayCount_ += delta_time;
	}

	if (canChangeScene_) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			// BGM��~
			StopSoundMem(clearBGMhdl_);

			// �^�C�g���V�[���ɐ؂�ւ�
			ito::GameManager::GetInstance_()->changeScene(std::shared_ptr<SceneTitle>(new SceneTitle()));
		}

	}


}


// �`��̏���
void SceneClear::draw() {

	// �w�i�`��
	DrawRotaGraph(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 2, 0, backGpc_, true);

	SetFontSize(80);

	DrawStringEx(450, 150, -1, "�E�o�����I");

	DrawRotaGraph(characterDrawPos_.x, characterDrawPos_.y, 6.5, 0, (*characterAnim_)[animframe_], true);

	SetFontSize(50);

	DrawStringEx(450, 530, -1, "Enter�Ń^�C�g���ɖ߂�");

}