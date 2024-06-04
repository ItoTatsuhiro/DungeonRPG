#include "UiHP.h"


// コンストラクタ
// 引数：
// character...HPを表示するキャラクター
// hpIconFileName...表示するHPアイコンのファイル名
// nomalHpGpcFileName...表示するHP画像のファイル名
// damagedHpGpcFileName...表示するHP画像（被ダメージ時）のファイル名
// pos...表示位置
UiHP::UiHP(std::shared_ptr<BattleCharacterBase> character, std::string hpIconFileName, std::string nomalHpGpcFileName, std::string damagedHpGpcFileName, tnl::Vector3 pos)
	: character_(character), ito::Transform(pos)
{
	// アイコン画像のクラスの作成
	hpIcon_ = std::shared_ptr<ito::Graphic>(new ito::Graphic(ito::ResourceManager::GetInstance()->loadGraph(hpIconFileName)));
	hpIcon_->setPos_(hpIconPos_);
	// 画像の大きさを設定
	hpIcon_->setSizeMag(0.8);



	// キャラクターのHP最大値の値までクラスを作成
		for (int i = 0; i < character_->status_->getHpMax(); ++i) {


			// 一個分のHPの画像の配列
			// 配列の一つ目を通常のHP用の画像、二つ目を削れたHP用の画像として使用する
			std::vector< std::shared_ptr< ito::Graphic> > hpGpc;

			// 通常の体力の画像
			std::shared_ptr< ito::Graphic > nomalHpGpc = 
				std::shared_ptr<ito::Graphic>(new ito::Graphic(ito::ResourceManager::GetInstance()->loadGraph(nomalHpGpcFileName)));
			// 座標設定
			nomalHpGpc->setPos_(hpGpcPos_ + tnl::Vector3{ hpGpcSpaceWidth_ * i, 0, 0 });
			// 倍率設定
			nomalHpGpc->setSizeMag(1);

			// 被ダメージ時の体力画像
			std::shared_ptr< ito::Graphic > damagedHpGpc = 
				std::shared_ptr<ito::Graphic>(new ito::Graphic(ito::ResourceManager::GetInstance()->loadGraph(damagedHpGpcFileName)));
			// 座標設定
			damagedHpGpc->setPos_(hpGpcPos_ + tnl::Vector3{ hpGpcSpaceWidth_ * i, 0, 0 });
			// 倍率設定
			damagedHpGpc->setSizeMag(1);

			// 配列にそれぞれ追加
			hpGpc.emplace_back( nomalHpGpc );
			hpGpc.emplace_back( damagedHpGpc );

			// クラスをvectorに追加
			hpGpcArray_.emplace_back( hpGpc );

		}

}


// デストラクタ
UiHP::~UiHP() {

}


//void update(float delta_time) {
//
//}


// 描画用の関数
void UiHP::draw() {

	hpIcon_->draw(ito::Transform::pos_);

	for (int i = 0; i < character_->status_->getHpMax(); ++i) {

		if (i < character_->status_->getHp()) {

			hpGpcArray_[i][ static_cast<int>(HPGPC_CONTENT::NOMAL_HP)]->draw(ito::Transform::pos_);

		}
		else {

			hpGpcArray_[i][static_cast<int>(HPGPC_CONTENT::DAMAGED_HP)]->draw(ito::Transform::pos_);

		}

	}

}