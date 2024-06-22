#pragma once

#include "../../base/SpriteObjectBase.h"
#include "StatusCharacter.h"
#include "../Battle/attack/Attack.h"


// バトルシーンでのキャラクターのベースとなるクラス
// *************************************************************
// 継承先のクラスでは、update,draw関数をそれぞれ呼び出すこと！
// *************************************************************
// 引数：tnl::Vector3 startPos...開始位置, float objSize...キャラクターの大きさ,
//		std::string objectName...オブジェクト(キャラクター)名
class BattleCharacterBase : public SpriteObjectBase {
public :

	// コンストラクタ
	BattleCharacterBase(tnl::Vector3 startPos, float objSize, std::string objectName);
	// デストラクタ
	virtual ~BattleCharacterBase();

	// 更新用の関数
	// *********************************************************************
	// 継承先のupdate関数でも、このクラスのupdate関数を呼び出すこと!!
	// *********************************************************************
	virtual void update(float delta_time) = 0;

	// 描画用の関数
	// *********************************************************************
	// 継承先のdraw関数でも、このクラスのdraw関数を呼び出すこと!!
	// *********************************************************************
	// 処理内容
	// 1.描画するメッシュの座標を更新
	// 2.攻撃のメッシュの描画
	void draw(std::shared_ptr<dxe::Camera> camera) = 0;


	// キャラクターのベースステータス
	// コンストラクタで生成
	std::shared_ptr< StatusCharacter > status_;


	// キャラクターを移動させる関数
	// 継承先のそれぞれのキャラクタークラスでキャラクターを動かす際にこの関数を用いて動かす
	void MoveCharacter(tnl::Vector3 moveVector, float moveVectorMag = 1.0f);

	// ダメージを受ける関数
	// 引数：damage...受けるダメージ
	void TakeDamage(float damage);





	// ******************************************************************************
	// 以下ゲッター

	// 移動前の座標を取得する関数
	// 座標の補正等の際に使用
	inline tnl::Vector3 getBeforePos() const { return beforePos_; }

	// 移動量を取得するための関数
	inline float getMoveValue() const { return moveValue_; }

	// ダメージが入る状態かどうか取得する関数
	inline bool getCanTakeDamage() const { return canTakeDamage_; }

	// 攻撃のリストを取得する関数
	inline const std::list<std::shared_ptr<Attack>>& getActiveAttackList() const { return activeAttackList_; }

protected :

	// 移動前の座標
	// 座標の補正の際にこの座標を使用する
	tnl::Vector3 beforePos_;


	// 移動量
	float moveValue_ = 5;


	// 攻撃の大きさ
	// コンストラクタで初期化
	// 基本キャラクターの1.5倍とする(仮)
	float attackSize_;

	// ダメージを受ける状態かどうかのフラグ
	bool canTakeDamage_ = true;

	// 無敵時間のカウント
	float invincibleTimeCount_ = 0.0f;
	// 無敵時間の最大時間
	// ダメージを受けたときカウントをこの時間にする
	float invincibleTimeMax_ = 1.0f;

	// 点滅時間のカウント
	float invincibleBlinkCount_ = 0.0f;
	// 点滅間隔
	float invincibleBlinkInterval_ = 0.15f;
	// 点滅させるための描画するかどうかのフラグ
	bool isDisplay_ = true;


	// 発生している攻撃のリスト
	std::list<std::shared_ptr<Attack>> activeAttackList_;

};