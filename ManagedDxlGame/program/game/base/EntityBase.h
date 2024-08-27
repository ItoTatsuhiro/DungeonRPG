#pragma once


#include "../../dxlib_ext/dxlib_ext.h"

#include "../other/Enum.h"

// マップ上に配置されるエンティティの元となるクラス
// マップ上での座標(存在しているマス目)を情報にもつものに継承して使用
// 引数：startPos...マップ上での初期位置(何マス目に存在するか)、gridSize...1マスの縦横の大きさ
// 継承先の例：プレイヤー、エネミー、アイテム等
// 
class EntityBase : public ito::Object3D {
public :

	// コンストラクタ
	// 引数：存在しているマス目
	EntityBase(tnl::Vector2i startPos, float gridSize);

	// デストラクタ
	virtual ~EntityBase();


	//----------------------------------------------------------------------------------------
	// ゲッター

	// gridPos_のゲッター
	// 戻り値：gridPos_...マップ上のマス目の位置
	tnl::Vector2i getGridPos() { return gridPos_; }

	// dir_のゲッター
	// 戻り値：dir_...向いている方向
	Enum::eDir4 getFrontDir() { return frontDir_; }

	//----------------------------------------------------------------------------------------
	// セッター

	// gridPos_のセッター
	// 引数：newGridPos...新規のマップ上の位置
	void setGridPos(tnl::Vector2i newGridPos) { gridPos_ = newGridPos; }

	// dir_のセッター
	// 引数：newDir...変更する新しい方向
	void setDir(Enum::eDir4 newDir) { frontDir_ = newDir; }

protected :

	// 存在するマップ上のマス目の位置
	// 一番左上に存在している場合, ( 0, 0 )
	// コンストラクタで初期化
	tnl::Vector2i gridPos_;

	// 3D座標
	// gridPos_に応じた座標となる
	tnl::Vector3 pos_;

	// 1マス分の大きさ
	// コンストラクタで初期化
	float gridSize_ = 0;

	// 向いている方向を表す変数
	// Dir4クラスは別ファイルで定義
	Enum::eDir4 frontDir_ = Enum::eDir4::UP;

};
