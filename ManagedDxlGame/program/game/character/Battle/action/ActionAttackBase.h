#pragma once
#include "BattleActionBase.h"
#include "../../../other/Enum.h"

// 前方宣言
class Attack;
class BattleCharacterBase;


// 攻撃を行う行動のベースとなるクラス
// 攻撃の当たり判定を持ち、それに関する処理を行う
class ActionAttackBase : public BattleActionBase {
public :

	// コンストラクタ
	// 引数：actionCharacter ... 行動を行うキャラクター, targetCharacter ... 攻撃対象のキャラクター 
	ActionAttackBase(std::shared_ptr <BattleCharacterBase> actionCharacter, std::shared_ptr <BattleCharacterBase> targetCharacter);

	// デストラクタ
	virtual ~ActionAttackBase();


	//--------------------------------------------------------------------------
	// 継承先のそれぞれの関数でも呼び出す

	// 更新用の関数
	void update(const float delta_time);

	// 描画用の関数
	void draw(std::shared_ptr<dxe::Camera> camera);

	//--------------------------------------------------------------------------


	// 攻撃のクラスを作成する関数
	// 継承先のクラスで攻撃を行う際にこの関数で攻撃のクラスを作成する
	// 引数：座標、大きさ、ファイル名、正面の方向、ダメージ
	void MakeAttack(tnl::Vector3 pos, float attackSize, std::string fileName, Enum::Dir4 front, float damage);


protected :

	// 攻撃のクラス
	std::shared_ptr< Attack > attack_ = nullptr;

	// 攻撃対象のキャラクター
	// コンストラクタで初期化
	std::shared_ptr< BattleCharacterBase > targetCharacter_;

};
