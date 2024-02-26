#include "BattleCharacterBase.h"

// コンストラクタ
// 引数：startPos...開始位置, objSize...作成するキャラクターの大きさ, objName...名前
// 移動前の座標は開始位置で初期化
BattleCharacterBase::BattleCharacterBase(tnl::Vector3 startPos, float objSize, std::string objName)
	: beforePos_(startPos), SpriteObjectBase(startPos, objSize, objName) {


	// SpriteObjectBaseクラスの関数
	// テクスチャを表示する用のplaneの配列を作成する
	CreateSpriteObjArray("travellerAnim.png");


	displayObj_ = tnl::Vector2i(1, textureCutNum_.y - 2);


	return;
}

// デストラクタ
BattleCharacterBase::~BattleCharacterBase() {

}

// 更新用の関数
// *********************************************************************
// 継承先のupdate関数でも、このクラスのupdate関数を呼び出すこと!!
// *********************************************************************
void BattleCharacterBase::update(float delta_time) {

	// 攻撃の処理を実行
	auto it = attackList_.begin();
	while (it != attackList_.end()) {
		(*it)->update(delta_time);

		if (!((*it)->getIsActive())) {

			it = attackList_.erase(it);

		}
		else {
			++it;
		}
	}
}


// 描画用の関数
// *********************************************************************
// 継承先のdraw関数でも、このクラスのdraw関数を呼び出すこと!!
// *********************************************************************
void BattleCharacterBase::draw(std::shared_ptr<dxe::Camera> camera ) {

	SpriteObjectBase::draw(camera);

	// 攻撃のメッシュを描画
	auto it = attackList_.begin();
	while (it != attackList_.end()) {
		(*it)->draw(camera);

		++it;
	}

	return;

}