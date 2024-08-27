#include "BattleCharacterBase.h"

// �R���X�g���N�^
// �����FstartPos...�J�n�ʒu, objSize...�쐬����L�����N�^�[�̑傫��, objName...���O
// �ړ��O�̍��W�͊J�n�ʒu�ŏ�����
BattleCharacterBase::BattleCharacterBase(tnl::Vector3 startPos, float objSize, std::string fileName)
	: beforePos_(startPos), attackSize_(objSize * 1.5), SpriteObjectBase(startPos, objSize, fileName) {

	// SpriteObjectBase�N���X�̊֐�
	// �e�N�X�`����\������p��plane�̔z����쐬����
	CreateSpriteObjArray(fileName);

	// �X�e�[�^�X�̃N���X�𐶐�
	status_ = std::shared_ptr<StatusCharacter>(new StatusCharacter());

	return;
}

// �f�X�g���N�^
BattleCharacterBase::~BattleCharacterBase() {

}

// �X�V�p�̊֐�
// *********************************************************************
// �p�����update�֐��ł��A���̃N���X��update�֐����Ăяo������!!
// *********************************************************************
// �������e
// 1.
void BattleCharacterBase::update(float delta_time) {

	// ��Ԃ�Active�łȂ��Ƃ��ȉ��̏������s��Ȃ�
	if (!isActive_) {
		return;
	}

	SpriteObjectBase::update(delta_time);

	// �U���̏��������s
	auto it = attackList_.begin();
	while (it != attackList_.end()) {
		(*it)->update(delta_time);

		if ((*it)->getIsEnd()) {

			it = attackList_.erase(it);

		}
		else {
			++it;
		}
	}

	// ���G���Ԃ̏���
	// ���G��Ԃ̎��ȉ��̏������s��
	if (!canTakeDamage_) {

		// ���G���Ԃ̃J�E���g�����炷
		invincibleTimeCount_ += delta_time;
		// �_�ŃJ�E���g�𑝂₷
		invincibleBlinkCount_ += delta_time;

		// �c��̖��G���Ԃ����G���Ԃ̍ő�l���������Ƃ�
		if (invincibleTimeCount_ >= invincibleTimeMax_) {

			// �_���[�W���󂯂��Ԃɂ���
			canTakeDamage_ = true;

			// �`�悷���Ԃɂ���
			isDisplay_ = true;

			// ���G�̎��Ԃ����Z�b�g
			invincibleTimeCount_ = 0;

			// �_�Ŏ��Ԃ̃J�E���g�����Z�b�g
			invincibleBlinkCount_ = 0;
		}

		// �_�Ŏ��Ԃ��Ԋu���������Ƃ�
		if (invincibleBlinkCount_ >= invincibleBlinkInterval_) {

			// �`���Ԃ����ւ���
			isDisplay_ = !isDisplay_;
			// �_�Ŏ��Ԃ̃J�E���g�����Z�b�g
			invincibleBlinkCount_ = 0;
		}


	}

}


// �`��p�̊֐�
// *********************************************************************
// �p�����draw�֐��ł��A���̃N���X��draw�֐����Ăяo������!!
// *********************************************************************
// �������e
// 1.�`�悷�郁�b�V���̍��W���X�V
// 2.�U���̃��b�V���̕`��
void BattleCharacterBase::draw(const std::shared_ptr<dxe::Camera>& camera ) {

	// ��Ԃ�Active�łȂ��Ƃ��ɂ͈ȉ��̏������s��Ȃ�
	if (!isActive_) {
		return;
	}

	if (canTakeDamage_ && !isDisplay_) {
		isDisplay_ = true;
	}

	// ���g��`��
	if (isDisplay_) {
		SpriteObjectBase::draw(camera);
	}

	// �U���̃��b�V����`��
	auto it = attackList_.begin();
	while (it != attackList_.end()) {

		if( (*it)->getIsActive() ){

			(*it)->draw(camera);

		}

		++it;
	}

	return;

}


// �L�����N�^�[���ړ�������֐�
// �p����̂��ꂼ��̃L�����N�^�[�N���X�ŃL�����N�^�[�𓮂����ۂɂ��̊֐���p���ē�����
// 
// �����FmoveVector...�ړ�����, moveVectorMag...�ړ��ʂ̔{���A����̍s���̎��݈̂ړ����x���グ�����ꍇ�Ɏg�p�A�f�t�H���g��1�{
void BattleCharacterBase::MoveCharacter(float delta_time, tnl::Vector3 moveVector, float moveVectorMag) {

	// ���݂̍��W�ɑ΂��Ĉړ��ʂ����Z���鏈��
	// �ړ��ʂ͈ړ������ƈړ��ʁi�Ɣ{���j���������킹�Čv�Z
	transform_.setPos_(transform_.getPos_() + moveVector * moveValue_ * moveVectorMag * delta_time);

	return;
}


// �_���[�W���󂯂�֐�
// �����Fdamage...�󂯂�_���[�W
void BattleCharacterBase::TakeDamage(float damage) {

	// �ȉ��̏����̎��������s�킸return����
	// �P�D��_���[�W��̖��G��Ԃ̂Ƃ�
	// �Q�D�̗͂�0�ȉ��̂Ƃ�
	if (!canTakeDamage_ || status_->getHp() <= 0 ) {
		return;
	}

	// �v�Z���ꂽ�_���[�W
	// �h��͂��_���[�W����������l
	// �v�Z���ʂ�1�ȉ��ɂȂ����Ƃ���1�_���[�W�Ƃ���
	float calcDamage = ((damage - status_->getDef() > 1) ? (damage - status_->getDef()) : 1);

	// HP��calcDamage�̒l�����炷
	status_->setHp( status_->getHp() - calcDamage );

	// �̗͂�0�����ɂȂ����Ƃ�0���Z�b�g����
	if (status_->getHp() < 0) {
		status_->setHp(0);
	}


	// ���G��Ԃɂ���
	canTakeDamage_ = false;

	// ���G���Ԃ̃J�E���g�̃��Z�b�g
	invincibleTimeCount_ = 0;

	// �_�Ŏ��Ԃ̃��Z�b�g
	invincibleBlinkCount_ = 0;
}