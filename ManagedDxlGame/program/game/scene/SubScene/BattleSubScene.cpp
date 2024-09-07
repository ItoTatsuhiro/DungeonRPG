#include "BattleSubScene.h"
#include "../../base/ObjectBlockBase.h"
#include "../../map/objectBlock/Floor.h"
#include "../../map/objectBlock/Wall.h"
#include "../../character/other/BattleCharacterBase.h"
#include "../../character/Battle/BattlePlayer.h"
#include "../../character/Battle/BattleEnemy.h"
#include "../../character/Battle/Enemy/EnemyEscape.h"
#include "../../manager/SubSceneManager.h"
#include "../../ui/UiHP.h"


#include "../../other/TransformCamera.h"
#include "../../manager/InputManager.h"



// コンストラクタ
BattleSubScene::BattleSubScene() {

	// リスト生成
	battleCharaList_ = std::make_shared<std::list<std::shared_ptr<BattleCharacterBase>>>();

	// バトルシーンのマップ配列の読み込み
	battleStageArray_ = tnl::LoadCsv<int>("csv/BattleMap.csv");
	// 表示するカメラの変数を初期化
	TPCamera_ = std::make_shared< TransformCamera >(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	// キャラクターの開始位置の初期化
	startPosPlayer_ = { static_cast<float>(battleStageArray_[0].size()) / 3 * gridSize_, 0, static_cast<float>(battleStageArray_[0].size()) / 2 * -gridSize_ };
	startPosEnemy_ = { static_cast<float>(battleStageArray_[0].size()) * 2 / 3 * gridSize_, 0, static_cast<float>(battleStageArray_[0].size()) / 2 * -gridSize_ };


	// プレイヤーを生成
	player_ = std::shared_ptr<BattlePlayer>(new BattlePlayer(startPosPlayer_, gridSize_, "travellerAnim.png"));
	// プレイヤーの向きを設定(右向き)
	player_->setFrontDir(Enum::eDir4::RIGHT);
	// 描画するリストに追加
	battleCharaList_->emplace_back(player_);


	// 敵キャラクターの生成
	enemy_ = BattleEnemyEscape::Create(startPosEnemy_, gridSize_, "slimeAnim.png", battleCharaList_);
	// 敵キャラクターの向きを設定(左向き)
	enemy_->setFrontDir(Enum::eDir4::LEFT);
	// 描画するリストに追加
	battleCharaList_->emplace_back(enemy_);


	CreateBattleUI();


	// カメラの座標を設定
	TPCamera_->pos_ = { basePos_.x + (battleStageArray_[0].size() / 2) * gridSize_, gridSize_ * 2, gridSize_ * (-15) };



	CreateStage();

	// 操作説明画像読み込み
	battleControlExpGpc_ = ito::ResourceManager::GetInstance()->loadGraph("battleExp.png");

	// BGM読み込み
	battleBgmHdl_ = ito::ResourceManager::GetInstance()->loadSoundMem("hiphop2.mp3");

	// 音量調整
	ChangeVolumeSoundMem(50, battleBgmHdl_);

}

// デストラクタ
BattleSubScene::~BattleSubScene() {

}


// 更新用関数
void BattleSubScene::update(float delta_time) {

	// BGM再生
	if (!isPlayingBGM_) {
		PlaySoundMem(battleBgmHdl_, DX_PLAYTYPE_LOOP);

		isPlayingBGM_ = true;
	}


	// シーケンスの更新
	seq_.update(delta_time);


	// カメラの更新
	TPCamera_->update();
	
}


// 描画用関数
void BattleSubScene::draw() {



	// 描画するキャラクターをソート
	SortCharacter(TPCamera_);

	// オブジェクトを順番に描画
	auto it = battleStageObjList_.begin();
	while (it != battleStageObjList_.end()) {

		(*it)->draw(TPCamera_);

		++it;
	}


	// キャラクターを順番に描画
	auto itC = battleCharaList_->begin();
	while (itC != battleCharaList_->end()) {

		(*itC)->draw(TPCamera_);

		++itC;
	}

	// UIの描画
	DisplayBattleUI();


	// 画像の描画
	auto itGpc = gpcList_.begin();
	while (itGpc != gpcList_.end()) {

		// 画像を描画
		DrawRotaGraph((*itGpc)->getPos_().x, (*itGpc)->getPos_().y, (*itGpc)->getSizeMag(), 0, (*itGpc)->getHdl(), true);

		++itGpc;
	}

	// 操作説明画像の描画
	DrawRotaGraph(battleControlExpPos_.x, battleControlExpPos_.y, battleControlExpSize_, 0, battleControlExpGpc_, true);

}



// サブシーン切り替えの際に実行する関数
void BattleSubScene::ChangeSubScene() {

	// BGM停止
	StopSoundMem(battleBgmHdl_);

	isPlayingBGM_ = false;
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
				floorObj = std::shared_ptr<Floor>(new Floor(gridSize_, tnl::Vector3(basePos_.x + x * gridSize_, basePos_.y + gridSize_ / 2, basePos_.z - y * gridSize_)));

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


	cameraTargetPos_ = { battleStageObjArray_[battleStageArray_.size() / 2][battleStageArray_[0].size() / 2]->getPos_() };

	TPCamera_->target_ = cameraTargetPos_;

	// 描画するオブジェクトをソート
	SortObject(TPCamera_);

}

// 描画するオブジェクトをソートする関数
void BattleSubScene::SortObject(std::shared_ptr<dxe::Camera> camera) {

	// ステージに配置しているブロック等をカメラからの距離順でソート
	battleStageObjList_.sort([&](const std::shared_ptr<ObjectBlockBase>& left, const std::shared_ptr<ObjectBlockBase>& right) {
		float l1 = (camera->pos_ - left->getPos_()).length();
		float l2 = (camera->pos_ - right->getPos_()).length();
		return (l1 > l2);
	});

}

// 描画するオブジェクトをソートする関数
void BattleSubScene::SortCharacter(std::shared_ptr<dxe::Camera> camera) {

	// キャラクターをカメラからの距離でソート
	battleCharaList_->sort([&](const std::shared_ptr<BattleCharacterBase>& left, const std::shared_ptr<BattleCharacterBase>& right) {
		float l1 = (camera->pos_ - left->getPos()).length();
		float l2 = (camera->pos_ - right->getPos()).length();
		return (l1 > l2);
		});

}


// 座標の補正を行う関数
// ステージの範囲外にはみ出た場合、前の座標をもとに補正を行う
void BattleSubScene::PosCorrection() {


	auto it = battleCharaList_->begin();

	while (it != battleCharaList_->end()) {

		// キャラクターのxをステージサイズに補正
		if ((*it)->getPos().x < stageSizeMin_.x) {
			(*it)->setPos(tnl::Vector3{ stageSizeMin_.x, (*it)->getPos().y, (*it)->getPos().z });
		}
		else if ((*it)->getPos().x > stageSizeMax_.x) {
			(*it)->setPos(tnl::Vector3{ stageSizeMax_.x, (*it)->getPos().y, (*it)->getPos().z });
		}

		// キャラクターのyをステージサイズ未満にならないよう補正
		if ((*it)->getPos().y < stageSizeMin_.y) {
			(*it)->setPos(tnl::Vector3{ (*it)->getPos().x, stageSizeMin_.y, (*it)->getPos().z });
		}

		// キャラクターのzをステージサイズに補正
		if ((*it)->getPos().z > stageSizeMin_.z) {
			(*it)->setPos(tnl::Vector3{ (*it)->getPos().x, (*it)->getPos().y, stageSizeMin_.z });
		}
		else if ((*it)->getPos().z < stageSizeMax_.z) {
			(*it)->setPos(tnl::Vector3{ (*it)->getPos().x, (*it)->getPos().y, stageSizeMax_.z });
		}

		++it;

	}


}


// 攻撃判定が当たっているかどうか確認する関数
void BattleSubScene::CheckHitAttack() {


	//-----------------------------------------------------------------
	// プレイヤーの攻撃の当たり判定の処理

	auto& playerAttack = player_->getAttackList();

	auto it_p = playerAttack.begin();



	while (it_p != player_->getAttackList().end()) {

		// 攻撃が有効でないときは処理しない
		if (!(*it_p)->getIsActive()) {
			++it_p;
			continue;
		}


		tnl::Vector3 atkPos = (*it_p)->getPos();

		// キャラクターとの当たり判定を確認
		if (tnl::IsIntersectAABB( atkPos, { (*it_p)->getMeshSize(), (*it_p)->getMeshSize(), (*it_p)->getMeshSize() },
									enemy_->getPos(), { enemy_->getMeshSize(), enemy_->getMeshSize(), enemy_->getMeshSize() })) {

			// ダメージを与える関数
			enemy_->TakeDamage( (*it_p)->getDamage() );

		}

		// *********************************************************************************************************
		// ステージとの当たり判定を確認
		// 作成中！！！！！
		if (atkPos.x < stageSizeMin_.x || atkPos.y < stageSizeMin_.y || atkPos.x > stageSizeMax_.x || atkPos.y > stageSizeMax_.y) {

			//// ステージの範囲外の時アクティブ状態をfalseにする
			//(*it_p)->setIsActive(false);

			// ステージ範囲外に出たとき当たった判定にする
			(*it_p)->setIsHit(true);

		}



		++it_p;
	}

	//-----------------------------------------------------------------
	// 敵の攻撃の当たり判定の処理

	auto& enemyAttack = enemy_->getAttackList();

	auto it_e = enemyAttack.begin();

	while (it_e != enemy_->getAttackList().end()) {

		// 攻撃が有効でないときは処理しない
		if (!(*it_e)->getIsActive()) {
			++it_e;
			continue;
		}

		// キャラクターとの当たり判定
		if (tnl::IsIntersectAABB((*it_e)->getPos(), { (*it_e)->getMeshSize(), (*it_e)->getMeshSize(), (*it_e)->getMeshSize() },
			player_->getPos(), { player_->getMeshSize(), player_->getMeshSize(), player_->getMeshSize() })) {

			// ダメージを与える関数
			player_->TakeDamage((*it_e)->getDamage());

		}

		++it_e;
	}




}

// バトルシーンが終了しているかどうかを確認する関数
void BattleSubScene::CheckBattleEnd() {

	float playerHp = player_->status_->getHp();
	float enemyHp = enemy_->status_->getHp();


	// バトルが終了していないとき処理せずreturnする
	if (playerHp > 0 && enemyHp > 0) {

		return;

	}


	isBattling_ = false;

	// 敵のHPが0以下かつplayerが生存している時
	if (enemyHp <= 0 && playerHp > 0) {

		// クリア時の表示
		std::shared_ptr<ito::Graphic> clearText = 
			std::shared_ptr<ito::Graphic>(new ito::Graphic(ito::ResourceManager::GetInstance()->loadGraph("CRUSH!.png"), 2.0f));
		// 座標を設定
		clearText->setPos_(mainGpcPos_);

		// 表示する画像リストに入れる
		gpcList_.emplace_back(clearText);

	}

	// プレイヤーのHPが0以下かつ敵が生存しているとき
	if (playerHp <= 0 && enemyHp > 0) {

		// 敗北時の表示
		std::shared_ptr<ito::Graphic> clearText =
			std::shared_ptr<ito::Graphic>(new ito::Graphic(ito::ResourceManager::GetInstance()->loadGraph("CRUSHED....png"), 2.0f));
		// 座標を設定
		clearText->setPos_(mainGpcPos_);

		// 表示する画像リストに入れる
		gpcList_.emplace_back(clearText);

	}


	seq_.change(&BattleSubScene::seqBattleEnd);


}



// UI関係を生成する関数
void BattleSubScene::CreateBattleUI() {


	playerHpUi_ = std::shared_ptr< UiHP >(new UiHP(player_, "LIFE.png", "blockLong_Blue-Green.png", "ball_Blue-Green.png", playerHpPos_));

	enemyHpUi_ = std::shared_ptr< UiHP >(new UiHP(enemy_, "LIFE_red.png", "blockLong_Red-Blue.png", "ball_Red-Blue.png", enemyHpPos_));

}

// バトルのUIを表示するための関数
// draw関数内で呼び出す
void BattleSubScene::DisplayBattleUI() {

	// プレイヤーのHPのUIを表示
	playerHpUi_->draw();

	enemyHpUi_ -> draw();



	

}


bool BattleSubScene::seqBattle(const float delta_time) {


	// キャラクターの更新
	if (player_) {
		player_->update(delta_time);
	}
	if (enemy_) {
		enemy_->update(delta_time);
	}

	// 位置の補正
	PosCorrection();

	// 攻撃の当たり判定の確認
	CheckHitAttack();

	// 終了しているかどうかの確認
	CheckBattleEnd();

	//// カメラの更新
	//TPCamera_->update();

	return true;
}



// バトルシーンを終了させるシーケンス
bool BattleSubScene::seqBattleEnd(const float delta_time) {

	// シーンを切り替えるまでの時間をカウント
	sceneChangeCount_ += delta_time;

	// シーンを切り替える時間が経過したとき
	if (sceneChangeCount_ >= sceneChangeTime_) {

		SubSceneManager::GetInstance()->ChangeSubScene(SubSceneManager::ScenePlaySubScene::DUNGEON);

	}

	return true;
}