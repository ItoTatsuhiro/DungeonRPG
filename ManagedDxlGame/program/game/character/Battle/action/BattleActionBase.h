#pragma once
#include "../../../../dxlib_ext/dxlib_ext.h"

class BattleCharacterBase;

// バトルシーンにおいて、主に敵が使用する行動のクラス
// 移動、攻撃等を一つの行動として扱うために,
// それぞれの行動のクラスに継承して使用する
class BattleActionBase {
public :

	// コンストラクタ
	// 引数：行動を行うキャラクター
	BattleActionBase(std::shared_ptr< BattleCharacterBase > actionCharacter);

	// 仮想関数
	virtual ~BattleActionBase(){}


	// 純粋仮想関数
	// この関数を継承したそれぞれの行動クラスでこの関数を必ず実装すること！
	virtual void update(const float delta_time) = 0;


	// 純粋仮想関数
	// 行動を実行する前に、数値を初期化するための関数
	// それぞれの行動で初期化する必要のある数値が異なるため、それぞれの行動クラスで必ず作成する
	virtual void setUpAction() = 0;


	//-----------------------------------------------------
	// ゲッター

	// isFinished_を取得するためのゲッター
	// 行動が終了しているかどうかを外から取得するために使用する
	inline bool getIsFinished() const { return isFinished_; }


	//-----------------------------------------------------
	// セッター

	// isFinished_を変更するためのセッター
	// キャラクター側で行動の決定後、行動させる前にfalseに変更するのに使用する
	inline void setIsFinished(bool isFinished) { isFinished_ = isFinished; }


protected :

	// 行動を行うキャラクター
	// コンストラクタで初期化
	std::weak_ptr< BattleCharacterBase > actionCharacter_;

	// 行動が終了しているかどうかのフラグ
	bool isFinished_ = false;

};