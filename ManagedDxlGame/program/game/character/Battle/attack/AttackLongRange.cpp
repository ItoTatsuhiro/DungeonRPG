#include "AttackLongRange.h"



// コンストラクタ
// 引数：
// targetPos...目標地点の座標
// moveValue...移動する量
// startPos...開始地点の座標
// size...大きさ
// fileName...ファイル名
// front...正面の方向
// charaType...攻撃のキャラクター属性（player or enemy）
// damage...ダメージ
AttackLongRange::AttackLongRange(const tnl::Vector3& targetPos, float moveValue, const tnl::Vector3& startPos, float size, std::string fileName, Enum::eDir4 front, eCharaType charaType, float damage )
	: AttackBase(startPos, size, fileName, front, charaType, damage), moveValue_(moveValue)
{

	SetNewTargetPos(targetPos);


	// ステージとの接触を確認するようにする
	checkHitStage_ = true;
	

}



// デストラクタ
AttackLongRange::~AttackLongRange() {

}



// 更新用の関数
void AttackLongRange::update(const float delta_time) {

	// 移動の処理

	beforePos_ = transform_.getPos_();

	transform_.setPos_(beforePos_ + moveDir_ * delta_time);


	// AttackBaseクラスの更新
	AttackBase::update(delta_time);

}



// 描画用の関数
void AttackLongRange::draw(const std::shared_ptr<dxe::Camera>& camera) {


	AttackBase::draw(camera);


}



// 新しい目標地点をセットする関数
// 追尾する弾等を作成する際に使用
// targetPos_のセットのみでなく、moveDir_も再度計算を行う
void AttackLongRange::SetNewTargetPos(const tnl::Vector3& newTargetPos) {

	//目標地点のセット
	targetPos_ = newTargetPos;

	// 移動のベクトルを計算
	moveDir_ = tnl::Vector3::Normalize(targetPos_ - transform_.getPos_());


}

