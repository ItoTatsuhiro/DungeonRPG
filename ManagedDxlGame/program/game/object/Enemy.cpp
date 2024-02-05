#include "../../dxlib_ext/dxlib_ext.h"
#include "Enemy.h"

#include "../map/Stage.h"
#include "../manager/ObjectManager.h"
#include "Player.h"

// �R���X�g���N�^
// cellSize_(�}�b�v��1�}�X���̑傫��)��gridPos_(���݂��Ă�����W)��������
// �����FcellSize...�X�e�[�W��1�}�X�̑傫��
// startGridPos...�������̏����ʒu
Enemy::Enemy(float gridSize, tnl::Vector2i startGridPos, std::shared_ptr<Player> player) : player_(player), CharacterBase(gridSize, startGridPos) {

	stage_ = Stage::GetInstance();

	enemyTexture_ = ito::ResourceManager::GetInstance()->loadTexture("wispAnimDir4.png");

	textureCutNum_ = ito::ResourceManager::GetInstance()->getTextureCutNum("wispAnimDir4.png");

	nowTransform_.setPos_( stage_->getGridObjPos(startGridPos) + tnl::Vector3(0, 1, 0) * gridSize );

	// �e�N�X�`���̈���̑傫�����v�Z
	float sizeU = 1.0 / textureCutNum_.x;
	float sizeV = 1.0 / textureCutNum_.y;

	tnl::DebugTrace("sizeU = %f, sizeV = %f\n", sizeU, sizeV);

	for (int v = 0; v < textureCutNum_.y; ++v) {

		std::vector<std::shared_ptr<ito::Object3D>> objArray;

		for (int u = 0; u < textureCutNum_.x; ++u) {

			std::string objName = "enemy" + std::to_string(u) + std::to_string(v);

			std::shared_ptr<ito::Object3D> enemyObj
				= ObjectManager::GetInstance()->createPlane(tnl::Vector3(gridSize * 1.5 ), objName, { u * sizeU, v * sizeV, 0 }, { (u + 1) * sizeU, (v + 1) * sizeV, 0 });


			tnl::DebugTrace(" (%d, %d) = �O(%f, %f), ��(%f, %f)\n", u, v, u * sizeU, v * sizeV, (u + 1) * sizeU, (v + 1) * sizeV);


			enemyObj->get_mesh_()->rot_ *= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, 1), tnl::ToDegree(90));
			enemyObj->get_mesh_()->rot_ *= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 1, 0), tnl::ToDegree(90));


			enemyObj->get_mesh_()->setBlendMode(DX_BLENDMODE_ALPHA);
			enemyObj->get_mesh_()->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			enemyObj->get_mesh_()->setCullingMode(DX_CULLING_RIGHT);

			enemyObj->get_mesh_()->setTexture(enemyTexture_);

			objArray.emplace_back(enemyObj);
		}
		enemyObjArray_.emplace_back(objArray);
	}

	size = { sizeU, sizeV, 0 };

	// nowTransform_.setPos_({ 0, 50, 150 });
}

// �f�X�g���N�^
Enemy::~Enemy() {

}

// �X�V�p�̊֐�
void Enemy::update(float delta_time) {

	animCount_ += delta_time;

	if (animCount_ / animTime_ > textureCutNum_.x) { animCount_ = 0; }

	displayObj_ = { static_cast<int> (animCount_ / animTime_) , displayObj_.y };


	// �v���C���[�̌����Ƃ̍��ɉ����ĕ\��������e�N�X�`����؂�ւ���
	// �w���̉摜��\��
	if (frontDir_ - (player_->getFrontDir()) == Enum::Dir4::UP) { 
		displayObj_.y= 0;
	}
	// �������̉摜��\��
	else if (frontDir_ - (player_->getFrontDir()) == Enum::Dir4::LEFT) { 
		displayObj_.y = 1;
	}
	// ���ʂ̉摜��\��
	else if (frontDir_ - (player_->getFrontDir()) == Enum::Dir4::DOWN) { 
		displayObj_.y = 3;
	}
	// �E�����̉摜��\��
	else if (frontDir_ - (player_->getFrontDir()) == Enum::Dir4::RIGHT) { 
		displayObj_.y = 2;
	}


	//seq_.update(delta_time);

	// �\�����̃I�u�W�F�N�g��Transform�������݂̏�Ԃɍ��킹��
	enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->pos_ = nowTransform_.getPos_();
	enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->rot_ = (player_->getTransform().getRot3D_());

	// LookAt�֐�
	// ����g�p�ł��Ă��Ȃ�
	// 
	//enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->rot_
	//	*= tnl::Quaternion::LookAt(nowTransform_.getPos_(), player_->getTransform().getPos_(), {0, 1, 0});

}

// �`��p�̊֐�
void Enemy::draw( std::shared_ptr<dxe::Camera> camera ) {

	DrawStringEx(500, 100, -1, "�\���� = %d, %d", displayObj_.x, displayObj_.y);
	DrawStringEx(500, 200, -1, "�\�����W = %f, %f", enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->pos_.x, enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->pos_.z);

	DrawStringEx(500, 300, -1, "name = %s", enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->getName().c_str());

	enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->render(camera);

	DrawStringEx(650, 100, -1, "���ʁF�G = %d, �v���C���[ = %d", frontDir_, player_->getFrontDir());


}


//bool Enemy::seqIdle(const float delta_time) {
//
//
//
//}








