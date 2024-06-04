#include "Attack.h"
#include "../../../manager/ObjectManager.h"



// コンストラクタ
// 引数：座標、大きさ、ファイル名、正面の方向(LEFTかRIGHT), ダメージ
// Object3Dのメッシュを当たり判定用のメッシュとして作成する
Attack::Attack(tnl::Vector3 pos, float size, std::string fileName, Enum::Dir4 front, float damage)
	: SpriteObjectBase(pos, size, fileName) , damage_(damage)
{

	CreateSpriteObjArray(fileName);

	// 当たり判定を作成
	hitBox_ = ObjectManager::GetInstance()->createCube(size, fileName);
	hitBox_->get_mesh_()->pos_ = pos;
	

	displayObj_.y = (frontDir_ == Enum::Dir4::LEFT) ? 1 : 0;

}

// デストラクタ
Attack::~Attack() {

}


// 更新用の関数
void Attack::update(float delta_time) {

	if (animChangeCount_ > animChangeTime_ / 3) {
		// 次の画像のメッシュに切り替え
		++displayObj_.x;
		// 表示時間を0にリセットする
		animChangeCount_ = 0;

		// 攻撃が終わった際に表示しない状態にする
		if (displayObj_.x >= textureCutNum_.x) {

			isActive_ = false;

		}

	}
	else {
		animChangeCount_ += delta_time;
	}

}

// 描画用の関数
void Attack::draw(std::shared_ptr<dxe::Camera> camera) {

	SpriteObjectBase::draw(camera);

}


