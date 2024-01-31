#include "../../dxlib_ext/dxlib_ext.h"
#include "Enemy.h"

#include "../manager/ObjectManager.h"


// �R���X�g���N�^
// cellSize_(�}�b�v��1�}�X���̑傫��)��gridPos_(���݂��Ă�����W)��������
// �����FcellSize...�X�e�[�W��1�}�X�̑傫��
// startGridPos...�������̏����ʒu
Enemy::Enemy(float gridSize, tnl::Vector2i startGridPos) : CharacterBase(gridSize, startGridPos) {

	enemyObj_ = ObjectManager::GetInstance()->createPlane(tnl::Vector3(gridSize), "enemy");

	enemyObj_->get_mesh_()->rot_ *= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, 1), tnl::ToDegree(90));

	

}

// �f�X�g���N�^
Enemy::~Enemy() {

}

// �X�V�p�̊֐�
void Enemy::update(float delta_time) {

	//seq_.update(delta_time);

}

// �`��p�̊֐�
void Enemy::draw( std::shared_ptr<dxe::Camera> camera ) {

	enemyObj_->get_mesh_()->render(camera);

}


//bool Enemy::seqIdle(const float delta_time) {
//
//
//
//}








