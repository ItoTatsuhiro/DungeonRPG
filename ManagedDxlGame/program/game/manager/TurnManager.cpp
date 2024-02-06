#include "TurnManager.h"
#include "../object/Player.h"
#include "../object/Enemy.h"


// コンストラクタ
TurnManager::TurnManager() {

}

// ターンマネージャーのインスタンスを取得する関数
std::shared_ptr<TurnManager> TurnManager::GetInstance() {

	// TurnManagerクラスのインスタンス
	static std::shared_ptr<TurnManager> instance = nullptr;

	// 既に生成されていないときのみ新しく生成
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

// プレイヤーが入力が行われた際に呼び出す関数
// 敵の処理を行うシーケンスに遷移するための関数
void TurnManager::ChangeSeqFromWaitPlayerInput() {

	if (nowSeq_ != TurnManagerSeq::WAIT_PLAYER_INPUT) {
		tnl::DebugTrace("ターンマネージャー用のプレイヤーの入力終了の関数呼び出しのタイミングが誤っています\n");
		return;
	}
	
	// シーケンスを切り替え
	seq_.change(&TurnManager::seqEnemyActionDecade);

	return;
}

// プレイヤーの行動が終了した際に呼び出す関数
// actionEndPlayer_をtrueにする
void TurnManager::ActionEndPlayer() {
	// プレイヤーの処理が終了した
	actionEndPlayer_ = true;
	return;
}


// 敵の行動が終了した際に呼び出す関数
// actionEndEnemyListのうち、falseを一つtrueにする関数
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


// プレイヤーの入力待ちのシーケンス
bool TurnManager::seqWaitPlayerInput(const float delta_time) {



	return true;
}


// 敵キャラクターの行動を決定するシーケンス
bool TurnManager::seqEnemyActionDecade(const float delta_time) {

	
	// 敵を待機状態から遷移させる処理
	auto it = enemyList_.begin();
	while (it != enemyList_.end()) {

		(*it)->ChangeSeqFromIdle();
		++it;
	}

	seq_.change(&TurnManager::seqCheckAction);

	return true;
}

// それぞれのキャラクターの行動を確認するシーケンス
bool TurnManager::seqCheckAction(const float delta_time) {

	// それぞれが次に移動するマス目を取得
	tnl::Vector2i nextPlayerPos = player_->getGridPos();
	// 敵の現在のマス目のリスト
	std::list<tnl::Vector2i> enemyPosList;

	auto it = enemyList_.begin();
	while (it != enemyList_.end()) {
		enemyPosList.emplace_back((*it)->getGridPos());
		++it;
	}

	// 敵の現在の座標がプレイヤーの次の座標と重なるか確認
	// 重なる場合は移動を止める
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

// 行動を行うシーケンス
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

	// 敵が通常通り動けるとき
	if (canMoveEnemy_) {
		auto it = enemyList_.begin();
		while (it != enemyList_.end()) {
			(*it)->ChangeSeqFromWait();
			++it;
		}
	}
	// 敵が動けないとき
	else if (!canMoveEnemy_) {
		// プレイヤーの処理が終わってから敵が動くことができるようにする
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
			// 処理が終了していないものがあれば以下は行わない
			if ((*it) == false) { break; }
			++it;
		}
		// 処理が全て終了していれば初期のシーケンスに戻す
		if (it == actionEndEnemyList_.end()) {



			seq_.change(&TurnManager::seqWaitPlayerInput);
		}

	}


	return true;
}

