#include "BattleSubScene.h"
#include "../../base/ObjectBlockBase.h"
#include "../../map/objectBlock/Floor.h"
#include "../../map/objectBlock/Wall.h"
#include "../../character/other/BattleCharacterBase.h"
#include "../../character/Battle/BattlePlayer.h"
#include "../../character/Battle/BattleEnemy.h"
#include "../../character/Battle/Enemy/EnemyEscape.h"
#include "../../manager/SubSceneManager.h"
#include "../../ui/UiHP.h"


#include "../../other/TransformCamera.h"
#include "../../manager/InputManager.h"



// �R���X�g���N�^
BattleSubScene::BattleSubScene() {

	// ���X�g����
	battleCharaList_ = std::make_shared<std::list<std::shared_ptr<BattleCharacterBase>>>();

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
	player_->setFrontDir(Enum::eDir4::RIGHT);
	// �`�悷�郊�X�g�ɒǉ�
	battleCharaList_->emplace_back(player_);


	// �G�L�����N�^�[�̐���
	enemy_ = BattleEnemyEscape::Create(startPosEnemy_, gridSize_, "slimeAnim.png", battleCharaList_);
	// �G�L�����N�^�[�̌�����ݒ�(������)
	enemy_->setFrontDir(Enum::eDir4::LEFT);
	// �`�悷�郊�X�g�ɒǉ�
	battleCharaList_->emplace_back(enemy_);


	CreateBattleUI();


	// �J�����̍��W��ݒ�
	TPCamera_->pos_ = { basePos_.x + (battleStageArray_[0].size() / 2) * gridSize_, gridSize_ * 2, gridSize_ * (-15) };



	CreateStage();

	// ��������摜�ǂݍ���
	battleControlExpGpc_ = ito::ResourceManager::GetInstance()->loadGraph("battleExp.png");

	// BGM�ǂݍ���
	battleBgmHdl_ = ito::ResourceManager::GetInstance()->loadSoundMem("hiphop2.mp3");

	// ���ʒ���
	ChangeVolumeSoundMem(50, battleBgmHdl_);

}

// �f�X�g���N�^
BattleSubScene::~BattleSubScene() {

}


// �X�V�p�֐�
void BattleSubScene::update(float delta_time) {

	// BGM�Đ�
	if (!isPlayingBGM_) {
		PlaySoundMem(battleBgmHdl_, DX_PLAYTYPE_LOOP);

		isPlayingBGM_ = true;
	}


	// �V�[�P���X�̍X�V
	seq_.update(delta_time);


	// �J�����̍X�V
	TPCamera_->update();
	
}


// �`��p�֐�
void BattleSubScene::draw() {



	// �`�悷��L�����N�^�[���\�[�g
	SortCharacter(TPCamera_);

	// �I�u�W�F�N�g�����Ԃɕ`��
	auto it = battleStageObjList_.begin();
	while (it != battleStageObjList_.end()) {

		(*it)->draw(TPCamera_);

		++it;
	}


	// �L�����N�^�[�����Ԃɕ`��
	auto itC = battleCharaList_->begin();
	while (itC != battleCharaList_->end()) {

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

	// ��������摜�̕`��
	DrawRotaGraph(battleControlExpPos_.x, battleControlExpPos_.y, battleControlExpSize_, 0, battleControlExpGpc_, true);

}



// �T�u�V�[���؂�ւ��̍ۂɎ��s����֐�
void BattleSubScene::ChangeSubScene() {

	// BGM��~
	StopSoundMem(battleBgmHdl_);

	isPlayingBGM_ = false;
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
	battleCharaList_->sort([&](const std::shared_ptr<BattleCharacterBase>& left, const std::shared_ptr<BattleCharacterBase>& right) {
		float l1 = (camera->pos_ - left->getPos()).length();
		float l2 = (camera->pos_ - right->getPos()).length();
		return (l1 > l2);
		});

}


// ���W�̕␳���s���֐�
// �X�e�[�W�͈̔͊O�ɂ͂ݏo���ꍇ�A�O�̍��W�����Ƃɕ␳���s��
void BattleSubScene::PosCorrection() {


	auto it = battleCharaList_->begin();

	while (it != battleCharaList_->end()) {

		// �L�����N�^�[��x���X�e�[�W�T�C�Y�ɕ␳
		if ((*it)->getPos().x < stageSizeMin_.x) {
			(*it)->setPos(tnl::Vector3{ stageSizeMin_.x, (*it)->getPos().y, (*it)->getPos().z });
		}
		else if ((*it)->getPos().x > stageSizeMax_.x) {
			(*it)->setPos(tnl::Vector3{ stageSizeMax_.x, (*it)->getPos().y, (*it)->getPos().z });
		}

		// �L�����N�^�[��y���X�e�[�W�T�C�Y�����ɂȂ�Ȃ��悤�␳
		if ((*it)->getPos().y < stageSizeMin_.y) {
			(*it)->setPos(tnl::Vector3{ (*it)->getPos().x, stageSizeMin_.y, (*it)->getPos().z });
		}

		// �L�����N�^�[��z���X�e�[�W�T�C�Y�ɕ␳
		if ((*it)->getPos().z > stageSizeMin_.z) {
			(*it)->setPos(tnl::Vector3{ (*it)->getPos().x, (*it)->getPos().y, stageSizeMin_.z });
		}
		else if ((*it)->getPos().z < stageSizeMax_.z) {
			(*it)->setPos(tnl::Vector3{ (*it)->getPos().x, (*it)->getPos().y, stageSizeMax_.z });
		}

		++it;

	}


}


// �U�����肪�������Ă��邩�ǂ����m�F����֐�
void BattleSubScene::CheckHitAttack() {


	//-----------------------------------------------------------------
	// �v���C���[�̍U���̓����蔻��̏���

	auto& playerAttack = player_->getAttackList();

	auto it_p = playerAttack.begin();



	while (it_p != player_->getAttackList().end()) {

		// �U�����L���łȂ��Ƃ��͏������Ȃ�
		if (!(*it_p)->getIsActive()) {
			++it_p;
			continue;
		}


		tnl::Vector3 atkPos = (*it_p)->getPos();

		// �L�����N�^�[�Ƃ̓����蔻����m�F
		if (tnl::IsIntersectAABB( atkPos, { (*it_p)->getMeshSize(), (*it_p)->getMeshSize(), (*it_p)->getMeshSize() },
									enemy_->getPos(), { enemy_->getMeshSize(), enemy_->getMeshSize(), enemy_->getMeshSize() })) {

			// �_���[�W��^����֐�
			enemy_->TakeDamage( (*it_p)->getDamage() );

		}

		// *********************************************************************************************************
		// �X�e�[�W�Ƃ̓����蔻����m�F
		// �쐬���I�I�I�I�I
		if (atkPos.x < stageSizeMin_.x || atkPos.y < stageSizeMin_.y || atkPos.x > stageSizeMax_.x || atkPos.y > stageSizeMax_.y) {

			//// �X�e�[�W�͈̔͊O�̎��A�N�e�B�u��Ԃ�false�ɂ���
			//(*it_p)->setIsActive(false);

			// �X�e�[�W�͈͊O�ɏo���Ƃ�������������ɂ���
			(*it_p)->setIsHit(true);

		}



		++it_p;
	}

	//-----------------------------------------------------------------
	// �G�̍U���̓����蔻��̏���

	auto& enemyAttack = enemy_->getAttackList();

	auto it_e = enemyAttack.begin();

	while (it_e != enemy_->getAttackList().end()) {

		// �U�����L���łȂ��Ƃ��͏������Ȃ�
		if (!(*it_e)->getIsActive()) {
			++it_e;
			continue;
		}

		// �L�����N�^�[�Ƃ̓����蔻��
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

	//// �J�����̍X�V
	//TPCamera_->update();

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