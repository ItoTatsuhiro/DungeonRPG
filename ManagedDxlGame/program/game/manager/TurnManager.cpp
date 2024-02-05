#include "TurnManager.h"



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


void TurnManager::update() {



}


