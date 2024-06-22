#include "../../../dxlib_ext/dxlib_ext.h"
#include "Enemy.h"

#include "../../map/Stage.h"
#include "../../manager/ObjectManager.h"
#include "Player.h"
#include "../../manager/TurnManager.h"

// コンストラクタ
// cellSize_(マップの1マス分の大きさ)とgridPos_(存在している座標)を初期化
// 引数：gridSize...ステージの1マスの大きさ
// startGridPos...生成時の初期位置
Enemy::Enemy(float gridSize, tnl::Vector2i startGridPos, std::shared_ptr<Player> player, std::shared_ptr<TurnManager> turnManager)
	: player_(player), CharacterBaseDungeon(gridSize, startGridPos), turnManager_(turnManager) {

	// 向きをランダムに決定
	frontDir_ = static_cast<Enum::Dir4>(rand() % static_cast<int>(Enum::Dir4::DIRMAX));

	// ステージクラスのインスタンスを取得
	stage_ = Stage::GetInstance();

	// テクスチャの読み込み
	enemyTexture_ = ito::ResourceManager::GetInstance()->loadTexture("wispAnimDir4.png");

	// テクスチャの分割数を取得
	textureCutNum_ = ito::ResourceManager::GetInstance()->getTextureCutNum("wispAnimDir4.png");

	// Transformの情報を入れる
	nowTransform_.setPos_( stage_->getGridObjPos(startGridPos) + tnl::Vector3(0, 1, 0) * gridSize );

	// テクスチャの一つ分の大きさを計算
	float sizeU = 1.0 / textureCutNum_.x;
	float sizeV = 1.0 / textureCutNum_.y;

	// デバッグ用表示
	tnl::DebugTrace("sizeU = %f, sizeV = %f\n", sizeU, sizeV);

	// テクスチャを貼り付ける用のメッシュを生成
	for (int v = 0; v < textureCutNum_.y; ++v) {

		std::vector<std::shared_ptr<ito::Object3D>> objArray;

		for (int u = 0; u < textureCutNum_.x; ++u) {

			std::string objName = "enemy" + std::to_string(u) + std::to_string(v);

			std::shared_ptr<ito::Object3D> enemyObj
				= ObjectManager::GetInstance()->createPlane(tnl::Vector3(gridSize * 1.5 ), objName, { u * sizeU, v * sizeV, 0 }, { (u + 1) * sizeU, (v + 1) * sizeV, 0 });

			// デバッグ用表示
			//tnl::DebugTrace(" (%d, %d) = 前(%f, %f), 後(%f, %f)\n", u, v, u * sizeU, v * sizeV, (u + 1) * sizeU, (v + 1) * sizeV);

			// 向きを回転
			enemyObj->get_mesh_()->rot_ *= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 0, 1), tnl::ToRadian(90));
			enemyObj->get_mesh_()->rot_ *= tnl::Quaternion::RotationAxis(tnl::Vector3(0, 1, 0), tnl::ToRadian(90));

			// 表示設定を変更
			enemyObj->get_mesh_()->setBlendMode(DX_BLENDMODE_ALPHA);
			enemyObj->get_mesh_()->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			enemyObj->get_mesh_()->setCullingMode(DX_CULLING_RIGHT);

			// テクスチャの貼り付け
			enemyObj->get_mesh_()->setTexture(enemyTexture_);

			objArray.emplace_back(enemyObj);
		}
		enemyObjArray_.emplace_back(objArray);
	}

	// デバッグ用
	size = { sizeU, sizeV, 0 };

	// nowTransform_.setPos_({ 0, 50, 150 });
}

// デストラクタ
Enemy::~Enemy() {

}

// 更新用の関数
void Enemy::update(float delta_time) {

	// 画像をアニメーションさせるための処理
	animCount_ += delta_time;
	if (animCount_ / animTime_ > textureCutNum_.x) { animCount_ = 0; }
	displayObj_ = { static_cast<int> (animCount_ / animTime_) , displayObj_.y };


	// プレイヤーの向きとの差に応じて表示させるテクスチャを切り替える
	// 背中の画像を表示
	if (frontDir_ - (player_->getFrontDir()) == Enum::Dir4::UP) { 
		displayObj_.y= 0;
	}
	// 左向きの画像を表示
	else if (frontDir_ - (player_->getFrontDir()) == Enum::Dir4::LEFT) { 
		displayObj_.y = 1;
	}
	// 正面の画像を表示
	else if (frontDir_ - (player_->getFrontDir()) == Enum::Dir4::DOWN) { 
		displayObj_.y = 3;
	}
	// 右向きの画像を表示
	else if (frontDir_ - (player_->getFrontDir()) == Enum::Dir4::RIGHT) { 
		displayObj_.y = 2;
	}

	

	// シーケンスのアップデート処理
	seq_.update(delta_time);

	// 表示中のオブジェクトのTransform情報を現在の状態に合わせる
	enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->pos_ = nowTransform_.getPos_();
	enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->rot_ = ( player_->getTransform().getRot3D_() );

	// LookAt関数
	// 現状使用できていない
	// 
	//enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->rot_
	//	*= tnl::Quaternion::LookAt(nowTransform_.getPos_(), player_->getTransform().getPos_(), {0, 1, 0});

}

// 描画用の関数
void Enemy::draw( std::shared_ptr<dxe::Camera> camera ) {

	//// デバッグ用表示
	//DrawStringEx(500, 100, -1, "表示中 = %d, %d", displayObj_.x, displayObj_.y);
	//DrawStringEx(500, 200, -1, "表示座標 = %f, %f", enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->pos_.x, enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->pos_.z);
	//DrawStringEx(500, 250, -1, "nowTransform = %f, %f", nowTransform_.getPos_().x, nowTransform_.getPos_().z);
	//DrawStringEx(500, 300, -1, "name = %s", enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->getName().c_str());
	//DrawStringEx(650, 100, -1, "正面：敵 = %d, プレイヤー = %d", frontDir_, player_->getFrontDir());
	//DrawStringEx(500, 350, -1, "frontDir_ - (player_->getFrontDir() = %d", frontDir_ - (player_->getFrontDir()));

	enemyObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->render(camera);

}


// 自身を削除する関数
void Enemy::Destroy() {


	delete this;
}


// Idle状態からシーケンスを切り替えるための関数
// TurnManagerから呼び出して使用する
void Enemy::ChangeSeqFromIdle() {

	// Idle以外の状態のとき処理しない
	if (nowSeq_ != EnemySeq::IDLE) { 
		tnl::DebugTrace("Idle状態では無かったため処理できませんでした\n");
		return;
	}

	// シーケンスを切り替える
	seq_.change(&Enemy::seqActionDecide);

}


// Wait状態から次の処理に切り替える処理
// TurnManagerから呼び出して使用する
void Enemy::ChangeSeqFromWait() {

	// Wait以外の状態のとき処理しない
	if (nowSeq_ != EnemySeq::WAIT) {
		tnl::DebugTrace("Wait状態では無かったため処理できませんでした\n");
		return;
	}

	// シーケンスを切り替える
	// decadedSeq_に応じて切り替えるシーケンスを変更する
	if (decadedSeq_ == EnemySeq::WAIT) {
		tnl::DebugTrace("次の処理が決定されていなかったため処理できませんでした\n");
	}
	else if (decadedSeq_ == EnemySeq::MOVING) {
		seq_.change(&Enemy::seqMoving);
	}
	else if (decadedSeq_ == EnemySeq::ROTATING) {
		seq_.change(&Enemy::seqRotating);
	}
	
	return;

}


// 待機中のシーケンス
// ChangeSeqFromIdle関数を呼び出すことで次のシーケンスに遷移
bool Enemy::seqIdle(const float delta_time) {

	if (actDebugMove) { actDebugMove = false; }

	if (tnl::Input::IsKeyDown(eKeys::KB_LCONTROL) && tnl::Input::IsKeyDown(eKeys::KB_E)) {
		actDebugMove = true;
		tnl::DebugTrace("デバッグ行動実行");

		ChangeSeqFromIdle();
	}

	return true;

}


// 行動内容を決定するシーケンス
bool Enemy::seqActionDecide(const float delta_time) {

	// 次の進行方向
	tnl::Vector2i nextGrid = gridPos_;

	// マスを計算
	nextGrid = calcMoveGrid(frontDir_);

	// 進行方向のマスが移動できないとき
	if (!(stage_->CheckGridCanMove(nextGrid))) {


		// 自分の左のマスが移動可能か確認
		tnl::Vector2i leftGrid = { 0, 0 };
		if (frontDir_ + Enum::Dir4::LEFT == Enum::Dir4::UP) { leftGrid = gridPos_ + tnl::Vector2i::up; }
		else if (frontDir_ + Enum::Dir4::LEFT == Enum::Dir4::LEFT) { leftGrid = gridPos_ + tnl::Vector2i::left; }
		else if (frontDir_ + Enum::Dir4::LEFT == Enum::Dir4::DOWN) { leftGrid = gridPos_ + tnl::Vector2i::down; }
		else if (frontDir_ + Enum::Dir4::LEFT == Enum::Dir4::RIGHT) { leftGrid = gridPos_ + tnl::Vector2i::right; }

		bool canMoveL = stage_->CheckGridCanMove(leftGrid);


		// 自分の右のマスが移動可能か確認
		tnl::Vector2i rightGrid = { 0, 0 };
		if (frontDir_ + Enum::Dir4::RIGHT == Enum::Dir4::UP) { rightGrid = gridPos_ + tnl::Vector2i::up; }
		else if (frontDir_ + Enum::Dir4::RIGHT == Enum::Dir4::LEFT) { rightGrid = gridPos_ + tnl::Vector2i::left; }
		else if (frontDir_ + Enum::Dir4::RIGHT == Enum::Dir4::DOWN) { rightGrid = gridPos_ + tnl::Vector2i::down; }
		else if (frontDir_ + Enum::Dir4::RIGHT == Enum::Dir4::RIGHT) { rightGrid = gridPos_ + tnl::Vector2i::right; }

		bool canMoveR = stage_->CheckGridCanMove(rightGrid);


		// 左右どちらにも移動できるとき
		if (canMoveL && canMoveR) {
			// 次に向く方向を左右からランダムに決定する
			nextDir_ = frontDir_ + ((rand() % 2 == 0) ? Enum::Dir4::LEFT : Enum::Dir4::RIGHT);
		}
		// 左にのみ移動できるとき
		else if (canMoveL && !canMoveR) {
			// 次に向く方向を現在の向きの左向きにする
			nextDir_ = frontDir_ + Enum::Dir4::LEFT;
		}
		// 右にのみ移動できるとき
		else if (!canMoveL && canMoveR) {
			// 次に向く向きを現在の向きの右向きにする
			nextDir_ = frontDir_ + Enum::Dir4::RIGHT;
		}
		// 左右どちらにも移動できないとき
		else if (!canMoveL && !canMoveR) {
			// 次に向く向きを現在の向きの後ろ向きにする
			nextDir_ = frontDir_ + Enum::Dir4::DOWN;
		}
		nowSeq_ = EnemySeq::ROT_CHECK;

		// シーケンスを回転の確認をするシーケンスに切り替える
		seq_.change(&Enemy::seqRotateCheck);


	}
	// 正面が移動できるとき
	else {
	
		nextGridPos_ = nextGrid;

		nowSeq_ = EnemySeq::MOVE_CHECK;

		// シーケンスを移動の確認をするシーケンスに切り替える
		seq_.change(&Enemy::seqMoveCheck);

	}

	return true;

}


// 移動を準備するシーケンス
bool Enemy::seqMoveCheck(const float delta_time) {

	// 移動先が配列外の場合移動しないようにするための処理
	if (stage_->CheckGridPosInt(nextGridPos_) == -1) {
		tnl::DebugTrace("配列外のため移動できません\n");

		nowSeq_ = EnemySeq::IDLE;
		seq_.change(&Enemy::seqIdle);

		return true;
	}

	// 移動先のマスが移動できないとき
	if (!(stage_->CheckGridPosObj(nextGridPos_)->getCanMove())) {

		// 次の座標を現在の座標に戻す
		nextGridPos_ = gridPos_;
		// シーケンスを待機中に戻す
		seq_.change(&Enemy::seqIdle);
		nowSeq_ = EnemySeq::IDLE;
		// 処理を終了する
		return true;
	}
	// 移動できるとき
	else {
		// 移動先の座標を設定
		nextTransform_.setPos_({ nextGridPos_.x * gridSize_, gridSize_, -nextGridPos_.y * gridSize_ });

		// 待機を行うシーケンスに切り替え
		seq_.change(&Enemy::seqWait);

		// シーケンスの切り替えを制限
		finishAction_ = false;

		// 状態を待機に切り替え
		nowSeq_ = EnemySeq::WAIT;
		// 待機後の行動をMovingに設定
		decadedSeq_ = EnemySeq::MOVING;

		return true;
	}

}


// 回転を準備するシーケンス
bool Enemy::seqRotateCheck(const float delta_time) {

	// 次の向きに応じて次の方向を変更する
	// 左周りをプラスとする
	if (nextDir_ - frontDir_ == Enum::Dir4::LEFT) {
		// 回転させる量を90度にする
		rotValMax_ = -90;
	}
	else if (nextDir_ - frontDir_ == Enum::Dir4::DOWN) {
		// 回転させる量を180度にする
		rotValMax_ = -180;
	}
	else if (nextDir_ - frontDir_ == Enum::Dir4::RIGHT) {
		// 回転させる量を-90度にする
		rotValMax_ = 90;
	}



	// 次の角度を現在の角度から回転量分回転させる
	nextTransform_.setRot3D_(nextTransform_.getRot3D_() * tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(rotValMax_)));

	// 待機を行うシーケンスに切り替え
	seq_.change(&Enemy::seqWait);

	// シーケンスの切り替えを制限
	finishAction_ = false;

	// 現在のシーケンスをWaitに変更
	nowSeq_ = EnemySeq::WAIT;
	// 待機後の行動をRotatingに設定
	decadedSeq_ = EnemySeq::ROTATING;

	return true;


}



// 行動待ちシーケンス
// ChangeSeqFromWait関数を呼び出すことで次のシーケンスに遷移
bool Enemy::seqWait(const float delta_time) {

	if (actDebugMove) {
		ChangeSeqFromWait();
	}

	return true;

}



// 移動を行うシーケンス
bool Enemy::seqMoving(const float delta_time) {

	Moving(delta_time);

	if (finishAction_) {
		turnManager_->ActionEndEnemy();

		seq_.change(&Enemy::seqIdle);
		nowSeq_ = EnemySeq::IDLE;
	}

	return true;
}

// 回転を行うシーケンス
bool Enemy::seqRotating(const float delta_time) {


	// 現在のトランスフォームを次のトランスフォームに合わせる
	nowTransform_.setRot3D_(nextTransform_.getRot3D_());
	// 回転量のリセット
	rotValMax_ = 0;
	// 向きの情報を最新の状態にする
	frontDir_ += nextDir_;
	// 次の位置を正面にしておく
	nextDir_ = Enum::Dir4::UP;
	// 行動処理が終わった判定をtrueに
	finishAction_ = true;

	if (finishAction_) {

		turnManager_->ActionEndEnemy();

		seq_.change(&Enemy::seqIdle);
		nowSeq_ = EnemySeq::IDLE;
	}

	return true;

}








