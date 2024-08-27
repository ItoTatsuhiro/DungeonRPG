#pragma once
#include "BattleActionBase.h"
#include "../../../other/Enum.h"




// 前方宣言
class Attack;
class BattleCharacterBase;
class BattlePlayer;


// 攻撃を行う行動のベースとなるクラス
// 攻撃の当たり判定を持ち、それに関する処理を行う
//
// ************************************************************
// ※注記
// 現在update関数では攻撃を更新する処理のみ行っているため、
// 継承先では攻撃の処理を行う箇所で更新を行うこと！
// ************************************************************
class ActionAttackBase : public BattleActionBase {
public :

	// コンストラクタ
	// 引数：actionCharacter ... 行動を行うキャラクター, targetCharacter ... 攻撃対象のキャラクター 
	ActionAttackBase(std::shared_ptr <BattleCharacterBase> actionCharacter, std::shared_ptr<std::list<std::shared_ptr< BattleCharacterBase >>> charaList);

	// デストラクタ
	virtual ~ActionAttackBase();


	//--------------------------------------------------------------------------
	// 継承先のそれぞれの関数でも呼び出す

	// 更新用の関数
	// ************************************************************
	// 攻撃の処理の更新のみ行っているため、継承先では
	// 攻撃の処理をしている箇所でこの関数を更新すること！
	// ************************************************************
	void update(const float delta_time);

	// 描画用の関数
	void draw(std::shared_ptr<dxe::Camera> camera);

	//--------------------------------------------------------------------------


	// 攻撃対象のキャラクターをリスト内から選択する処理
	// 仮想関数としているので、必要な継承先のクラスでは作成すること
	virtual void SelectTargetCharacter() {};


	// 攻撃のクラスを作成する関数
	// 継承先のクラスで攻撃を行う際にこの関数で攻撃のクラスを作成する
	// 生成するのは通常の攻撃クラスなので、他の処理が必要な場合はオーバーライドして使用すること
	// 引数：座標、大きさ、ファイル名、正面の方向、ダメージ
	virtual void MakeAttack(std::string fileName = "attackKari.png", tnl::Vector3 pos = {0, 0, 0}, 
							float attackSize = 50, Enum::eDir4 front = Enum::eDir4::UP, float damage = 1.0f);


protected :


	// 攻撃のクラス
	std::weak_ptr< Attack > attack_;



	// キャラクターのリスト
	// この中から対象のキャラクターを選択する
	std::weak_ptr<std::list<std::shared_ptr< BattleCharacterBase >>> charaList_;


	// 攻撃対象のキャラクター
	// コンストラクタで初期化
	std::weak_ptr< BattleCharacterBase > targetCharacter_;

};
