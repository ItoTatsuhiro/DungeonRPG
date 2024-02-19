#include "Attack.h"
#include "../../../manager/ObjectManager.h"



// コンストラクタ
// 引数：座標、大きさ、ファイル名、正面の方向(LEFTかRIGHT)
// Object3Dのメッシュを当たり判定用のメッシュとして作成する
Attack::Attack(tnl::Vector3 pos, float size, std::string fileName, Enum::Dir4 front) : frontDir_(front) {

	// 当たり判定を作成
	hitBox_ = ObjectManager::GetInstance()->createCube(size, fileName);
	hitBox_->get_mesh_()->pos_ = pos;
	
	// テクスチャ関係読み込み
	texture_ = ito::ResourceManager::GetInstance()->loadTexture(fileName);
	textureCutNum_ = ito::ResourceManager::GetInstance()->getTextureCutNum(fileName);

	// テクスチャの一つ分の大きさを計算
	float sizeU = 1.0 / textureCutNum_.x;
	float sizeV = 1.0 / textureCutNum_.y;


	// テクスチャを貼り付ける用のメッシュを生成
	for (int v = 0; v < textureCutNum_.y; ++v) {

		std::vector<std::shared_ptr<ito::Object3D>> objArray;

		for (int u = 0; u < textureCutNum_.x; ++u) {

			std::string objName = fileName + std::to_string(u) + std::to_string(v);

			std::shared_ptr<ito::Object3D> playerObj
				= ObjectManager::GetInstance()->createPlane(tnl::Vector3{ size, size, size }, objName, { u * sizeU, v * sizeV, 0 }, { (u + 1) * sizeU, (v + 1) * sizeV, 0 });


			// 表示設定を変更
			playerObj->get_mesh_()->setBlendMode(DX_BLENDMODE_ALPHA);
			playerObj->get_mesh_()->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			playerObj->get_mesh_()->setCullingMode(DX_CULLING_RIGHT);

			// テクスチャの貼り付け
			playerObj->get_mesh_()->setTexture(texture_);

			objArray.emplace_back(playerObj);
		}
		displayObjArray_.emplace_back(objArray);
	}

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

void Attack::draw(std::shared_ptr<dxe::Camera> camera) {

	// 非表示状態の時以下の描画の処理を行わない
	if (!isActive_) { return; }

	// 表示する画像用のメッシュの座標を当たり判定用のメッシュの位置に更新
	displayObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->pos_ = hitBox_->get_mesh_()->pos_;

	displayObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->render(camera);

}


