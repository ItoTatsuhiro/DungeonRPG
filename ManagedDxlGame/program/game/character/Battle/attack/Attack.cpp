#include "Attack.h"
#include "../../../manager/ObjectManager.h"





// �R���X�g���N�^
// �����F���W�A�傫���A�t�@�C�����A���ʂ̕���(LEFT��RIGHT), �U���̃L�����N�^�[����, �_���[�W
// Object3D�̃��b�V���𓖂��蔻��p�̃��b�V���Ƃ��č쐬����
Attack::Attack(const tnl::Vector3& pos, float size, std::string fileName, Enum::eDir4 front, eCharaType charaType, float damage)
	: AttackBase(pos, size, fileName, front, charaType, damage)
{



}

// �f�X�g���N�^
Attack::~Attack() {




}


// �X�V�p�̊֐�
void Attack::update(float delta_time) {

	// ���N���X�̍X�V
	AttackBase::update(delta_time);



}

// �`��p�̊֐�
void Attack::draw(const std::shared_ptr<dxe::Camera>& camera) {

	// ���N���X�̕`��
	AttackBase::draw(camera);



}


