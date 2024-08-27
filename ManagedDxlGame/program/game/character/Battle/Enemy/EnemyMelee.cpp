#include "EnemyMelee.h"
#include "../action/BattleActionBase.h"
#include "../action/enemyAction/ActionMove.h"
#include "../action/enemyAction/ActionWait.h"

// コンストラクタ
// 引数はBattleEnemyの初期化用
// 引数：tnl::Vector3 startPos...開始位置, float objSize...オブジェクトの大きさ, std::string fileName...貼り付けるテクスチャのパス
// 移動前の座標は開始位置で初期化
// SpriteObjectBaseの引数も入れる
BattleEnemyMelee::BattleEnemyMelee(tnl::Vector3 startPos, float objSize, std::string fileName, std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>> charaList)
	: BattleEnemy(startPos, objSize, fileName, charaList)
{

	moveValue_ = 2.5;

}

// デストラクタ
BattleEnemyMelee::~BattleEnemyMelee() {

}


// クラスの生成用の関数
std::shared_ptr<BattleEnemyMelee> BattleEnemyMelee::Create(tnl::Vector3 startPos, float objSize, std::string fileName, std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>> charaList) {

	// クラスのインスタンスを生成
	std::shared_ptr<BattleEnemyMelee> instance(new BattleEnemyMelee(startPos, objSize, fileName, charaList));
	instance->actionList_.emplace_back(std::shared_ptr<ActionMove>(new ActionMove(instance)));
	instance->actionList_.emplace_back(std::shared_ptr<ActionWait>(new ActionWait(instance)));
	

	return instance;
}



// 更新用の関数
void BattleEnemyMelee::update(const float delta_time) {

	// BattleEnemyの更新
	BattleEnemy::update(delta_time);

}

// 描画用の関数
void BattleEnemyMelee::draw(const std::shared_ptr< dxe::Camera >& camera) {

	// BattleEnemyの描画
	BattleEnemy::draw(camera);

}
