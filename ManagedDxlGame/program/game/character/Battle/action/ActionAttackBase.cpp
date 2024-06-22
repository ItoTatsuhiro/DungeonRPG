#include "ActionAttackBase.h"

#include "../attack/Attack.h"
#include "../../other/BattleCharacterBase.h"


// コンストラクタ
// 引数：actionCharacter ... 行動を行うキャラクター, targetCharacter ... 攻撃対象のキャラクター , attackSize...攻撃のサイズ
ActionAttackBase::ActionAttackBase(std::shared_ptr < BattleCharacterBase > actionCharacter, std::shared_ptr < BattleCharacterBase > targetCharacter) 
	: BattleActionBase(actionCharacter), targetCharacter_(targetCharacter)
{



}


// デストラクタ
ActionAttackBase::~ActionAttackBase() {

}


// 更新用の関数
void ActionAttackBase::update(const float delta_time) {


	if (attack_ != nullptr) {

		attack_->update(delta_time);

	}

}


// 描画用の関数
void ActionAttackBase::draw(std::shared_ptr<dxe::Camera> camera) {


	if (attack_ != nullptr) {

		attack_->draw(camera);

	}

}



// 攻撃のクラスを作成する関数
// 継承先のクラスで攻撃を行う際にこの関数で攻撃のクラスを作成する
// 引数：座標、大きさ、ファイル名、正面の方向、ダメージ
void ActionAttackBase::MakeAttack(tnl::Vector3 pos, float attackSize, std::string fileName, Enum::Dir4 front, float damage) {


	// 攻撃のクラスの作成
	attack_ = std::shared_ptr<Attack>(new Attack(pos, attackSize, fileName, front, damage));

}
