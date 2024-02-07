#include "DungeonSubScene.h"
#include "../../map/Stage.h"
#include "../../object/Player.h"
#include "../../object/Enemy.h"
#include "../../manager/TurnManager.h"
#include "../../other/TransformCamera.h"


// �R���X�g���N�^
DungeonSubScene::DungeonSubScene() {

	// �`��p�̃J�����̏�����
	FPCamera_ = std::make_shared< TransformCamera >(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// �X�e�[�W���Ǘ�����N���X�̐���
	stage_ = Stage::GetInstance("test", "csv/mapData.csv", gridSize_);


	CreateCharacter();


}

// �f�X�g���N�^
DungeonSubScene::~DungeonSubScene() {


}

// �X�V�p�̊֐�
void DungeonSubScene::update(float delta_time){

	// ���̕`��
	DrawGridGround(FPCamera_, 50, 20);

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
	TurnManager::GetInstance()->update(delta_time);


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

}


// �v���C���[�A�G�L�����N�^�[���쐬���鏈��
void DungeonSubScene::CreateCharacter() {

	// �v���C���[�̍쐬
	player_ = std::shared_ptr<Player>(new Player(gridSize_, { 0, 0 }));
	// �v���C���[�̃Z�b�g
	TurnManager::GetInstance()->setPlayer(player_);

	// �G�L�����N�^�[�̍쐬
	enemy_ = std::shared_ptr<Enemy>(new Enemy(gridSize_, { 4, 1 }, player_));
	// ���X�g�ɓ����
	enemyList_.emplace_back(enemy_);
	// �G�̃��X�g���Z�b�g
	TurnManager::GetInstance()->setEnemyList(enemyList_);

}