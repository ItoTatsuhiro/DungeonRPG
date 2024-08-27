#include "AttackLongRange.h"



// �R���X�g���N�^
// �����F
// targetPos...�ڕW�n�_�̍��W
// moveValue...�ړ������
// startPos...�J�n�n�_�̍��W
// size...�傫��
// fileName...�t�@�C����
// front...���ʂ̕���
// charaType...�U���̃L�����N�^�[�����iplayer or enemy�j
// damage...�_���[�W
AttackLongRange::AttackLongRange(const tnl::Vector3& targetPos, float moveValue, const tnl::Vector3& startPos, float size, std::string fileName, Enum::eDir4 front, eCharaType charaType, float damage )
	: AttackBase(startPos, size, fileName, front, charaType, damage), moveValue_(moveValue)
{

	SetNewTargetPos(targetPos);


	// �X�e�[�W�Ƃ̐ڐG���m�F����悤�ɂ���
	checkHitStage_ = true;
	

}



// �f�X�g���N�^
AttackLongRange::~AttackLongRange() {

}



// �X�V�p�̊֐�
void AttackLongRange::update(const float delta_time) {

	// �ړ��̏���

	beforePos_ = transform_.getPos_();

	transform_.setPos_(beforePos_ + moveDir_ * delta_time);


	// AttackBase�N���X�̍X�V
	AttackBase::update(delta_time);

}



// �`��p�̊֐�
void AttackLongRange::draw(const std::shared_ptr<dxe::Camera>& camera) {


	AttackBase::draw(camera);


}



// �V�����ڕW�n�_���Z�b�g����֐�
// �ǔ�����e�����쐬����ۂɎg�p
// targetPos_�̃Z�b�g�݂̂łȂ��AmoveDir_���ēx�v�Z���s��
void AttackLongRange::SetNewTargetPos(const tnl::Vector3& newTargetPos) {

	//�ڕW�n�_�̃Z�b�g
	targetPos_ = newTargetPos;

	// �ړ��̃x�N�g�����v�Z
	moveDir_ = tnl::Vector3::Normalize(targetPos_ - transform_.getPos_());


}

