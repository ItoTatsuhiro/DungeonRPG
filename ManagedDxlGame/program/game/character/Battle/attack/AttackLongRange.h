#pragma once

#include "AttackBase.h"

// *****************************************************************
//	これ続き書く！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
// ******************************************************************

// 遠距離攻撃のクラス
// 攻撃の当たり判定を移動するようにしたクラス
class AttackLongRange : public AttackBase{
public :

	// コンストラクタ
	// 引数：
	// targetPos...目標地点の座標
	// moveValue...移動する量
	// startPos...開始地点の座標
	// size...大きさ
	// fileName...ファイル名
	// front...正面の方向
	// charaType...攻撃のキャラクター属性
	// damage...ダメージ
	AttackLongRange(const tnl::Vector3& targetPos, float moveValue, const tnl::Vector3& startPos, float size, std::string fileName, Enum::eDir4 front, eCharaType charaType, float damage = 1.0f);

	// デストラクタ
	~AttackLongRange();


	// 更新用の関数
	void update(const float delta_time);

	// 描画用の関数
	void draw(const std::shared_ptr<dxe::Camera>& camera);


	// 新しい目標地点をセットする関数
	// 追尾する弾等を作成する際に使用
	// targetPos_のセットのみでなく、moveDir_も再度計算を行う
	void SetNewTargetPos(const tnl::Vector3& newTargetPos);


protected :


	// 移動先となる目標地点
	// コンストラクタで初期化
	tnl::Vector3 targetPos_;


	// 単位化された移動方向のベクトル
	// コンストラクタ内で計算
	tnl::Vector3 moveDir_;


	// 移動前の座標
	tnl::Vector3 beforePos_;

	// 移動する量
	// コンストラクタで初期化
	float moveValue_;

};