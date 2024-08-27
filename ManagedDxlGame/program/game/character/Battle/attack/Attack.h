#pragma once

#include "../../../../dxlib_ext/dxlib_ext.h"
#include "AttackBase.h"
#include "../../other/CharacterTypeEnum.h"


// 通常の攻撃のクラス
// 移動等の特殊な処理は行わない
// 処理はほぼほぼattackBaseクラスの内容
class Attack : public AttackBase {
public :

	// コンストラクタ
	// 引数：座標、大きさ、ファイル名、正面の方向、攻撃のキャラクター属性、ダメージ
	Attack(const tnl::Vector3& pos, float size, std::string fileName, Enum::eDir4 front, eCharaType charaType, float damage = 1.0f );
	// デストラクタ
	virtual ~Attack();
	// 更新用の関数
	virtual void update(float delta_time) override;
	// 描画用の関数
	virtual void draw(const std::shared_ptr<dxe::Camera>& camera) override;



protected :



};
