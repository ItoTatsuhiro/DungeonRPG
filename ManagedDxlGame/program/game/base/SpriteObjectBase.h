#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../other/Enum.h"



// 当たり判定用のBoxと、テクスチャを貼り付けて画面に表示する用のplaneの配列を持つクラス
// 使用箇所：キャラクター、攻撃のエフェクト等
// これをさらに用途に応じて継承して使用
class SpriteObjectBase {
public :

	// コンストラクタ
	// 引数：startPos...開始位置, meshSize...当たり判定のBoxの大きさ, objName...このオブジェクトの名前
	SpriteObjectBase(tnl::Vector3 startPos, float meshSize, std::string objName);

	// デストラクタ
	virtual ~SpriteObjectBase();


	// 更新用の関数
	// *********************************************************************
	// 継承先のupdate関数でも、このクラスのupdate関数を呼び出すこと!!
	// *********************************************************************
	virtual void update(float delta_time) = 0;

	// 描画用の関数
	// 引数：描画用のカメラ、デフォルトはnullptrに設定しているが基本入れること
	// *********************************************************************
	// 継承先のdraw関数でも、このクラスのdraw関数を呼び出すこと!!
	// *********************************************************************
	virtual void draw(const std::shared_ptr<dxe::Camera>& camera) = 0;

	// spriteObjArray_の中身を生成する関数
	// 引数：textureFileName...貼り付けるテクスチャのファイル名
	void CreateSpriteObjArray(std::string textureFileName);

	// ******************************************************************************
	// 以下ゲッター

	// isActive_のゲッター
	inline bool getIsActive() const { return isActive_; }

	// transform_を取得するゲッター
	inline ito::Transform getTransform() const { return transform_; }

	// transform_のpos_要素を取得するゲッター
	inline tnl::Vector3 getPos() const { return transform_.getPos_(); }

	// hitBox_のゲッター
	inline std::shared_ptr<ito::Object3D> getHitBox() const { return hitBox_; }

	// frontDir_のゲッター
	inline Enum::eDir4 getFrontDir() const { return frontDir_; }

	// meshSize_のゲッター
	inline float getMeshSize() const { return meshSize_; }

	// ******************************************************************************
	// 以下セッター


	// isActive_のセッター
	inline void setIsActive(bool isActive) { isActive_ = isActive; }

	// transformのセッター
	inline void setTransform(ito::Transform transform) { transform_ = transform; }

	// transformのpos_要素のセッター
	inline void setPos(tnl::Vector3 newPos) { transform_.setPos_(newPos); }

	// frontDirのセッター
	inline void setFrontDir(Enum::eDir4 frontDir) { frontDir_ = frontDir; }


protected :

	// オブジェクトのアクティブ状態のフラグ
	bool isActive_ = true;

	// オブジェクトの名前
	std::string objName_;

	// オブジェクトの座標等の情報
	// これを変更すると、hitBox_とspriteObj_の座標も変更できるようにする
	ito::Transform transform_;

	// 当たり判定用のBox
	// テクスチャは基本的に無し
	// コンストラクタで生成
	std::shared_ptr<ito::Object3D> hitBox_ = nullptr;

	// テクスチャを貼り付けるplane用の配列
	std::vector<std::vector<std::shared_ptr<ito::Object3D>>> spriteObjArray_;
	// テクスチャ用
	// CreateSpriteObjArray関数で読み込み
	std::shared_ptr<dxe::Texture> texture_ = nullptr;
	// テクスチャの分割数
	// CreateSpriteObjArray関数で読み込み
	tnl::Vector2i textureCutNum_ = { 0, 0 };

	// アニメーション用のメッシュを切り替える時間
	const float animChangeTime_ = 0.15;
	// 現在のアニメーションを再生している時間
	// 移動等のアニメーションは止めた際に0にリセットする
	float animChangeCount_ = 0;
	// 表示中のオブジェクトの番号
	tnl::Vector2i displayObj_ = { 0, 0 };

	// メッシュの大きさ
	float meshSize_ = 50;

	// 向いている方向の変数
	Enum::eDir4 frontDir_ = Enum::eDir4::UP;
	// アニメーションの方向
	// アニメーションが左右の絵しかない場合等、これで管理する
	Enum::eDir4 animFrontDir_ = Enum::eDir4::UP;



};
