#include "AttackBase.h"
#include "../../../manager/ObjectManager.h"


// **************************************************************************
// �����炭����ōU���𔭐������鏈�����ł��Ă���̂ŁA
// �U���̔���������ʒu���̐ݒ���s�����ƁI�I�I
// **************************************************************************



// �R���X�g���N�^
// �����F���W�A�傫���A�t�@�C�����A���ʂ̕���(LEFT��RIGHT), �_���[�W
// Object3D�̃��b�V���𓖂��蔻��p�̃��b�V���Ƃ��č쐬����
AttackBase::AttackBase(tnl::Vector3 pos, float size, std::string fileName, Enum::eDir4 front, eCharaType charaType, float damage)
	: SpriteObjectBase(pos, size, fileName), charaType_(charaType), damage_(damage), isLoop_(false), isEnd_(false), isHit_(false), checkHitStage_(false)
{

	CreateSpriteObjArray(fileName);

	// �����蔻����쐬
	hitBox_ = ObjectManager::GetInstance()->createCube(size, fileName);
	hitBox_->get_mesh_()->pos_ = pos;


	displayObj_.y = (frontDir_ == Enum::eDir4::LEFT) ? 1 : 0;

}

// �f�X�g���N�^
AttackBase::~AttackBase() {

	// �s���̏I����`����K�v�����鎞�͈ȉ��̏������s��

	auto creatorAction = creatorAction_.lock();

	if (creatorAction) {

		// �s���̏I���t���O��true�ɂ���
		creatorAction->setIsFinished(true);

	}


}


// �X�V�p�̊֐�
void AttackBase::update(float delta_time) {

	// �A�N�e�B�u�łȂ��Ƃ��������Ȃ�
	if (!isActive_) {
		return;
	}

	// ���N���X�̍X�V
	SpriteObjectBase::update(delta_time);

	if (animChangeCount_ > animChangeTime_ / 3) {
		// ���̉摜�̃��b�V���ɐ؂�ւ�
		++displayObj_.x;
		// �\�����Ԃ�0�Ƀ��Z�b�g����
		animChangeCount_ = 0;



		// �ȉ��̏����̎��ɏ�Ԃ��A�N�e�B�u��Ԃɂ���
		// �E�U���A�j���[�V�������Đ����I������Ƃ�
		// �E�U�����q�b�g�����Ƃ�
		if ((displayObj_.x >= textureCutNum_.x && !isLoop_)) {

			// ��Ԃ𖳌��ɂ���
			isActive_ = false;

		}



	}
	else {
		animChangeCount_ += delta_time;
	}




}

// �`��p�̊֐�
void AttackBase::draw(const std::shared_ptr<dxe::Camera>& camera) {

	// �A�N�e�B�u�łȂ��Ƃ��������Ȃ�
	if (!isActive_) {
		return;
	}

	SpriteObjectBase::draw(camera);


}


// �U�����Փ˂����ۂɎ��s����֐�
// ******************************************************
// �p����̃N���X�ł̓I�[�o�[���C�h����֐���K���쐬���邱�ƁI
// ******************************************************
void AttackBase::OnHit() {

	// �T�E���h���ݒ肳��Ă��鎞�T�E���h���Đ�
	if (hitSoundHdl_) {
		PlaySoundMem(hitSoundHdl_, DX_PLAYTYPE_BACK);
	}

	// �q�b�g���̃G�t�F�N�g���o���������쐬����
	// �G�t�F�N�g�̃N���X���쐬������ǉ�����

}
