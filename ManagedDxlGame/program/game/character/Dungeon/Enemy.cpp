#include "../../../dxlib_ext/dxlib_ext.h"
#include "Enemy.h"

#include "../../map/Stage.h"
#include "../../manager/ObjectManager.h"
#include "Player.h"
#include "../../manager/TurnManager.h"

// �R���X�g���N�^
// cellSize_(�}�b�v��1�}�X���̑傫��)��gridPos_(���݂��Ă�����W)��������
// �����FgridSize...�X�e�[�W��1�}�X�̑傫��
// startGridPos...�������̏����ʒu
Enemy::Enemy(float gridSize, tnl::Vector2i startGridPos, std::shared_ptr<Player> player, std::shared_ptr<TurnManager> turnManager)
	: player_(player), CharacterBaseDungeon(gridSize, startGridPos), turnManager_(turnManager) {

	// �����������_���Ɍ���
	frontDir_ = static_cast<Enum::Dir4>(rand() % static_cast<int>(Enum::Dir4::DIRMAX));

	// �X�e�[�W�N���X�̃C���X�^���X���擾
	stage_ = Stage::GetInstance();

	// �e�N�X�`���̓ǂݍ���
	enemyTexture_ = ito::ResourceManager::GetInstance()->loadTexture("wispAnimDir4.png");

	// �e�N�X�`���̕��������擾
	textureCutNum_ = ito::ResourceManager::GetInstance()->getTextureCutNum("wispAnimDir4.png");

	// Transform�̏�������
	nowTransform_.setPos_( stage_->getGridObjPos(startGridPos) + tnl::Vector3(0, 1, 0) * gridSize );

	// �e�N�X�`���̈���̑傫�����v�Z
	float sizeU = 1.0 / textureCutNum_.x;
	float sizeV = 1.0 / textureCutNum_.y;

	// �f�o�b�O�p�\��
	tnl::DebugTrace("sizeU = %f, sizeV = %f\n", sizeU, sizeV);

	// �e�N�X�`����\��t����p�̃��b�V���𐶐�
	for (int v = 0; v < textureCutNum_.y; ++v) {

		std::vector<std::shared_ptr<ito::Object3D>> objArray;

		for (int u = 0; u < textureCutNum_.x; ++u) {

			std::string objName = "enemy" + std::to_string(u) + std::to_string(v);

			std::shared_ptr<ito::Object3D> enemyObj
				= ObjectManager::GetInstance()->createPlane(tnl::Vector3(gridSize * 1.5 ), objName, { u * sizeU, v * sizeV, 0 }, { (u + 1) * sizeU, (v + 1) * sizeV, 0 });

			// �f�o�b�O�p�\��
			//tnl::DebugTrace(" (%d, %d) = �O(%f, %f), ��(%f, %f)\n", u, v, u * sizeU, v * sizeV, (u + 1) * sizeU, (v + 1) * sizeV);

			// ��������]
			enemyObj->get_mesh_()->rot_ *= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, 1), tnl::ToRadian(90));
			enemyObj->get_mesh_()->rot_ *= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 1, 0), tnl::ToRadian(90));

			// �\���ݒ��ύX
			enemyObj->get_mesh_()->setBlendMode(DX_BLENDMODE_ALPHA);
			enemyObj->get_mesh_()->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			enemyObj->get_mesh_()->setCullingMode(DX_CULLING_RIGHT);

			// �e�N�X�`���̓\��t��
			enemyObj->get_mesh_()->setTexture(enemyTexture_);

			objArray.emplace_back(enemyObj);
		}
		enemyObjArray_.emplace_back(objArray);
	}

	// �f�o�b�O�p
	size = { sizeU, sizeV, 0 };

	// nowTransform_.setPos_({ 0, 50, 150 });
}

// �f�X�g���N�^
Enemy::~Enemy() {

}

// �X�V�p�̊֐�
void Enemy::update(float delta_time) {

	// �摜���A�j���[�V���������邽�߂̏���
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

	

	// �V�[�P���X�̃A�b�v�f�[�g����
	seq_.update(delta_time);

	// �\�����̃I�u�W�F�N�g��Transform�������݂̏�Ԃɍ��킹��
	enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->pos_ = nowTransform_.getPos_();
	enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->rot_ = ( player_->getTransform().getRot3D_() );

	// LookAt�֐�
	// ����g�p�ł��Ă��Ȃ�
	// 
	//enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->rot_
	//	*= tnl::Quaternion::LookAt(nowTransform_.getPos_(), player_->getTransform().getPos_(), {0, 1, 0});

}

// �`��p�̊֐�
void Enemy::draw( std::shared_ptr<dxe::Camera> camera ) {

	//// �f�o�b�O�p�\��
	//DrawStringEx(500, 100, -1, "�\���� = %d, %d", displayObj_.x, displayObj_.y);
	//DrawStringEx(500, 200, -1, "�\�����W = %f, %f", enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->pos_.x, enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->pos_.z);
	//DrawStringEx(500, 250, -1, "nowTransform = %f, %f", nowTransform_.getPos_().x, nowTransform_.getPos_().z);
	//DrawStringEx(500, 300, -1, "name = %s", enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->getName().c_str());
	//DrawStringEx(650, 100, -1, "���ʁF�G = %d, �v���C���[ = %d", frontDir_, player_->getFrontDir());
	//DrawStringEx(500, 350, -1, "frontDir_ - (player_->getFrontDir() = %d", frontDir_ - (player_->getFrontDir()));

	enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->render(camera);

}


// ���g���폜����֐�
void Enemy::Destroy() {


	delete this;
}


// Idle��Ԃ���V�[�P���X��؂�ւ��邽�߂̊֐�
// TurnManager����Ăяo���Ďg�p����
void Enemy::ChangeSeqFromIdle() {

	// Idle�ȊO�̏�Ԃ̂Ƃ��������Ȃ�
	if (nowSeq_ != EnemySeq::IDLE) { 
		tnl::DebugTrace("Idle��Ԃł͖����������ߏ����ł��܂���ł���\n");
		return;
	}

	// �V�[�P���X��؂�ւ���
	seq_.change(&Enemy::seqActionDecide);

}


// Wait��Ԃ��玟�̏����ɐ؂�ւ��鏈��
// TurnManager����Ăяo���Ďg�p����
void Enemy::ChangeSeqFromWait() {

	// Wait�ȊO�̏�Ԃ̂Ƃ��������Ȃ�
	if (nowSeq_ != EnemySeq::WAIT) {
		tnl::DebugTrace("Wait��Ԃł͖����������ߏ����ł��܂���ł���\n");
		return;
	}

	// �V�[�P���X��؂�ւ���
	// decadedSeq_�ɉ����Đ؂�ւ���V�[�P���X��ύX����
	if (decadedSeq_ == EnemySeq::WAIT) {
		tnl::DebugTrace("���̏��������肳��Ă��Ȃ��������ߏ����ł��܂���ł���\n");
	}
	else if (decadedSeq_ == EnemySeq::MOVING) {
		seq_.change(&Enemy::seqMoving);
	}
	else if (decadedSeq_ == EnemySeq::ROTATING) {
		seq_.change(&Enemy::seqRotating);
	}
	
	return;

}


// �ҋ@���̃V�[�P���X
// ChangeSeqFromIdle�֐����Ăяo�����ƂŎ��̃V�[�P���X�ɑJ��
bool Enemy::seqIdle(const float delta_time) {

	if (actDebugMove) { actDebugMove = false; }

	if (tnl::Input::IsKeyDown(eKeys::KB_LCONTROL) && tnl::Input::IsKeyDown(eKeys::KB_E)) {
		actDebugMove = true;
		tnl::DebugTrace("�f�o�b�O�s�����s");

		ChangeSeqFromIdle();
	}

	return true;

}


// �s�����e�����肷��V�[�P���X
bool Enemy::seqActionDecide(const float delta_time) {

	// ���̐i�s����
	tnl::Vector2i nextGrid = gridPos_;

	// �}�X���v�Z
	nextGrid = calcMoveGrid(frontDir_);

	// �i�s�����̃}�X���ړ��ł��Ȃ��Ƃ�
	if (!(stage_->CheckGridCanMove(nextGrid))) {


		// �����̍��̃}�X���ړ��\���m�F
		tnl::Vector2i leftGrid = { 0, 0 };
		if (frontDir_ + Enum::Dir4::LEFT == Enum::Dir4::UP) { leftGrid = gridPos_ + tnl::Vector2i::up; }
		else if (frontDir_ + Enum::Dir4::LEFT == Enum::Dir4::LEFT) { leftGrid = gridPos_ + tnl::Vector2i::left; }
		else if (frontDir_ + Enum::Dir4::LEFT == Enum::Dir4::DOWN) { leftGrid = gridPos_ + tnl::Vector2i::down; }
		else if (frontDir_ + Enum::Dir4::LEFT == Enum::Dir4::RIGHT) { leftGrid = gridPos_ + tnl::Vector2i::right; }

		bool canMoveL = stage_->CheckGridCanMove(leftGrid);


		// �����̉E�̃}�X���ړ��\���m�F
		tnl::Vector2i rightGrid = { 0, 0 };
		if (frontDir_ + Enum::Dir4::RIGHT == Enum::Dir4::UP) { rightGrid = gridPos_ + tnl::Vector2i::up; }
		else if (frontDir_ + Enum::Dir4::RIGHT == Enum::Dir4::LEFT) { rightGrid = gridPos_ + tnl::Vector2i::left; }
		else if (frontDir_ + Enum::Dir4::RIGHT == Enum::Dir4::DOWN) { rightGrid = gridPos_ + tnl::Vector2i::down; }
		else if (frontDir_ + Enum::Dir4::RIGHT == Enum::Dir4::RIGHT) { rightGrid = gridPos_ + tnl::Vector2i::right; }

		bool canMoveR = stage_->CheckGridCanMove(rightGrid);


		// ���E�ǂ���ɂ��ړ��ł���Ƃ�
		if (canMoveL && canMoveR) {
			// ���Ɍ������������E���烉���_���Ɍ��肷��
			nextDir_ = frontDir_ + ((rand() % 2 == 0) ? Enum::Dir4::LEFT : Enum::Dir4::RIGHT);
		}
		// ���ɂ݈̂ړ��ł���Ƃ�
		else if (canMoveL && !canMoveR) {
			// ���Ɍ������������݂̌����̍������ɂ���
			nextDir_ = frontDir_ + Enum::Dir4::LEFT;
		}
		// �E�ɂ݈̂ړ��ł���Ƃ�
		else if (!canMoveL && canMoveR) {
			// ���Ɍ������������݂̌����̉E�����ɂ���
			nextDir_ = frontDir_ + Enum::Dir4::RIGHT;
		}
		// ���E�ǂ���ɂ��ړ��ł��Ȃ��Ƃ�
		else if (!canMoveL && !canMoveR) {
			// ���Ɍ������������݂̌����̌������ɂ���
			nextDir_ = frontDir_ + Enum::Dir4::DOWN;
		}
		nowSeq_ = EnemySeq::ROT_CHECK;

		// �V�[�P���X����]�̊m�F������V�[�P���X�ɐ؂�ւ���
		seq_.change(&Enemy::seqRotateCheck);


	}
	// ���ʂ��ړ��ł���Ƃ�
	else {
	
		nextGridPos_ = nextGrid;

		nowSeq_ = EnemySeq::MOVE_CHECK;

		// �V�[�P���X���ړ��̊m�F������V�[�P���X�ɐ؂�ւ���
		seq_.change(&Enemy::seqMoveCheck);

	}

	return true;

}


// �ړ�����������V�[�P���X
bool Enemy::seqMoveCheck(const float delta_time) {

	// �ړ��悪�z��O�̏ꍇ�ړ����Ȃ��悤�ɂ��邽�߂̏���
	if (stage_->CheckGridPosInt(nextGridPos_) == -1) {
		tnl::DebugTrace("�z��O�̂��߈ړ��ł��܂���\n");

		nowSeq_ = EnemySeq::IDLE;
		seq_.change(&Enemy::seqIdle);

		return true;
	}

	// �ړ���̃}�X���ړ��ł��Ȃ��Ƃ�
	if (!(stage_->CheckGridPosObj(nextGridPos_)->getCanMove())) {

		// ���̍��W�����݂̍��W�ɖ߂�
		nextGridPos_ = gridPos_;
		// �V�[�P���X��ҋ@���ɖ߂�
		seq_.change(&Enemy::seqIdle);
		nowSeq_ = EnemySeq::IDLE;
		// �������I������
		return true;
	}
	// �ړ��ł���Ƃ�
	else {
		// �ړ���̍��W��ݒ�
		nextTransform_.setPos_({ nextGridPos_.x * gridSize_, gridSize_, -nextGridPos_.y * gridSize_ });

		// �ҋ@���s���V�[�P���X�ɐ؂�ւ�
		seq_.change(&Enemy::seqWait);

		// �V�[�P���X�̐؂�ւ��𐧌�
		finishAction_ = false;

		// ��Ԃ�ҋ@�ɐ؂�ւ�
		nowSeq_ = EnemySeq::WAIT;
		// �ҋ@��̍s����Moving�ɐݒ�
		decadedSeq_ = EnemySeq::MOVING;

		return true;
	}

}


// ��]����������V�[�P���X
bool Enemy::seqRotateCheck(const float delta_time) {

	// ���̌����ɉ����Ď��̕�����ύX����
	// ��������v���X�Ƃ���
	if (nextDir_ - frontDir_ == Enum::Dir4::LEFT) {
		// ��]������ʂ�90�x�ɂ���
		rotValMax_ = -90;
	}
	else if (nextDir_ - frontDir_ == Enum::Dir4::DOWN) {
		// ��]������ʂ�180�x�ɂ���
		rotValMax_ = -180;
	}
	else if (nextDir_ - frontDir_ == Enum::Dir4::RIGHT) {
		// ��]������ʂ�-90�x�ɂ���
		rotValMax_ = 90;
	}



	// ���̊p�x�����݂̊p�x�����]�ʕ���]������
	nextTransform_.setRot3D_(nextTransform_.getRot3D_() * tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(rotValMax_)));

	// �ҋ@���s���V�[�P���X�ɐ؂�ւ�
	seq_.change(&Enemy::seqWait);

	// �V�[�P���X�̐؂�ւ��𐧌�
	finishAction_ = false;

	// ���݂̃V�[�P���X��Wait�ɕύX
	nowSeq_ = EnemySeq::WAIT;
	// �ҋ@��̍s����Rotating�ɐݒ�
	decadedSeq_ = EnemySeq::ROTATING;

	return true;


}



// �s���҂��V�[�P���X
// ChangeSeqFromWait�֐����Ăяo�����ƂŎ��̃V�[�P���X�ɑJ��
bool Enemy::seqWait(const float delta_time) {

	if (actDebugMove) {
		ChangeSeqFromWait();
	}

	return true;

}



// �ړ����s���V�[�P���X
bool Enemy::seqMoving(const float delta_time) {

	Moving(delta_time);

	if (finishAction_) {
		turnManager_->ActionEndEnemy();

		seq_.change(&Enemy::seqIdle);
		nowSeq_ = EnemySeq::IDLE;
	}

	return true;
}

// ��]���s���V�[�P���X
bool Enemy::seqRotating(const float delta_time) {


	// ���݂̃g�����X�t�H�[�������̃g�����X�t�H�[���ɍ��킹��
	nowTransform_.setRot3D_(nextTransform_.getRot3D_());
	// ��]�ʂ̃��Z�b�g
	rotValMax_ = 0;
	// �����̏����ŐV�̏�Ԃɂ���
	frontDir_ += nextDir_;
	// ���̈ʒu�𐳖ʂɂ��Ă���
	nextDir_ = Enum::Dir4::UP;
	// �s���������I����������true��
	finishAction_ = true;

	if (finishAction_) {

		turnManager_->ActionEndEnemy();

		seq_.change(&Enemy::seqIdle);
		nowSeq_ = EnemySeq::IDLE;
	}

	return true;

}








