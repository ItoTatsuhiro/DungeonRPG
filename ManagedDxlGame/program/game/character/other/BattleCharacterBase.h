#pragma once

#include "../../base/SpriteObjectBase.h"
#include "StatusCharacter.h"

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
	void draw(std::shared_ptr<dxe::Camera> camera) = 0;

	// ******************************************************************************
	// 以下ゲッター

	// 移動前の座標を取得する関数
	// 座標の補正等の際に使用
	inline tnl::Vector3 getBeforePos() const { return beforePos_; }

protected :

	// 移動前の座標
	// 座標の補正の際にこの座標を使用する
	tnl::Vector3 beforePos_;

	// 移動量
	float moveValue_ = 5;


	// 通常時のステータス
	// 変動した際のステータスを元に戻すのに使用
	StatusCharacter baseStatus_;
	// 何らかの要因で変動したステータス
	// (バフ、デバフ等)
	StatusCharacter changeStatus_;

	// 発生している攻撃のリスト
	std::list<std::shared_ptr<SpriteObjectBase>> attackList_;

};