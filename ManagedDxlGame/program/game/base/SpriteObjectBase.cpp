#include "SpriteObjectBase.h"
#include "../manager/ObjectManager.h"

// コンストラクタ
// 引数：startPos...開始位置, meshSize...当たり判定のBoxの大きさ, objName...このオブジェクトの名前
SpriteObjectBase::SpriteObjectBase(tnl::Vector3 startPos, float meshSize, std::string objName) : meshSize_(meshSize), objName_(objName){

	// hitBox + 大きさで名前を付ける
	std::string hitBoxName = objName + "hitBox";
	// 当たり判定用のメッシュ生成
	hitBox_ = ObjectManager::GetInstance()->createCube(meshSize_, hitBoxName);


}

// デストラクタ
SpriteObjectBase::~SpriteObjectBase() {



}


// spriteObjArray_の中身を生成する関数
// 引数：textureFileName...貼り付けるテクスチャのファイル名
void SpriteObjectBase::CreateSpriteObjArray(std::string textureFileName) {

	// テクスチャ関連読み込み
	texture_ = ito::ResourceManager::GetInstance()->loadTexture(textureFileName);
	textureCutNum_ = ito::ResourceManager::GetInstance()->getTextureCutNum(textureFileName);

	// テクスチャの一つ分の大きさを計算
	float sizeU = 1.0 / textureCutNum_.x;
	float sizeV = 1.0 / textureCutNum_.y;

	// デバッグ用表示
	tnl::DebugTrace("sizeU = %f, sizeV = %f\n", sizeU, sizeV);

	// テクスチャを貼り付ける用のメッシュを生成
	for (int v = 0; v < textureCutNum_.y; ++v) {

		std::vector<std::shared_ptr<ito::Object3D>> objArray;

		for (int u = 0; u < textureCutNum_.x; ++u) {

			std::string objName = objName_ + std::to_string(u) + std::to_string(v);

			std::shared_ptr<ito::Object3D> playerObj
				= ObjectManager::GetInstance()->createPlane(tnl::Vector3{ meshSize_, meshSize_, meshSize_ }, objName, { u * sizeU, v * sizeV, 0 }, { (u + 1) * sizeU, (v + 1) * sizeV, 0 });

			// デバッグ用表示
			tnl::DebugTrace(" (%d, %d) = 前(%f, %f), 後(%f, %f)\n", u, v, u * sizeU, v * sizeV, (u + 1) * sizeU, (v + 1) * sizeV);


			// 表示設定を変更
			playerObj->get_mesh_()->setBlendMode(DX_BLENDMODE_ALPHA);
			playerObj->get_mesh_()->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			playerObj->get_mesh_()->setCullingMode(DX_CULLING_RIGHT);

			// テクスチャの貼り付け
			playerObj->get_mesh_()->setTexture(texture_);

			objArray.emplace_back(playerObj);
		}
		spriteObjArray_.emplace_back(objArray);
	}

}