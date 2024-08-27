#include "ActionAttackBase.h"

#include "../attack/Attack.h"
#include "../../other/BattleCharacterBase.h"


// コンストラクタ
// 引数：actionCharacter ... 行動を行うキャラクター, targetCharacter ... 攻撃対象のキャラクター , attackSize...攻撃のサイズ
ActionAttackBase::ActionAttackBase(std::shared_ptr < BattleCharacterBase > actionCharacter, std::shared_ptr<std::list<std::shared_ptr< BattleCharacterBase >>> charaList)
	: BattleActionBase(actionCharacter), charaList_(charaList)
{



}


// デストラクタ
ActionAttackBase::~ActionAttackBase() {

}


// 更新用の関数
// ************************************************************
// 攻撃の処理の更新のみ行っているため、継承先では
// 攻撃の処理をしている箇所でこの関数を更新すること！
// ************************************************************
void ActionAttackBase::update(const float delta_time) {



	//// 攻撃の更新
	//attack_->update(delta_time);


}


// 描画用の関数
void ActionAttackBase::draw(std::shared_ptr<dxe::Camera> camera) {

	//// attack_が存在していないとき処理しない
	//if (attack_ == nullptr) {
	//	return;
	//}
	//// attackの処理が終了しているときも処理を行わない
	//if (attack_->getIsEnd()) {
	//	return;
	//}

	//// 攻撃の描画
	//attack_->draw(camera);

}



// 攻撃のクラスを作成する関数
// 継承先のクラスで攻撃を行う際にこの関数で攻撃のクラスを作成する
// 引数：座標、大きさ、ファイル名、正面の方向（デフォルトで上）、ダメージ（デフォルトで1）
void ActionAttackBase::MakeAttack(std::string fileName, tnl::Vector3 pos, float attackSize, Enum::eDir4 front, float damage) {


	auto actionCharacter = actionCharacter_.lock();

	if (!actionCharacter) {
		return;
	}


	// 攻撃のクラスの作成
	std::shared_ptr<Attack> attack = std::shared_ptr<Attack>(new Attack(pos, attackSize, fileName, front, eCharaType::ENEMY,damage));
	// 状態をfalseにする
	attack->setIsActive(false);

	// メンバー変数として所持している攻撃のクラスに設定
	attack_ = attack;

	actionCharacter->addActiveAttack(attack);

	

}
