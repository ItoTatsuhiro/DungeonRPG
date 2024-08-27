#include "Attack.h"
#include "../../../manager/ObjectManager.h"





// コンストラクタ
// 引数：座標、大きさ、ファイル名、正面の方向(LEFTかRIGHT), 攻撃のキャラクター属性, ダメージ
// Object3Dのメッシュを当たり判定用のメッシュとして作成する
Attack::Attack(const tnl::Vector3& pos, float size, std::string fileName, Enum::eDir4 front, eCharaType charaType, float damage)
	: AttackBase(pos, size, fileName, front, charaType, damage)
{



}

// デストラクタ
Attack::~Attack() {




}


// 更新用の関数
void Attack::update(float delta_time) {

	// 基底クラスの更新
	AttackBase::update(delta_time);



}

// 描画用の関数
void Attack::draw(const std::shared_ptr<dxe::Camera>& camera) {

	// 基底クラスの描画
	AttackBase::draw(camera);



}


