#include "ScenePlay.h"

#include "../manager/TurnManager.h"

ScenePlay::ScenePlay() {

	// camera_ = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	FPCamera_ = std::make_shared< TransformCamera >(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// �X�e�[�W���Ǘ�����N���X�̐���
	stage_ = Stage::GetInstance("test", "csv/mapData.csv", gridSize_);

	
	turnManager_ = TurnManager::GetInstance();


	CreateCharacter();

}


ScenePlay::~ScenePlay() {

}


void ScenePlay::update(float delta_time) {

	DrawGridGround(FPCamera_, 50, 20);

	FPCamera_->pos_ = player_->getTransform().getPos_();
	//FPCamera_->angle_ = tnl::ToRadian(15);


	FPCamera_->update( player_->getTransform().getRot3D_() );



	// �X�e�[�W�̍X�V
	stage_->update(delta_time);

	player_->update(delta_time);

	// �G�̃��X�g�̏���
	auto it = enemyList_.begin();
	while (it != enemyList_.end()) {
		(*it)->update(delta_time);
		++it;
	}

	TurnManager::GetInstance()->update(delta_time);


	// enemy_->update(delta_time);





}

void ScenePlay::draw() {

	// �X�e�[�W�̕`��
	stage_->draw(FPCamera_);

	// enemy_->draw(FPCamera_);

	// �G�̃��X�g�̕`�揈��
	auto it = enemyList_.begin();

	while (it != enemyList_.end()) {
		(*it)->draw(FPCamera_);
		++it;
	}

}


void ScenePlay::CreateCharacter() {

	// �v���C���[�̍쐬
	player_ = std::shared_ptr<Player>(new Player(gridSize_, { 0, 0 }));

	TurnManager::GetInstance()->setPlayer(player_);

	enemy_ = std::shared_ptr<Enemy>(new Enemy(gridSize_, { 4, 1 }, player_));


	enemyList_.emplace_back(enemy_);

	TurnManager::GetInstance()->setEnemyList(enemyList_);
}
