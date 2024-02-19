#include "BattleSubScene.h"
#include "../../base/ObjectBlockBase.h"
#include "../../map/objectBlock/Floor.h"
#include "../../map/objectBlock/Wall.h"
#include "../../character/Battle/BattlePlayer.h"

#include "../../other/TransformCamera.h"
#include "../../manager/InputManager.h"



// コンストラクタ
BattleSubScene::BattleSubScene() {

	// バトルシーンのマップ配列の読み込み
	battleStageArray_ = tnl::LoadCsv<int>("csv/BattleMap.csv");
	// 表示するカメラの変数を初期化
	TPCamera_ = std::make_shared< TransformCamera >(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// キャラクターの開始位置の初期化
	startPosPlayer_ = { static_cast<float>(battleStageArray_[0].size()) / 3 * gridSize_, 0, static_cast<float>(battleStageArray_[0].size()) / 2 * -gridSize_ };
	startPosEnemy_ = { static_cast<float>(battleStageArray_[0].size()) * 2 / 3 * gridSize_, 0, static_cast<float>(battleStageArray_[0].size()) / 2 * -gridSize_ };

	// プレイヤーを生成
	player_ = std::shared_ptr<BattlePlayer>(new BattlePlayer(startPosPlayer_));


	// カメラの座標を設定
	TPCamera_->pos_ = { basePos_.x + (battleStageArray_[0].size() / 2) * gridSize_, gridSize_ * 2, gridSize_ * (-15) };



	CreateStage();

}

// デストラクタ
BattleSubScene::~BattleSubScene() {

}


// 更新用関数
void BattleSubScene::update(float delta_time) {

	player_->update(delta_time);

	posCorrection();

	TPCamera_->update();

	
}


// 描画用関数
void BattleSubScene::draw() {

	// 線の描画
	// DrawGridGround(TPCamera_, 50, 20);

	// 描画するオブジェクトをソート
	SortObject(TPCamera_);



	// 順番に描画
	auto it = battleStageObjList_.begin();
	while (it != battleStageObjList_.end()) {

		(*it)->draw(TPCamera_);

		++it;
	}
	// プレイヤーの描画
	player_->draw(TPCamera_);

}

// 読み込んだCSVの配列からステージを生成する関数
void BattleSubScene::CreateStage() {

	// 次のステージが作成されていない場合
	// ステージの配列情報が読み込んであるか確認
	if (battleStageArray_.size() == 0) {
		tnl::DebugTrace("配列が読み込めていません\n");
		return;
	}


	// ステージのオブジェクトを作成するための繰り返し処理
	for (int y = 0; y < battleStageArray_.size(); ++y) {

		// 横方向の配列
		std::vector<std::shared_ptr<ObjectBlockBase>> objArray_;

		for (int x = 0; x < battleStageArray_[0].size(); ++x) {

			std::shared_ptr<ObjectBlockBase> floorObj;

			// マップの情報によって生成するオブジェクトを変更する処理
			// もし要素を追加する場合はcaseを追加する
			switch (battleStageArray_[y][x]) {
			case 0:
				// 0の時壁を生成
				floorObj = std::shared_ptr<Floor>(new Floor(gridSize_, tnl::Vector3(basePos_.x + x * gridSize_, basePos_.y, basePos_.z - y * gridSize_)));

				if (floorHeight_ - 0 < FLT_EPSILON) {
					floorHeight_ = floorObj->getPos_().y;
				}

				// ステージのオブジェクトの配列に入れる
				objArray_.emplace_back(floorObj);
				// 描画用のリストに生成したオブジェクトを追加
				battleStageObjList_.emplace_back(floorObj);

				break;

			case 1:
				// 1の時壁のオブジェクトを生成
				std::shared_ptr<ObjectBlockBase> wallObj = std::shared_ptr<Wall>(new Wall(gridSize_, tnl::Vector3(basePos_.x + x * gridSize_, basePos_.y, basePos_.z - y * gridSize_)));
				// 配列に入れる用の配列に入れる
				objArray_.emplace_back(wallObj);
				// 描画用のリストに生成したオブジェクトを追加
				battleStageObjList_.emplace_back(wallObj);

				break;

			}

		}
		// ステージのオブジェクトの配列に入れる
		battleStageObjArray_.emplace_back(objArray_);
	}

	stageSizeMin_ = (battleStageObjArray_[0][0]->getPos_() + tnl::Vector3( 1.0f, 0, -1.0f) * gridSize_);
	stageSizeMin_.y = floorHeight_;

	stageSizeMax_ 
		= (battleStageObjArray_[battleStageObjArray_.size() - 1][battleStageObjArray_[battleStageObjArray_.size() - 1].size() - 1]->getPos_() 
			- tnl::Vector3{ 1.0f, 0, -1.0f } * gridSize_);
	stageSizeMax_.y = floorHeight_;

	// カメラの向きを設定
	tnl::Vector3 targetPos = { battleStageObjArray_[battleStageArray_.size() / 2][battleStageArray_[0].size() / 2]->getPos_() };

	TPCamera_->target_ = targetPos;

}

// 描画するオブジェクトをソートする関数
void BattleSubScene::SortObject(std::shared_ptr<dxe::Camera> camera) {

	battleStageObjList_.sort([&](const std::shared_ptr<ObjectBlockBase>& left, const std::shared_ptr<ObjectBlockBase>& right) {
		float l1 = (camera->pos_ - left->getPos_()).length();
		float l2 = (camera->pos_ - right->getPos_()).length();
		return (l1 > l2);
	});

}

// 座標の補正を行う関数
// ステージの範囲外にはみ出た場合、前の座標をもとに補正を行う
void BattleSubScene::posCorrection() {

	// プレイヤーのxをステージサイズに補正
	if (player_->getHitBox()->get_mesh_()->pos_.x < stageSizeMin_.x ) {
		player_->getHitBox()->get_mesh_()->pos_.x = stageSizeMin_.x;
	}
	else if (player_->getHitBox()->get_mesh_()->pos_.x > stageSizeMax_.x) {
		player_->getHitBox()->get_mesh_()->pos_.x = stageSizeMax_.x ;
	}

	// プレイヤーのyをステージサイズ未満にならないよう補正
	if (player_->getHitBox()->get_mesh_()->pos_.y < stageSizeMin_.y) {
		player_->getHitBox()->get_mesh_()->pos_.y = stageSizeMax_.y;
	}

	// プレイヤーのzをステージサイズに補正
	if (player_->getHitBox()->get_mesh_()->pos_.z > stageSizeMin_.z) {
		player_->getHitBox()->get_mesh_()->pos_.z = stageSizeMin_.z;
	}
	else if (player_->getHitBox()->get_mesh_()->pos_.z < stageSizeMax_.z) {
		player_->getHitBox()->get_mesh_()->pos_.z = stageSizeMax_.z;
	}

}


bool BattleSubScene::seqBattle(const float delta_time) {


	return true;
}