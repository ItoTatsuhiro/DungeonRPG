#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

#include "../object/Enemy.h"

// ターンの処理を管理する用のクラス
// プレイヤー、敵の処理状態を確認し、揃える役割
class TurnManager {
private :

	// コンストラクタ
	TurnManager();

public :

	// ターンマネージャーのインスタンスを取得する関数
	static std::shared_ptr<TurnManager> GetInstance();

	// デストラクタ
	~TurnManager();

	// 更新用の関数
	void update();


private :



	// 管理を行う敵リスト
	// 行動を行う敵キャラクター(オブジェクト)はこのリストに入れる
	std::list< Enemy > enemyList_;


	


};