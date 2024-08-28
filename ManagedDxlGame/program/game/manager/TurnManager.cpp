#include "TurnManager.h"
#include "../character/Dungeon/Player.h"
#include "../character/Dungeon/Enemy.h"

#include "../map/Stage.h"
#include "SubSceneManager.h"
#include "../scene/SceneClear.h"

// �R���X�g���N�^
TurnManager::TurnManager() {
	// ���Ƃ�CSV����ǂݍ��ނ悤�ɕύX����
	transGpc_ = LoadGraph("graphics/myGpc/black.png");

	goalPos_ = Stage::GetInstance()->getGoalPos();

}




TurnManager::~TurnManager() {

}


void TurnManager::update(float delta_time) {


	seq_.update(delta_time);

}


void TurnManager::setEnemyList( std::list<std::shared_ptr<Enemy>> enemyList ) {

	

	enemyList_.clear();


	enemyList_ = enemyList;

	actionEndEnemyList_.clear();

	for (int i = 0; i < enemyList_.size(); ++i) {

		actionEndEnemyList_.emplace_back(false);

	}

}

// �v���C���[�����͂��s��ꂽ�ۂɌĂяo���֐�
// �G�̏������s���V�[�P���X�ɑJ�ڂ��邽�߂̊֐�
void TurnManager::ChangeSeqFromWaitPlayerInput() {

	if (nowSeq_ != TurnManagerSeq::WAIT_PLAYER_INPUT) {
		tnl::DebugTrace("�^�[���}�l�[�W���[�p�̃v���C���[�̓��͏I���̊֐��Ăяo���̃^�C�~���O������Ă��܂�\n");
		return;
	}
	
	// �V�[�P���X��؂�ւ�
	seq_.change(&TurnManager::seqEnemyActionDecade);

	return;
}

// �v���C���[�̍s�����I�������ۂɌĂяo���֐�
// actionEndPlayer_��true�ɂ���
void TurnManager::ActionEndPlayer() {
	// �v���C���[�̏������I������
	actionEndPlayer_ = true;
	return;
}


// �G�̍s�����I�������ۂɌĂяo���֐�
// actionEndEnemyList�̂����Afalse�����true�ɂ���֐�
void TurnManager::ActionEndEnemy() {

	auto it = actionEndEnemyList_.begin();
	while (it != actionEndEnemyList_.end()) {

		if ((*it) == false) {
			(*it) = true;
			break;
		}

		++it;
	}
	if (it == actionEndEnemyList_.end()) { return; }

	return;
}


// ���g���폜����֐�
void TurnManager::Destroy() {

	delete this;

}



// �L�����N�^�[�̈ʒu���m�F����֐�
void TurnManager::CheckCharacterPos() {

	auto player = player_.lock();
	// auto battlingEnemy = battlingEnemy_.lock();

	if (!player) {
		return;
	}

	tnl::Vector2i playerGrid = player->getGridPos();

	auto it = enemyList_.begin();

	while (it != enemyList_.end()) {

		if (playerGrid == (*it)->getGridPos()) {


			battlingEnemy_ = (*it);

			// �V�[����؂�ւ��邽�߂̃V�[�P���X�ɕύX
			seq_.change(&TurnManager::seqChangeSubScene);


			return;
		}
		++it;
	}

	if (playerGrid == goalPos_) {
		
		// �V�[����؂�ւ�
		ito::GameManager::GetInstance_()->changeScene( std::shared_ptr< SceneClear >(new SceneClear()) );

		SubSceneManager::GetInstance()->DeleteSubScene();

		isSceneChange_ = true;


	}
	
	return;
}


// �v���C���[�̓��͑҂��̃V�[�P���X
// ChangeSeqFromWaitPlayerInput()���v���C���[���Ăяo�����ƂŁA
// ���̃V�[�P���X�ɑJ�ڂ���
bool TurnManager::seqWaitPlayerInput(const float delta_time) {



	return true;
}


// �G�L�����N�^�[�̍s�������肷��V�[�P���X
bool TurnManager::seqEnemyActionDecade(const float delta_time) {

	
	// �G��ҋ@��Ԃ���J�ڂ����鏈��
	auto it = enemyList_.begin();
	while (it != enemyList_.end()) {

		(*it)->ChangeSeqFromIdle();
		++it;

	}

	seq_.change(&TurnManager::seqCheckAction);

	return true;
}

// ���ꂼ��̃L�����N�^�[�̍s�����m�F����V�[�P���X
bool TurnManager::seqCheckAction(const float delta_time) {

	auto player = player_.lock();

	if (!player) {
		return true;
	}

	// ���ꂼ�ꂪ���Ɉړ�����}�X�ڂ��擾
	tnl::Vector2i nextPlayerPos = (player-> getNextGridPos());


	// �G�̌��݂̃}�X�ڂ̃��X�g
	std::list<tnl::Vector2i> enemyPosList;

	auto it = enemyList_.begin();
	while (it != enemyList_.end()) {
		enemyPosList.emplace_back((*it)->getGridPos());
		++it;
	}

	// �G�̌��݂̍��W���v���C���[�̎��̍��W�Əd�Ȃ邩�m�F
	// �d�Ȃ�ꍇ�͈ړ����~�߂�
	auto _it = enemyPosList.begin();
	while (_it != enemyPosList.end()) {

		if (nextPlayerPos == (*_it)) {
			canMoveEnemy_ = false;
			break;
		}
		++_it;
	}



	seq_.change(&TurnManager::seqAction);

	return true;


}

// �s�����s���V�[�P���X
bool TurnManager::seqAction(const float delta_time) {

	auto player = player_.lock();

	// �v���C���[�����݂��Ă��Ȃ��Ƃ��������s��Ȃ�
	if (!player) {

		return true;
	}

	if (actionEndPlayer_) {

		auto it = actionEndEnemyList_.begin();
		while (it != actionEndEnemyList_.end())
		{
			// �������I�����Ă��Ȃ����̂�����Έȉ��͍s��Ȃ�
			if ((*it) == false) { break; }
			++it;
		}
		// �������S�ďI�����Ă���Ώ����̃V�[�P���X�ɖ߂�
		if (it == actionEndEnemyList_.end()) {

			actionEndPlayer_ = false;

			seq_.change(&TurnManager::seqWaitPlayerInput);
			CheckCharacterPos();
			
		}
		
	}

	if (isSceneChange_) {
		return true;
	}

	if (player->getNowSeq() == Player::PlayerSeq::WAIT ) {

		auto it = enemyList_.begin();
		while (it != enemyList_.end()) {
			
			if ((*it)->getNowSeqEnemy() != Enemy::EnemySeq::WAIT) {
				return true;
			}

			++it;
		}


	}

	player->ChangeSeqFromWait();

	// �G���ʏ�ʂ蓮����Ƃ�
	if (canMoveEnemy_) {
		auto it = enemyList_.begin();
		while (it != enemyList_.end()) {
			(*it)->ChangeSeqFromWait();
			++it;
		}
	}
	// �G�������Ȃ��Ƃ�
	else if (!canMoveEnemy_) {
		// �v���C���[�̏������I����Ă���G���������Ƃ��ł���悤�ɂ���
		if (actionEndPlayer_) {
			auto it = enemyList_.begin();
			while (it != enemyList_.end()) {
				(*it)->ChangeSeqFromWait();
				++it;
			}
		}
	}


	return true;
}

bool TurnManager::seqChangeSubScene(const float delta_time) {

	auto battlingEnemy = battlingEnemy_.lock();

	if (!battlingEnemy) {
		return true;
	}

	// �V�[���؂�ւ�
	SubSceneManager::GetInstance()->ChangeSubScene(SubSceneManager::ScenePlaySubScene::BATTLE, battlingEnemy);

	seq_.change(&TurnManager::seqCheckAction);

	return true;

}