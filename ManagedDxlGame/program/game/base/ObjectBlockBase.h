#pragma once
#include "../../dxlib_ext/dxlib_ext.h"



// オブジェクトの元になるクラス
// 床、壁等のオブジェクトを作成する際はこれを継承する
class ObjectBlockBase : public ito::Transform {
public :
	// コンストラクタ
	// 初期座標がある場合は引数でtnl::Vector3型で入れる
	explicit ObjectBlockBase(float gridSize = 50.0f, tnl::Vector3 pos = {0, 0, 0}) : gridSize_(gridSize), ito::Transform(pos) {}
	// デストラクタ
	virtual ~ObjectBlockBase(){}

	// アップデート関数
	virtual void update(float delta_time) {};
	// 描画関数
	virtual void draw(std::shared_ptr<dxe::Camera> camera) {}

	// 構成するオブジェクトを生成する関数
	// これを仮想関数として回すことで、一気にオブジェクトを作成可能
	virtual void CreateObj(){}


	//-----------------------------------------------------------------------
	// ゲッター

	// hasCollisionのゲッター
	bool getHasCollision() const { return hasCollision_; }

	// canMoveのゲッター
	bool getCanMove() const { return canMove_; }
	
	// 座標を取得するゲッター
	// 継承先でメッシュの座標を取得できるよう関数を用意すること
	// virtual tnl::Vector3 getMeshPos() = 0 { return tnl::Vector3{ -1, -1, -1 }; }

	//-----------------------------------------------------------------------
	// セッター

	// hasCollision_のセッター
	void setHasCollision(bool setHasCollision) { hasCollision_ = setHasCollision; }

	// canMove_のセッター
	void setCanMove(bool setCanMove) { canMove_ = setCanMove; }

protected :

	// オブジェクトが当たり判定を持っているかを表す変数
	bool hasCollision_ = true;
	// そのオブジェクトを移動できるか
	bool canMove_ = true;

	// 大きさの変数
	// 初期値が基本の大きさとなる
	// { x方向の大きさ, y方向の大きさ, z方向の大きさ }
	float gridSize_ = 50.0f;

	// 天井までの高さ
	int height_ = 3;

};

