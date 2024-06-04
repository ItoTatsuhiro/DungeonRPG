#pragma once
#include "../../../../../dxlib_ext/dxlib_ext.h"
#include "../BattleActionBase.h"
#include "../../../other/BattleCharacterBase.h"

// 移動の行動のクラス
// 移動のみの行動を行う場合に使用する
// ランダムな位置を決定し、移動させる
class ActionMove final: public BattleActionBase {
public :

	// コンストラクタ
	// 引数：	actionCharacter ... 行動を行うキャラクター
	ActionMove(std::shared_ptr < BattleCharacterBase > actionCharacter);

	// デストラクタ
	~ActionMove();

	// 行動を実行するupdate関数
	void update(const float delta_time);


	// 行動を実行する前に、数値を初期化するための関数
	// 移動先の座標（targetPos_）、移動量関連（moveValue_, moveVectorNor_, moveVector_）を再度計算
	void setUpAction() override;


	// 移動先の座標を決定する
	void targetPosDecade();

private :


	// 目標地点の座標
	// 関数で移動地点の変更毎に変更
	tnl::Vector3 targetPos_;

	// 移動範囲の最大の大きさ
	// （キャラクターからの半径）
	// 関数で移動地点の変更毎に変更
	float moveRangeMax_;

	// 移動範囲の最小の大きさ
	// （キャラクターからの半径）
	// 関数で移動地点の変更毎に変更
	float moveRangeMin_;

	//// 移動量
	// 関数で移動地点の変更毎に変更
	float moveValue_;

	// 移動した距離をカウントする変数
	// この値がtotalMoveValue_を超えたとき移動の処理を終了させる
	float movedValueCount_;

	// 最終的に移動する距離の変数
	// 移動の際に、最終的にこの距離を進むようにする
	float totalMoveValue_;

	// 移動方向のベクトル
	// コンストラクタ内で計算し初期化
	tnl::Vector3 moveVectorNor_;

	// 移動のベクトル
	// コンストラクタ内で計算し初期化
	tnl::Vector3 moveVector_;

};