#pragma once
#include "../../../../dxlib_ext/dxlib_ext.h"
#include "../../../other/Enum.h"
#include "../../../base/SpriteObjectBase.h"
#include "../action/BattleActionBase.h"
#include "../../other/CharacterTypeEnum.h"

// 攻撃のクラス
// 当たり判定用のメッシュを持つ
// 
// ※※注意点※※
// 継承先のクラスでは以下を実装すること！
// ・OnHit関数をオーバーライドする関数
class AttackBase : public SpriteObjectBase {
public:

	// コンストラクタ
	// 引数：座標、大きさ、ファイル名、正面の方向、攻撃のキャラクター属性、ダメージ
	AttackBase(tnl::Vector3 pos, float size, std::string fileName, Enum::eDir4 front, eCharaType charaType, float damage = 1.0f);
	// デストラクタ
	virtual ~AttackBase();
	// 更新用の関数
	virtual void update(float delta_time) override;
	// 描画用の関数
	virtual void draw(const std::shared_ptr<dxe::Camera>& camera) override;


	// creatorAction_をセットする関数
	// 攻撃が終了した際にキャラクターの行動シーケンスを切り替える必要がある場合はここにセットする
	inline void setCreatorAction(std::shared_ptr<BattleActionBase> creatorAction)
	{
		creatorAction_ = creatorAction;
	}



	// 攻撃が衝突した際に実行する関数
	// ******************************************************
	// 継承先のクラスではオーバーライドする関数を必ず作成すること！
	// ******************************************************
	virtual void OnHit();



	//-------------------------------------------------------------
	// ゲッター

	// ダメージの数値を取得する関数
	inline float getDamage() const { return damage_; }

	// ゲームの終了状態を取得する関数
	inline bool getIsEnd() const { return isEnd_; }

	// キャラクターの属性を取得する関数
	inline eCharaType getCharacterType() const { return charaType_; }


	// -------------------------------------------------------------
	// セッター

	// isHit（攻撃自身が当たったかどうかのフラグ）のセッター
	inline void setIsHit(const bool isHit) { isHit_ = isHit; }

	// キャラクター属性をセットする関数
	inline void setCharacterType(const eCharaType newType) { charaType_ = newType; }

protected:

	// どのキャラクターの攻撃かを表す変数
	// 基本的に同じ属性のキャラクターには当たらないようにする
	// デフォルトでは属性未設定のため、必ず各継承先のコンストラクタで設定すること
	eCharaType charaType_ = eCharaType::NONE;


	// 自身を作った行動のクラス
	// 処理が終了した際に、攻撃が終了したことを伝える必要がある場合はここに入れる
	std::weak_ptr<BattleActionBase> creatorAction_;



	// 攻撃ヒット時に再生する音のハンドル
	// デフォルトでは設定していないので、必要な時はここにロードして使用する
	int hitSoundHdl_ = 0;



	// ダメージ
	float damage_;

	// ループするかどうか
	// ループしない場合はアニメーションの1ループで基本削除する
	bool isLoop_;

	// 終了しているかどうか
	// デフォルトでfalse
	// 処理を終了させるときはこのフラグをtrueにする
	bool isEnd_;

	// 攻撃が当たったかどうかのフラグ
	// デフォルトはfalseで、trueになった際に当たった際の処理を行う
	// ・近距離攻撃は基本何もしない
	// ・遠距離攻撃は基本当たったら当たった際のエフェクトを出して消す
	bool isHit_;

	// ステージとの当たり判定をとるか否かの変数
	// 基本的に、近距離攻撃はfalse、遠距離攻撃をtrueにする想定
	// デフォルトはfalseにする（コンストラクタ）
	bool checkHitStage_;

};



