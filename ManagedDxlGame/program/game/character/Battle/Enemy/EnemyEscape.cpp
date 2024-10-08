#include "EnemyEscape.h"
#include "../action/BattleActionBase.h"
#include "../action/enemyAction/ActionMove.h"
#include "../action/enemyAction/ActionWait.h"
#include "../action/enemyAction/ActionMeleeAttack.h"


// コンストラクタ
// 引数はBattleEnemyの初期化用
// 引数：tnl::Vector3 startPos...開始位置, float objSize...オブジェクトの大きさ, std::string fileName...貼り付けるテクスチャのパス
// 移動前の座標は開始位置で初期化
// SpriteObjectBaseの引数も入れる
BattleEnemyEscape::BattleEnemyEscape(tnl::Vector3 startPos, float objSize, std::string fileName, std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>> charaList)
	: BattleEnemy(startPos, objSize, fileName, charaList)
{
	// 敵キャラクター用の移動量を設定
	moveValue_ = 150;


}

// デストラクタ
BattleEnemyEscape::~BattleEnemyEscape() {

}


// クラスの生成用の関数
std::shared_ptr<BattleEnemyEscape> BattleEnemyEscape::Create(tnl::Vector3 startPos, float objSize, std::string fileName, std::shared_ptr<std::list<std::shared_ptr<BattleCharacterBase>>> charaList) {

	// クラスのインスタンスを生成
	std::shared_ptr<BattleEnemyEscape> instance(new BattleEnemyEscape(startPos, objSize, fileName, charaList));
	instance->actionList_.emplace_back(std::shared_ptr<ActionMove>( new ActionMove(instance) ));
	instance->actionList_.emplace_back(std::shared_ptr<ActionWait>( new ActionWait(instance) ));
	instance->actionList_.emplace_back(std::shared_ptr<ActionMeleeAttack>(new ActionMeleeAttack(instance, charaList)));


	return instance;
}



// 更新用の関数
void BattleEnemyEscape::update(const float delta_time) {

	// BattleEnemyの更新
	BattleEnemy::update(delta_time);

}

// 描画用の関数
void BattleEnemyEscape::draw(const std::shared_ptr< dxe::Camera >& camera ) {

	// 表示する画像の範囲を切り替える処理

	// 待機、移動、攻撃後の待機の状態の時
	if (nowSituation_ == Situation::WAITING || nowSituation_ == Situation::MOVING || nowSituation_ == Situation::WAITING_AFTER_ATTACK) {

		// 左向きの時
		if (frontDir_ == Enum::eDir4::LEFT) {
			displayObj_.y = 5;
		}
		// それ以外のとき
		else {
			displayObj_.y = 4;
		}

	}
	// 攻撃前の待機状態の時
	else if (nowSituation_ == Situation::WAITING_BEFORE_ATTACK) {
		// 左向きの時
		if (frontDir_ == Enum::eDir4::LEFT) {
			displayObj_.y = 3;
		}
		// それ以外のとき
		else {
			displayObj_.y = 2;
		}
	}
	else if (nowSituation_ == Situation::ATTACKING) {
		// 左向きの時
		if (frontDir_ == Enum::eDir4::LEFT) {
			displayObj_.y = 1;
		}
		// それ以外のとき
		else {
			displayObj_.y = 0;
		}
	}



	// BattleEnemyの描画
	BattleEnemy::draw( camera );

}
