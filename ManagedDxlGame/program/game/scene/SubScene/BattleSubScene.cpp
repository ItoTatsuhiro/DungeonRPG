#include "BattleSubScene.h"
#include "../../base/ObjectBlockBase.h"
#include "../../map/objectBlock/Floor.h"
#include "../../map/objectBlock/Wall.h"
#include "../../character/other/BattleCharacterBase.h"
#include "../../character/Battle/BattlePlayer.h"
#include "../../character/Battle/BattleEnemy.h"
#include "../../character/Battle/Enemy/Enemy_Escape.h"
#include "../../manager/SubSceneManager.h"
#include "../../ui/UiHP.h"


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
	player_ = std::shared_ptr<BattlePlayer>(new BattlePlayer(startPosPlayer_, gridSize_, "travellerAnim.png"));
	// �v���C���[�̌�����ݒ�(�E����)
	player_->setFrontDir(Enum::Dir4::RIGHT);
	// �`�悷�郊�X�g�ɒǉ�
	displayCharaList_.emplace_back(player_);


	// �G�L�����N�^�[�̐���
	enemy_ = BattleEnemyEscape::Create(startPosEnemy_, gridSize_, "slimeIdle.png");
	// �G�L�����N�^�[�̌�����ݒ�(������)
	enemy_->setFrontDir(Enum::Dir4::LEFT);
	// �`�悷�郊�X�g�ɒǉ�
	displayCharaList_.emplace_back(enemy_);


	CreateBattleUI();


	// �J�����̍��W��ݒ�
	TPCamera_->pos_ = { basePos_.x + (battleStageArray_[0].size() / 2) * gridSize_, gridSize_ * 2, gridSize_ * (-15) };



	CreateStage();

}

// �f�X�g���N�^
BattleSubScene::~BattleSubScene() {

}


// �X�V�p�֐�
void BattleSubScene::update(float delta_time) {

	// �V�[�P���X�̍X�V
	seq_.update(delta_time);


	// �J�����̍X�V
	TPCamera_->update();
	
}


// �`��p�֐�
void BattleSubScene::draw() {

	// ���̕`��
	// DrawGridGround(TPCamera_, 50, 20);

	DrawStringEx(600, 600, -1, "enemylife = %f", enemy_->status_->getHp());


	// �`�悷��L�����N�^�[���\�[�g
	SortCharacter(TPCamera_);

	// �I�u�W�F�N�g�����Ԃɕ`��
	auto it = battleStageObjList_.begin();
	while (it != battleStageObjList_.end()) {

		(*it)->draw(TPCamera_);

		++it;
	}


	// �L�����N�^�[�����Ԃɕ`��
	auto itC = displayCharaList_.begin();
	while (itC != displayCharaList_.end()) {

		(*itC)->draw(TPCamera_);

		++itC;
	}

	// UI�̕`��
	DisplayBattleUI();


	// �摜�̕`��
	auto itGpc = gpcList_.begin();
	while (itGpc != gpcList_.end()) {

		// �摜��`��
		DrawRotaGraph((*itGpc)->getPos_().x, (*itGpc)->getPos_().y, (*itGpc)->getSizeMag(), 0, (*itGpc)->getHdl(), true);

		++itGpc;
	}

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
				floorObj = std::shared_ptr<Floor>(new Floor(gridSize_, tnl::Vector3(basePos_.x + x * gridSize_, basePos_.y + gridSize_ / 2, basePos_.z - y * gridSize_)));

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


	cameraTargetPos_ = { battleStageObjArray_[battleStageArray_.size() / 2][battleStageArray_[0].size() / 2]->getPos_() };

	TPCamera_->target_ = cameraTargetPos_;

	// �`�悷��I�u�W�F�N�g���\�[�g
	SortObject(TPCamera_);

}

// �`�悷��I�u�W�F�N�g���\�[�g����֐�
void BattleSubScene::SortObject(std::shared_ptr<dxe::Camera> camera) {

	// �X�e�[�W�ɔz�u���Ă���u���b�N�����J��������̋������Ń\�[�g
	battleStageObjList_.sort([&](const std::shared_ptr<ObjectBlockBase>& left, const std::shared_ptr<ObjectBlockBase>& right) {
		float l1 = (camera->pos_ - left->getPos_()).length();
		float l2 = (camera->pos_ - right->getPos_()).length();
		return (l1 > l2);
	});

}

// �`�悷��I�u�W�F�N�g���\�[�g����֐�
void BattleSubScene::SortCharacter(std::shared_ptr<dxe::Camera> camera) {

	// �L�����N�^�[���J��������̋����Ń\�[�g
	displayCharaList_.sort([&](const std::shared_ptr<BattleCharacterBase>& left, const std::shared_ptr<BattleCharacterBase>& right) {
		float l1 = (camera->pos_ - left->getPos()).length();
		float l2 = (camera->pos_ - right->getPos()).length();
		return (l1 > l2);
		});

}


// ���W�̕␳���s���֐�
// �X�e�[�W�͈̔͊O�ɂ͂ݏo���ꍇ�A�O�̍��W�����Ƃɕ␳���s��
void BattleSubScene::PosCorrection() {

	// �v���C���[�����݂���Ƃ��̂ݏ���
	if (player_) {

		// �v���C���[��x���X�e�[�W�T�C�Y�ɕ␳
		if (player_->getPos().x < stageSizeMin_.x) {
			player_->setPos(tnl::Vector3{ stageSizeMin_.x, player_->getPos().y, player_->getPos().z });
		}
		else if (player_->getPos().x > stageSizeMax_.x) {
			player_->setPos(tnl::Vector3{ stageSizeMax_.x, player_->getPos().y, player_->getPos().z });
		}

		// �v���C���[��y���X�e�[�W�T�C�Y�����ɂȂ�Ȃ��悤�␳
		if (player_->getPos().y < stageSizeMin_.y) {
			player_->setPos(tnl::Vector3{ player_->getPos().x, stageSizeMin_.y, player_->getPos().z });
		}

		// �v���C���[��z���X�e�[�W�T�C�Y�ɕ␳
		if (player_->getPos().z > stageSizeMin_.z) {
			player_->setPos(tnl::Vector3{ player_->getPos().x, player_->getPos().y, stageSizeMin_.z });
		}
		else if (player_->getPos().z < stageSizeMax_.z) {
			player_->setPos(tnl::Vector3{ player_->getPos().x, player_->getPos().y, stageSizeMax_.z });
		}
	}

	// �G�����݂���Ƃ��̂ݏ���
	if (enemy_) {

		// �G��x���X�e�[�W�T�C�Y�ɕ␳
		if (enemy_->getPos().x < stageSizeMin_.x) {
			enemy_->setPos(tnl::Vector3{ stageSizeMin_.x, enemy_->getPos().y, enemy_->getPos().z });
		}
		else if (enemy_->getPos().x > stageSizeMax_.x) {
			enemy_->setPos(tnl::Vector3{ stageSizeMax_.x, enemy_->getPos().y, enemy_->getPos().z });
		}

		// �G��y���X�e�[�W�T�C�Y�����ɂȂ�Ȃ��悤�␳
		if (enemy_->getPos().y < stageSizeMin_.y) {
			enemy_->setPos(tnl::Vector3{ enemy_->getPos().x, stageSizeMax_.y, enemy_->getPos().z });
		}

		// �G��z���X�e�[�W�T�C�Y�ɕ␳
		if (enemy_->getPos().z > stageSizeMin_.z) {
			enemy_->setPos(tnl::Vector3{ enemy_->getPos().x, enemy_->getPos().y, stageSizeMin_.z });
		}
		else if (enemy_->getPos().z < stageSizeMax_.z) {
			enemy_->setPos(tnl::Vector3{ enemy_->getPos().x, enemy_->getPos().y, stageSizeMax_.z });
		}
	}
}


// �U�����肪�������Ă��邩�ǂ����m�F����֐�
void BattleSubScene::CheckHitAttack() {

	tnl::Vector3 aaa = player_->getPos();
	tnl::Vector3 bbb = player_->getHitBox()->get_mesh_()->pos_;



	//-----------------------------------------------------------------
	// �v���C���[�̍U���̓����蔻��̏���

	auto& playerAttack = player_->getActiveAttackList();

	auto it_p = playerAttack.begin();

	while (it_p != player_->getActiveAttackList().end()) {

		if (tnl::IsIntersectAABB((*it_p)->getPos(), { (*it_p)->getMeshSize(), (*it_p)->getMeshSize(), (*it_p)->getMeshSize() },
									enemy_->getPos(), { enemy_->getMeshSize(), enemy_->getMeshSize(), enemy_->getMeshSize() })) {

			// �_���[�W��^����֐�
			enemy_->TakeDamage( (*it_p)->getDamage() );

		}

		++it_p;
	}

	//-----------------------------------------------------------------
	// �G�̍U���̓����蔻��̏���

	auto& enemyAttack = enemy_->getActiveAttackList();

	auto it_e = enemyAttack.begin();

	while (it_e != enemy_->getActiveAttackList().end()) {

		if (tnl::IsIntersectAABB((*it_e)->getPos(), { (*it_e)->getMeshSize(), (*it_e)->getMeshSize(), (*it_e)->getMeshSize() },
			player_->getPos(), { player_->getMeshSize(), player_->getMeshSize(), player_->getMeshSize() })) {

			// �_���[�W��^����֐�
			player_->TakeDamage((*it_e)->getDamage());

		}

		++it_e;
	}



}

// �o�g���V�[�����I�����Ă��邩�ǂ������m�F����֐�
void BattleSubScene::CheckBattleEnd() {

	float playerHp = player_->status_->getHp();
	float enemyHp = enemy_->status_->getHp();


	// �o�g�����I�����Ă��Ȃ��Ƃ���������return����
	if (playerHp > 0 && enemyHp > 0) {

		return;

	}


	isBattling_ = false;

	// �G��HP��0�ȉ�����player���������Ă��鎞
	if (enemyHp <= 0 && playerHp > 0) {

		// �N���A���̕\��
		std::shared_ptr<ito::Graphic> clearText = 
			std::shared_ptr<ito::Graphic>(new ito::Graphic(ito::ResourceManager::GetInstance()->loadGraph("CRUSH!.png"), 2.0f));
		// ���W��ݒ�
		clearText->setPos_(mainGpcPos_);

		// �\������摜���X�g�ɓ����
		gpcList_.emplace_back(clearText);

	}

	// �v���C���[��HP��0�ȉ����G���������Ă���Ƃ�
	if (playerHp <= 0 && enemyHp > 0) {

		// �s�k���̕\��
		std::shared_ptr<ito::Graphic> clearText =
			std::shared_ptr<ito::Graphic>(new ito::Graphic(ito::ResourceManager::GetInstance()->loadGraph("CRUSHED....png"), 2.0f));
		// ���W��ݒ�
		clearText->setPos_(mainGpcPos_);

		// �\������摜���X�g�ɓ����
		gpcList_.emplace_back(clearText);

	}


	seq_.change(&BattleSubScene::seqBattleEnd);


}



// UI�֌W�𐶐�����֐�
void BattleSubScene::CreateBattleUI() {


	playerHpUi_ = std::shared_ptr< UiHP >(new UiHP(player_, "LIFE.png", "blockLong_Blue-Green.png", "ball_Blue-Green.png", playerHpPos_));

	enemyHpUi_ = std::shared_ptr< UiHP >(new UiHP(enemy_, "LIFE_red.png", "blockLong_Red-Blue.png", "ball_Red-Blue.png", enemyHpPos_));

}

// �o�g����UI��\�����邽�߂̊֐�
// draw�֐����ŌĂяo��
void BattleSubScene::DisplayBattleUI() {

	// �v���C���[��HP��UI��\��
	playerHpUi_->draw();

	enemyHpUi_ -> draw();



	

}


bool BattleSubScene::seqBattle(const float delta_time) {


	// �L�����N�^�[�̍X�V
	if (player_) {
		player_->update(delta_time);
	}
	if (enemy_) {
		enemy_->update(delta_time);
	}

	// �ʒu�̕␳
	PosCorrection();

	// �U���̓����蔻��̊m�F
	CheckHitAttack();

	// �I�����Ă��邩�ǂ����̊m�F
	CheckBattleEnd();


	return true;
}



// �o�g���V�[�����I��������V�[�P���X
bool BattleSubScene::seqBattleEnd(const float delta_time) {

	// �V�[����؂�ւ���܂ł̎��Ԃ��J�E���g
	sceneChangeCount_ += delta_time;

	// �V�[����؂�ւ��鎞�Ԃ��o�߂����Ƃ�
	if (sceneChangeCount_ >= sceneChangeTime_) {

		SubSceneManager::GetInstance()->ChangeSubScene(SubSceneManager::ScenePlaySubScene::DUNGEON);

	}

	return true;
}