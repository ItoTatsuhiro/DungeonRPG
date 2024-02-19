#pragma once
#include "../../../../dxlib_ext/dxlib_ext.h"
#include "../../../other/Enum.h"

class Attack : public ito::Object3D {
public :

	// コンストラクタ
	// 引数：座標、大きさ、ファイル名、正面の方向
	Attack(tnl::Vector3 pos, float size, std::string fileName, Enum::Dir4 front);
	// デストラクタ
	~Attack();
	// 更新用の関数
	void update(float delta_time) override;
	// 描画用の関数
	void draw( std::shared_ptr<dxe::Camera> camera) override;

private :

	// 当たり判定用
	std::shared_ptr<ito::Object3D> hitBox_;

	// 描画するオブジェクトのvector
	std::vector<std::vector<std::shared_ptr<ito::Object3D>>> displayObjArray_;
	// 描画するオブジェクト
	tnl::Vector2i displayObj_ = { 0, 0 };
	// テクスチャ
	std::shared_ptr<dxe::Texture> texture_;
	// テクスチャの分割数
	// コンストラクタで読み込み
	tnl::Vector2i textureCutNum_ = { 0, 0 };
	
	// アニメーション用のメッシュを切り替える時間
	const float animChangeTime_ = 0.15;
	// 現在のアニメーションを再生している時間
	// 移動等のアニメーションは止めた際に0にリセットする
	float animChangeCount_ = 0;

	// 正面の方向
	// コンストラクタで初期化
	// LEFTかRIGHTを入れること
	Enum::Dir4 frontDir_ = Enum::Dir4::LEFT;

};
