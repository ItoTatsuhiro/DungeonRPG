#include "BattlePlayer.h"
#include "../../manager/InputManager.h"
#include "../../manager/ObjectManager.h"

#include "../Battle/attack/Attack.h"

// �R���X�g���N�^
// �����Ftnl::Vector3 startPos...�J�n�ʒu, float objSize...�I�u�W�F�N�g�̑傫��, std::string objectName...�I�u�W�F�N�g��
// �ړ��O�̍��W�͊J�n�ʒu�ŏ�����
BattlePlayer::BattlePlayer(tnl::Vector3 startPos, float objSize, std::string objectName) 
	: attackSize_(meshSize_ * 2), BattleCharacterBase(startPos, objSize, objectName){


	// SpriteObjectBase�N���X�̊֐�
	// �e�N�X�`����\������p��plane�̔z����쐬����
	CreateSpriteObjArray("travellerAnim.png");

	// �\�����郁�b�V���̏����ݒ�
	displayObj_ = tnl::Vector2i( 1, textureCutNum_.y - 2);


	return;
}

// �f�X�g���N�^
BattlePlayer::~BattlePlayer() {


	return;
}

// �X�V�p�̊֐�
void BattlePlayer::update(float delta_time) {

	seq_.update(delta_time);

	// �L�����N�^�[�x�[�X�̍X�V
	BattleCharacterBase::update(delta_time);

	return;
}

// �`��p�̊֐�
void BattlePlayer::draw( std::shared_ptr<dxe::Camera> camera) {
	// �f�o�b�O�p
	// DrawStringEx(100, 100, -1, "playerPos = x : %f, y : %f, z : %f", hitBox_->get_mesh_()->pos_.x, hitBox_->get_mesh_()->pos_.y, hitBox_->get_mesh_()->pos_.z);

	// �\������摜�p�̃��b�V���̍��W�𓖂��蔻��p�̃��b�V���̈ʒu�ɍX�V
	spriteObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->pos_ = hitBox_->get_mesh_()->pos_;

	spriteObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->render(camera);


	auto it = attackList_.begin();
	while (it != attackList_.end()) {
		(*it)->draw(camera);

		++it;
	}

	return;
}


// �ړ��̊֐�
// �����蔻��̃��b�V��(hitBox)�����炵�A
void BattlePlayer::Move(float delta_time) {

	// �S�Ă̕����L�[��������Ă��鎞or����������Ă��Ȃ��Ƃ�
	if ((InputManager::GetInstance()->KeyDownUp() && InputManager::GetInstance()->KeyDownLeft()
		&& InputManager::GetInstance()->KeyDownDown() && InputManager::GetInstance()->KeyDownRight())
		|| (!InputManager::GetInstance()->KeyDownUp() && !InputManager::GetInstance()->KeyDownLeft()
			&& !InputManager::GetInstance()->KeyDownDown() && !InputManager::GetInstance()->KeyDownRight())) {

		// �A�j���[�V�����̃J�E���g��0�ɂ���
		animChangeCount_ = 0;

		displayObj_.x = 1;

		// �ȉ����������Ȃ�
		return;
	}

	// �ړ��O�ɍ��W���L�^����
	beforePos_ = hitBox_->get_mesh_()->pos_;

	// �������L�[�ɉ����č��W�����炷
	if (InputManager::GetInstance()->KeyDownUp()) {
		hitBox_->get_mesh_()->pos_.z += moveValue_;
		frontDir_ = Enum::Dir4::UP;
	}
	if (InputManager::GetInstance()->KeyDownDown()) {
		hitBox_->get_mesh_()->pos_.z -= moveValue_;
		frontDir_ = Enum::Dir4::DOWN;
	}
	if (InputManager::GetInstance()->KeyDownLeft()) {
		hitBox_->get_mesh_()->pos_.x -= moveValue_;
		animFrontDir_ = Enum::Dir4::LEFT;
		frontDir_ = Enum::Dir4::LEFT;
		displayObj_.y = 3;
	}
	if (InputManager::GetInstance()->KeyDownRight()) {
		hitBox_->get_mesh_()->pos_.x += moveValue_;
		animFrontDir_ = Enum::Dir4::RIGHT;
		frontDir_ = Enum::Dir4::RIGHT;
		displayObj_.y = 2;
	}

	if (animChangeCount_ >= animChangeTime_) {
		displayObj_.x = (displayObj_.x + 1) % textureCutNum_.x;
		animChangeCount_ = 0;
	}
	else {
		animChangeCount_ += delta_time;
	}

	return;
}


// �U���̏����ɓ��邽�߂̊֐�
// �U���̂��߂̃L�[���͂��������Ƃ��V�[�P���X��؂�ւ��鏈�����s��
// �܂��A�U���̏����̑O�̏������s��
void BattlePlayer::OnAttackKey() {

	// �U���̂��߂̓��͂��������ۂɃV�[�P���X��؂�ւ��鏈��
	// �����𖞂����Ă����ꍇ�͍U���Ɉڂ�O�̏������s��
	// �L�[�𑝂₷or�ύX����ۂ͈ȉ��̏�����ύX���邱��
	if (InputManager::GetInstance()->MouseClickTriggerLeft()) {
		seq_.change(&BattlePlayer::seqAttack);
		// �A�j���[�V�����̕\�����Ԃ̃J�E���g��0�ɂ���
		animChangeCount_ = 0;

		// �����ɉ����ĕ\������摜�̌�����ύX
		displayObj_.y = (animFrontDir_ == Enum::Dir4::LEFT) ? 1 : 0;
		displayObj_.x = 0;

		tnl::Vector3 attackPos;

		if (frontDir_ == Enum::Dir4::UP) {
			attackPos = hitBox_->get_mesh_()->pos_ + tnl::Vector3{ 0, 0, attackSize_ };
		}
		else if (frontDir_ == Enum::Dir4::DOWN) {
			attackPos = hitBox_->get_mesh_()->pos_ + tnl::Vector3{ 0, 0, -attackSize_ };
		}
		else if (frontDir_ == Enum::Dir4::LEFT) {
			attackPos = hitBox_->get_mesh_()->pos_ + tnl::Vector3{ -attackSize_ , 0, 0 };
		}
		else if (frontDir_ == Enum::Dir4::RIGHT) {
			attackPos = hitBox_->get_mesh_()->pos_ + tnl::Vector3{ attackSize_ , 0, 0 };
		}

		attackList_.emplace_back(std::shared_ptr<Attack>(new Attack(attackPos, attackSize_, "slashAnim.png", animFrontDir_)));
	}

	return;
}


// �ҋ@���̃V�[�P���X
// �ړ��͑ҋ@���ɍs�����Ƃ��ł���
bool BattlePlayer::seqIdle(const float delta_time) {

	// ���͂��������ۂɈړ����s��
	Move(delta_time);

	// �U���̓��͂̊m�F
	OnAttackKey();

	return true;

}

// �U���̃V�[�P���X
// ���͂��������ۂ�Idle����؂�ւ���
bool BattlePlayer::seqAttack(const float delta_time) {	

	if (animChangeCount_ > animChangeTime_ / 3) {
		// ���̉摜�̃��b�V���ɐ؂�ւ�
		++displayObj_.x;
		// �\�����Ԃ�0�Ƀ��Z�b�g����
		animChangeCount_ = 0;

		// �U�����I������ۂɍU���̏�������J�ڂ��鏈��
		if (displayObj_.x >= textureCutNum_.x) {

			// �\�����郁�b�V����؂�ւ�
			displayObj_.x = 0;
			displayObj_.y = (animFrontDir_ == Enum::Dir4::LEFT) ? 3 : 2;

			seq_.change(&BattlePlayer::seqIdle);
		}

	}
	else {
		animChangeCount_ += delta_time;
	}

	return true;

}