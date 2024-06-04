#include "Enemy_Escape.h"
#include "../action/BattleActionBase.h"
#include "../action/enemyAction/ActionMove.h"
#include "../action/enemyAction/ActionWait.h"

// コンストラクタ
// 引数はBattleEnemyの初期化用
// 引数：tnl::Vector3 startPos...開始位置, float objSize...オブジェクトの大きさ, std::string fileName...貼り付けるテクスチャのパス
// 移動前の座標は開始位置で初期化
// SpriteObjectBaseの引数も入れる
BattleEnemyEscape::BattleEnemyEscape(tnl::Vector3 startPos, float objSize, std::string fileName) 
	: BattleEnemy(startPos, objSize, fileName)
{

	moveValue_ = 2.5;

}

// デストラクタ
BattleEnemyEscape::~BattleEnemyEscape() {

}


// クラスの生成用の関数
std::shared_ptr<BattleEnemyEscape> BattleEnemyEscape::Create(tnl::Vector3 startPos, float objSize, std::string fileName) {

	// クラスのインスタンスを生成
	std::shared_ptr<BattleEnemyEscape> instance(new BattleEnemyEscape(startPos, objSize, fileName));
	instance->actionList_.emplace_back(std::shared_ptr<ActionMove>( new ActionMove(instance) ));
	instance->actionList_.emplace_back(std::shared_ptr<ActionWait>( new ActionWait(instance) ));

	return instance;
}



// 更新用の関数
void BattleEnemyEscape::update(const float delta_time) {

	// BattleEnemyの更新
	BattleEnemy::update(delta_time);

}

// 描画用の関数
void BattleEnemyEscape::draw( std::shared_ptr< dxe::Camera > camera ) {

	// BattleEnemyの描画
	BattleEnemy::draw( camera );

}
