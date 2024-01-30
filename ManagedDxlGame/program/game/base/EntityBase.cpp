#include "EntityBase.h"

// コンストラクタ
// gridPos_(マップ上で配置されている座標)、gridSize_(1マスの大きさ)を初期化
// 引数：startPos...存在しているマス目、gridSize...1マス分の大きさ
EntityBase::EntityBase(tnl::Vector2i startPos, float gridSize) : gridPos_(startPos), gridSize_(gridSize) {



}

// デストラクタ
EntityBase::~EntityBase() {

}


