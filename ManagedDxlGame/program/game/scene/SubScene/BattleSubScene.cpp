#include "BattleSubScene.h"
#include "../../base/ObjectBlockBase.h"
#include "../../map/objectBlock/Floor.h"
#include "../../map/objectBlock/Wall.h"
#include "../../character/Battle/BattlePlayer.h"

#include "../../other/TransformCamera.h"
#include "../../manager/InputManager.h"



// �R���X�g���N�^
BattleSubScene::BattleSubScene() {

	// �o�g���V�[���̃}�b�v�z��̓ǂݍ���
	battleStageArray_ = tnl::LoadCsv<int>("csv/BattleMap.csv");
	// �\������J�����̕ϐ���������
	TPCamera_ = std::make_shared< TransformCamera >(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// �L�����N�^�[�̊J�n�ʒu�̏�����
	startPosPlayer_ = { static_cast<float>(battleStageArray_[0].size()) / 3 * gridSize_, 0, static_cast<float>(battleStageArray_[0].size()) / 2 * -gridSize_ };
	startPosEnemy_ = { static_cast<float>(battleStageArray_[0].size()) * 2 / 3 * gridSize_, 0, static_cast<float>(battleStageArray_[0].size()) / 2 * -gridSize_ };

	// �v���C���[�𐶐�
	player_ = std::shared_ptr<BattlePlayer>(new BattlePlayer(startPosPlayer_));


	// �J�����̍��W��ݒ�
	TPCamera_->pos_ = { basePos_.x + (battleStageArray_[0].size() / 2) * gridSize_, gridSize_ * 2, gridSize_ * (-15) };



	CreateStage();

}

// �f�X�g���N�^
BattleSubScene::~BattleSubScene() {

}


// �X�V�p�֐�
void BattleSubScene::update(float delta_time) {

	player_->update(delta_time);

	posCorrection();

	TPCamera_->update();

	
}


// �`��p�֐�
void BattleSubScene::draw() {

	// ���̕`��
	// DrawGridGround(TPCamera_, 50, 20);

	// �`�悷��I�u�W�F�N�g���\�[�g
	SortObject(TPCamera_);



	// ���Ԃɕ`��
	auto it = battleStageObjList_.begin();
	while (it != battleStageObjList_.end()) {

		(*it)->draw(TPCamera_);

		++it;
	}
	// �v���C���[�̕`��
	player_->draw(TPCamera_);

}

// �ǂݍ���CSV�̔z�񂩂�X�e�[�W�𐶐�����֐�
void BattleSubScene::CreateStage() {

	// ���̃X�e�[�W���쐬����Ă��Ȃ��ꍇ
	// �X�e�[�W�̔z���񂪓ǂݍ���ł��邩�m�F
	if (battleStageArray_.size() == 0) {
		tnl::DebugTrace("�z�񂪓ǂݍ��߂Ă��܂���\n");
		return;
	}


	// �X�e�[�W�̃I�u�W�F�N�g���쐬���邽�߂̌J��Ԃ�����
	for (int y = 0; y < battleStageArray_.size(); ++y) {

		// �������̔z��
		std::vector<std::shared_ptr<ObjectBlockBase>> objArray_;

		for (int x = 0; x < battleStageArray_[0].size(); ++x) {

			std::shared_ptr<ObjectBlockBase> floorObj;

			// �}�b�v�̏��ɂ���Đ�������I�u�W�F�N�g��ύX���鏈��
			// �����v�f��ǉ�����ꍇ��case��ǉ�����
			switch (battleStageArray_[y][x]) {
			case 0:
				// 0�̎��ǂ𐶐�
				floorObj = std::shared_ptr<Floor>(new Floor(gridSize_, tnl::Vector3(basePos_.x + x * gridSize_, basePos_.y, basePos_.z - y * gridSize_)));

				if (floorHeight_ - 0 < FLT_EPSILON) {
					floorHeight_ = floorObj->getPos_().y;
				}

				// �X�e�[�W�̃I�u�W�F�N�g�̔z��ɓ����
				objArray_.emplace_back(floorObj);
				// �`��p�̃��X�g�ɐ��������I�u�W�F�N�g��ǉ�
				battleStageObjList_.emplace_back(floorObj);

				break;

			case 1:
				// 1�̎��ǂ̃I�u�W�F�N�g�𐶐�
				std::shared_ptr<ObjectBlockBase> wallObj = std::shared_ptr<Wall>(new Wall(gridSize_, tnl::Vector3(basePos_.x + x * gridSize_, basePos_.y, basePos_.z - y * gridSize_)));
				// �z��ɓ����p�̔z��ɓ����
				objArray_.emplace_back(wallObj);
				// �`��p�̃��X�g�ɐ��������I�u�W�F�N�g��ǉ�
				battleStageObjList_.emplace_back(wallObj);

				break;

			}

		}
		// �X�e�[�W�̃I�u�W�F�N�g�̔z��ɓ����
		battleStageObjArray_.emplace_back(objArray_);
	}

	stageSizeMin_ = (battleStageObjArray_[0][0]->getPos_() + tnl::Vector3( 1.0f, 0, -1.0f) * gridSize_);
	stageSizeMin_.y = floorHeight_;

	stageSizeMax_ 
		= (battleStageObjArray_[battleStageObjArray_.size() - 1][battleStageObjArray_[battleStageObjArray_.size() - 1].size() - 1]->getPos_() 
			- tnl::Vector3{ 1.0f, 0, -1.0f } * gridSize_);
	stageSizeMax_.y = floorHeight_;

	// �J�����̌�����ݒ�
	tnl::Vector3 targetPos = { battleStageObjArray_[battleStageArray_.size() / 2][battleStageArray_[0].size() / 2]->getPos_() };

	TPCamera_->target_ = targetPos;

}

// �`�悷��I�u�W�F�N�g���\�[�g����֐�
void BattleSubScene::SortObject(std::shared_ptr<dxe::Camera> camera) {

	battleStageObjList_.sort([&](const std::shared_ptr<ObjectBlockBase>& left, const std::shared_ptr<ObjectBlockBase>& right) {
		float l1 = (camera->pos_ - left->getPos_()).length();
		float l2 = (camera->pos_ - right->getPos_()).length();
		return (l1 > l2);
	});

}

// ���W�̕␳���s���֐�
// �X�e�[�W�͈̔͊O�ɂ͂ݏo���ꍇ�A�O�̍��W�����Ƃɕ␳���s��
void BattleSubScene::posCorrection() {

	// �v���C���[��x���X�e�[�W�T�C�Y�ɕ␳
	if (player_->getHitBox()->get_mesh_()->pos_.x < stageSizeMin_.x ) {
		player_->getHitBox()->get_mesh_()->pos_.x = stageSizeMin_.x;
	}
	else if (player_->getHitBox()->get_mesh_()->pos_.x > stageSizeMax_.x) {
		player_->getHitBox()->get_mesh_()->pos_.x = stageSizeMax_.x ;
	}

	// �v���C���[��y���X�e�[�W�T�C�Y�����ɂȂ�Ȃ��悤�␳
	if (player_->getHitBox()->get_mesh_()->pos_.y < stageSizeMin_.y) {
		player_->getHitBox()->get_mesh_()->pos_.y = stageSizeMax_.y;
	}

	// �v���C���[��z���X�e�[�W�T�C�Y�ɕ␳
	if (player_->getHitBox()->get_mesh_()->pos_.z > stageSizeMin_.z) {
		player_->getHitBox()->get_mesh_()->pos_.z = stageSizeMin_.z;
	}
	else if (player_->getHitBox()->get_mesh_()->pos_.z < stageSizeMax_.z) {
		player_->getHitBox()->get_mesh_()->pos_.z = stageSizeMax_.z;
	}

}


bool BattleSubScene::seqBattle(const float delta_time) {


	return true;
}