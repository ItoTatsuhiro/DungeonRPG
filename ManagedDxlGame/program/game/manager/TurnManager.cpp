#include "TurnManager.h"
#include "../object/Player.h"
#include "../object/Enemy.h"


// �R���X�g���N�^
TurnManager::TurnManager() {

}

// �^�[���}�l�[�W���[�̃C���X�^���X���擾����֐�
std::shared_ptr<TurnManager> TurnManager::GetInstance() {

	// TurnManager�N���X�̃C���X�^���X
	static std::shared_ptr<TurnManager> instance = nullptr;

	// ���ɐ�������Ă��Ȃ��Ƃ��̂ݐV��������
	if (!instance) {
		instance = std::shared_ptr<TurnManager>(new TurnManager());
	}

	return instance;

}


TurnManager::~TurnManager() {

}


void TurnManager::update(float delta_time) {

	seq_.update(delta_time);

}


void TurnManager::setEnemyList( std::list<std::shared_ptr<Enemy>> enemyList ) {

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


// �v���C���[�̓��͑҂��̃V�[�P���X
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

	// ���ꂼ�ꂪ���Ɉړ�����}�X�ڂ��擾
	tnl::Vector2i nextPlayerPos = player_->getGridPos();
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

	

	if (player_->getNowSeq() == Player::PlayerSeq::WAIT ) {

		auto it = enemyList_.begin();
		while (it != enemyList_.end()) {
			
			if ((*it)->getNowSeqEnemy() == Enemy::EnemySeq::WAIT) {
				return true;
			}

			++it;
		}


	}

	player_->ChangeSeqFromWait();

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



			seq_.change(&TurnManager::seqWaitPlayerInput);
		}

	}


	return true;
}

