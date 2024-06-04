#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../character/other/BattleCharacterBase.h"

// キャラクターのHPを表示するUI
class UiHP : public ito::Transform {
public :

	// コンストラクタ
	// 引数：
	// character...HPを表示するキャラクター
	// hpIconFileName...表示するHPアイコンのファイル名
	// nomalHpGpcFileName...表示するHP画像のファイル名
	// damagedHpGpcFileName...表示するHP画像（被ダメージ時）のファイル名
	// pos...表示位置
	UiHP(std::shared_ptr<BattleCharacterBase> character, std::string hpIconFileName, std::string nomalHpGpcFileName, std::string damagedHpGpcFileName, tnl::Vector3 pos = {0, 0, 0});

	// デストラクタ
	~UiHP();

	//// 更新用の関数
	//// 画像の更新等、updateをしたくなった時に実装
	//void update(const float delta_time);

	// 描画用の関数
	void draw();



private :

	// HPを表示するキャラクター
	std::shared_ptr<BattleCharacterBase> character_;

	// HPの横に表示するアイコン
	std::shared_ptr< ito::Graphic > hpIcon_;

	// アイコンの相対座標
	tnl::Vector3 hpIconPos_ = { -100, 0, 0 };

	// HPを表す画像
	// HPの数値分画像を並べる想定なので配列にして管理する
	std::vector< std::vector< std::shared_ptr< ito::Graphic> > > hpGpcArray_;


	// HPの画像の配列の要素番号として使用する用のenum class
	enum class HPGPC_CONTENT {
		NOMAL_HP,			// 削れていない通常のHP
		DAMAGED_HP			// 削れたHP
	};



	// 一つ目のHPの画像の相対座標
	tnl::Vector3 hpGpcPos_ = { 0, 0, 0 };

	// HPの画像同士の横の間隔
	float hpGpcSpaceWidth_ = 30;

};