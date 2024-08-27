#include "DungeonSubScene.h"
#include "../../map/Stage.h"
#include "../../character/Dungeon/Player.h"
#include "../../character/Dungeon/Enemy.h"
#include "../../manager/TurnManager.h"
#include "../../manager/SubSceneManager.h"
#include "../../other/TransformCamera.h"
#include "../../other/Enum.h"


// �R���X�g���N�^
DungeonSubScene::DungeonSubScene() {

	// �`��p�̃J�����̏�����
	FPCamera_ = std::make_shared< TransformCamera >(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// �X�e�[�W���Ǘ�����N���X�̐���
	stage_ = Stage::GetInstance("test", "csv/mapData.csv", gridSize_);

	// �^�[���}�l�[�W���[����
	turnManager_ = std::shared_ptr<TurnManager>(new TurnManager());

	// �L�����N�^�[����
	CreateCharacter();

	// �����\���p�̃R���p�X�̉摜��ǂݍ���
	directionGpcHdl_ = ito::ResourceManager::GetInstance()->loadGraph("compass.png");
	// ��������摜�̓ǂݍ���
	controlExpGpcHdl_ = ito::ResourceManager::GetInstance()->loadGraph("controlExp.png");

}

// �f�X�g���N�^
DungeonSubScene::~DungeonSubScene() {

	turnManager_.reset();
	player_.reset();

	enemyList_.clear();

}

// �X�V�p�̊֐�
void DungeonSubScene::update(float delta_time){

	// ���̕`��
	// DrawGridGround(FPCamera_, 50, 20);

	// �J�����̍��W���v���C���[�̍��W�ɍ��킹��
	FPCamera_->pos_ = player_->getTransform().getPos_();

	// �J�����̉�]���v���C���[�̉�]�̏�Ԃɍ��킹��
	FPCamera_->update(player_->getTransform().getRot3D_());



	// �X�e�[�W�̍X�V
	stage_->update(delta_time);
	// �v���C���[�̍X�V
	player_->update(delta_time);
	// �G�̃��X�g�̏���
	auto it = enemyList_.begin();
	while (it != enemyList_.end()) {
		(*it)->update(delta_time);
		++it;
	}

	// �^�[���}�l�[�W���[�̍X�V
	turnManager_->update(delta_time);


}

// �`��p�̊֐�
void DungeonSubScene::draw() {

	// �X�e�[�W�̕`��
	stage_->draw(FPCamera_);

	// �G�̃��X�g�̕`�揈��
	auto it = enemyList_.begin();
	while (it != enemyList_.end()) {
		(*it)->draw(FPCamera_);
		++it;
	}


	// �\����������̉摜�̌������v�Z
	switch (player_->getFrontDir()) {
	case Enum::eDir4::UP :
		directionGpcAngle_ = 0;
		break;
	case Enum::eDir4::DOWN:
		directionGpcAngle_ = tnl::PI ;
		break;
	case Enum::eDir4::LEFT:
		directionGpcAngle_ = tnl::PI / 2;
		break;
	case Enum::eDir4::RIGHT:
		directionGpcAngle_ = tnl::PI * 1.5;
		break;
	default :
		directionGpcAngle_ = 0;
		break;
	}

	// �R���p�X�摜�̕\��
	DrawRotaGraph(directionGpcPos_.x, directionGpcPos_.y, directionGpcSize_, directionGpcAngle_, directionGpcHdl_, true);

	// ��������̕\��
	DrawRotaGraph(controlExpPos_.x, controlExpPos_.y, controlExpSize_, 0, controlExpGpcHdl_, true);

}


// �G�������֐�
void DungeonSubScene::DeleteEnemy(std::shared_ptr<Enemy> deleteEnemy) {


	auto it = enemyList_.begin();

	while (it != enemyList_.end()) {

		if ((*it) == deleteEnemy) {

			enemyList_.erase(it);

			turnManager_->setEnemyList(enemyList_);

			break;
		}

		++it;
	}

}


// �v���C���[�A�G�L�����N�^�[���쐬���鏈��
void DungeonSubScene::CreateCharacter() {

	// �v���C���[�̍쐬
	player_ = std::shared_ptr<Player>(new Player(gridSize_, { 1, 1 }, stage_->getGridObjPos( {1, 1} ), turnManager_ ));


	// �v���C���[�̃Z�b�g
	turnManager_->setPlayer(player_);

	// �G�L�����N�^�[�̍쐬
	enemy_ = std::shared_ptr<Enemy>(new Enemy(gridSize_, { 5, 2 }, player_, turnManager_));
	// ���X�g�ɓ����
	enemyList_.emplace_back(enemy_);
	// �G�̃��X�g���Z�b�g
	turnManager_->setEnemyList(enemyList_);

}
