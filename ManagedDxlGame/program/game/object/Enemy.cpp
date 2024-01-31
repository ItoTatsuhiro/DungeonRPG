#include "../../dxlib_ext/dxlib_ext.h"
#include "Enemy.h"

#include "../manager/ObjectManager.h"


// コンストラクタ
// cellSize_(マップの1マス分の大きさ)とgridPos_(存在している座標)を初期化
// 引数：cellSize...ステージの1マスの大きさ
// startGridPos...生成時の初期位置
Enemy::Enemy(float gridSize, tnl::Vector2i startGridPos) : CharacterBase(gridSize, startGridPos) {

	enemyObj_ = ObjectManager::GetInstance()->createPlane(tnl::Vector3(gridSize), "enemy");

	enemyObj_->get_mesh_()->rot_ *= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, 1), tnl::ToDegree(90));

	

}

// デストラクタ
Enemy::~Enemy() {

}

// 更新用の関数
void Enemy::update(float delta_time) {

	//seq_.update(delta_time);

}

// 描画用の関数
void Enemy::draw( std::shared_ptr<dxe::Camera> camera ) {

	enemyObj_->get_mesh_()->render(camera);

}


//bool Enemy::seqIdle(const float delta_time) {
//
//
//
//}








