#pragma once
#include "../../../../dxlib_ext/dxlib_ext.h"
#include "../../../other/Enum.h"
#include "../../../base/SpriteObjectBase.h"


// 攻撃のクラス
// 当たり判定用のメッシュを持つ
class Attack : public SpriteObjectBase {
public :

	// コンストラクタ
	// 引数：座標、大きさ、ファイル名、正面の方向、ダメージ
	Attack(tnl::Vector3 pos, float size, std::string fileName, Enum::Dir4 front, float damage = 1.0f );
	// デストラクタ
	~Attack();
	// 更新用の関数
	void update(float delta_time) override;
	// 描画用の関数
	void draw( std::shared_ptr<dxe::Camera> camera) override;

	//-------------------------------------------------------------
	// ゲッター

	// ダメージの数値を取得する関数
	inline float getDamage() const { return damage_; }

	// ゲームの終了状態を取得する関数
	inline bool getIsEnd() const { return isEnd_; }



protected :

	// ダメージ
	float damage_;

	// ループするかどうか
	// ループしない場合はアニメーションの1ループで基本削除する
	bool isLoop_;

	// 終了しているかどうか
	// デフォルトでfalse
	// 処理を終了させるときはこのフラグをtrueにする
	bool isEnd_;
	
};
