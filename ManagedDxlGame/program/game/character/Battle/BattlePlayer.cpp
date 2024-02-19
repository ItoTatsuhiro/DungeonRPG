#include "BattlePlayer.h"
#include "../../manager/InputManager.h"
#include "../../manager/ObjectManager.h"

#include "../Battle/attack/Attack.h"

// コンストラクタ
// 引数：開始位置
// 移動前の座標は開始位置で初期化
BattlePlayer::BattlePlayer(tnl::Vector3 startPos) : beforePos_(startPos){
	// 当たり判定用のメッシュの作成
	hitBox_ = ObjectManager::GetInstance()->createCube(meshSize_, "playerHitBox");
	// 引数の開始位置の座標で初期化
	// 高さはメッシュの大きさの半分とする
	hitBox_->get_mesh_()->pos_ = (startPos + tnl::Vector3{0, meshSize_ / 5, 0});

	// テクスチャの読み込み
	playerTexture_ = ito::ResourceManager::GetInstance()->loadTexture("travellerAnim.png");
	// テクスチャの分割数の読み込み
	textureCutNum_ = ito::ResourceManager::GetInstance()->getTextureCutNum("travellerAnim.png");


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

			std::shared_ptr<ito::Object3D> playerObj
				= ObjectManager::GetInstance()->createPlane(tnl::Vector3{ meshSize_, meshSize_, meshSize_ }, objName, { u * sizeU, v * sizeV, 0 }, { (u + 1) * sizeU, (v + 1) * sizeV, 0 });

			// デバッグ用表示
			tnl::DebugTrace(" (%d, %d) = 前(%f, %f), 後(%f, %f)\n", u, v, u * sizeU, v * sizeV, (u + 1) * sizeU, (v + 1) * sizeV);


			// 表示設定を変更
			playerObj->get_mesh_()->setBlendMode(DX_BLENDMODE_ALPHA);
			playerObj->get_mesh_()->setSampleFilterMode(DX_DRAWMODE_NEAREST);
			playerObj->get_mesh_()->setCullingMode(DX_CULLING_RIGHT);

			// テクスチャの貼り付け
			playerObj->get_mesh_()->setTexture(playerTexture_);

			objArray.emplace_back(playerObj);
		}
		playerObjArray_.emplace_back(objArray);
	}

	displayObj_ = tnl::Vector2i( 1, textureCutNum_.y - 2);

	attackSize_ = meshSize_ * 2;

	return;
}

// デストラクタ
BattlePlayer::~BattlePlayer() {


	return;
}

// 更新用の関数
void BattlePlayer::update(float delta_time) {

	seq_.update(delta_time);

	auto it = attackList_.begin();
	while (it != attackList_.end()) {
		(*it)->update(delta_time);

		if ((*it)->get_isActive_() == false) {

			it = attackList_.erase(it);

		}
		else{
			++it;
		}
		
	}


	return;
}

// 描画用の関数
void BattlePlayer::draw( std::shared_ptr<dxe::Camera> camera) {
	// デバッグ用
	// DrawStringEx(100, 100, -1, "playerPos = x : %f, y : %f, z : %f", hitBox_->get_mesh_()->pos_.x, hitBox_->get_mesh_()->pos_.y, hitBox_->get_mesh_()->pos_.z);

	// 表示する画像用のメッシュの座標を当たり判定用のメッシュの位置に更新
	playerObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->pos_ = hitBox_->get_mesh_()->pos_;

	playerObjArray_[displayObj_.y][displayObj_.x]->get_mesh_()->render(camera);


	auto it = attackList_.begin();
	while (it != attackList_.end()) {
		(*it)->draw(camera);

		++it;
	}

	return;
}


// 移動の関数
// 当たり判定のメッシュ(hitBox)をずらし、
void BattlePlayer::Move(float delta_time) {

	// 全ての方向キーが押されている時or何も押されていないとき
	if ((InputManager::GetInstance()->KeyDownUp() && InputManager::GetInstance()->KeyDownLeft()
		&& InputManager::GetInstance()->KeyDownDown() && InputManager::GetInstance()->KeyDownRight())
		|| (!InputManager::GetInstance()->KeyDownUp() && !InputManager::GetInstance()->KeyDownLeft()
			&& !InputManager::GetInstance()->KeyDownDown() && !InputManager::GetInstance()->KeyDownRight())) {

		// アニメーションのカウントを0にする
		animChangeCount_ = 0;

		/*if (frontDir == Enum::Dir4::LEFT) {
			displayObj_ = tnl::Vector2i( 1, 3 );
		}
		else if (frontDir == Enum::Dir4::RIGHT) {
			displayObj_ = tnl::Vector2i(1, 2);
		}*/

		displayObj_.x = 1;

		// 以下を処理しない
		return;
	}

	// 移動前に座標を記録する
	beforePos_ = hitBox_->get_mesh_()->pos_;

	// 押したキーに応じて座標をずらす
	if (InputManager::GetInstance()->KeyDownUp()) {
		hitBox_->get_mesh_()->pos_.z += moveValue_;
		frontDir = Enum::Dir4::UP;
	}
	if (InputManager::GetInstance()->KeyDownDown()) {
		hitBox_->get_mesh_()->pos_.z -= moveValue_;
		frontDir = Enum::Dir4::DOWN;
	}
	if (InputManager::GetInstance()->KeyDownLeft()) {
		hitBox_->get_mesh_()->pos_.x -= moveValue_;
		animFrontDir = Enum::Dir4::LEFT;
		frontDir = Enum::Dir4::LEFT;
		displayObj_.y = 3;
	}
	if (InputManager::GetInstance()->KeyDownRight()) {
		hitBox_->get_mesh_()->pos_.x += moveValue_;
		animFrontDir = Enum::Dir4::RIGHT;
		frontDir = Enum::Dir4::RIGHT;
		displayObj_.y = 2;
	}

	if (animChangeCount_ >= animChangeTime_) {
		displayObj_.x = (displayObj_.x + 1) % textureCutNum_.x;
		animChangeCount_ = 0;
	}
	else {
		animChangeCount_ += delta_time;
	}

	return;
}


// 攻撃の処理に入るための関数
// 攻撃のためのキー入力が入ったときシーケンスを切り替える処理を行う
// また、攻撃の処理の前の準備も行う
void BattlePlayer::OnAttackKey() {

	// 攻撃のための入力が入った際にシーケンスを切り替える処理
	// 条件を満たしていた場合は攻撃に移る前の準備も行う
	// キーを増やすor変更する際は以下の条件を変更すること
	if (InputManager::GetInstance()->MouseClickTriggerLeft()) {
		seq_.change(&BattlePlayer::seqAttack);
		// アニメーションの表示時間のカウントを0にする
		animChangeCount_ = 0;

		// 向きに応じて表示する画像の向きを変更
		displayObj_.y = (animFrontDir == Enum::Dir4::LEFT) ? 1 : 0;
		displayObj_.x = 0;

		tnl::Vector3 attackPos;

		if (frontDir == Enum::Dir4::UP) {
			attackPos = hitBox_->get_mesh_()->pos_ + tnl::Vector3{ 0, 0, attackSize_ };
		}
		else if (frontDir == Enum::Dir4::DOWN) {
			attackPos = hitBox_->get_mesh_()->pos_ + tnl::Vector3{ 0, 0, -attackSize_ };
		}
		else if (frontDir == Enum::Dir4::LEFT) {
			attackPos = hitBox_->get_mesh_()->pos_ + tnl::Vector3{ -attackSize_ , 0, 0 };
		}
		else if (frontDir == Enum::Dir4::RIGHT) {
			attackPos = hitBox_->get_mesh_()->pos_ + tnl::Vector3{ attackSize_ , 0, 0 };
		}

		attackList_.emplace_back(std::shared_ptr<Attack>(new Attack(attackPos, attackSize_, "slashAnim.png", animFrontDir)));
	}

	return;
}


// 待機中のシーケンス
// 移動は待機中に行うことができる
bool BattlePlayer::seqIdle(const float delta_time) {

	// 入力があった際に移動を行う
	Move(delta_time);

	// 攻撃の入力の確認
	OnAttackKey();

	return true;

}

// 攻撃のシーケンス
// 入力があった際にIdleから切り替えて
bool BattlePlayer::seqAttack(const float delta_time) {	

	if (animChangeCount_ > animChangeTime_ / 3) {
		// 次の画像のメッシュに切り替え
		++displayObj_.x;
		// 表示時間を0にリセットする
		animChangeCount_ = 0;

		// 攻撃が終わった際に攻撃の処理から遷移する処理
		if (displayObj_.x >= textureCutNum_.x) {

			// 表示するメッシュを切り替え
			displayObj_.x = 0;
			displayObj_.y = (animFrontDir == Enum::Dir4::LEFT) ? 3 : 2;

			seq_.change(&BattlePlayer::seqIdle);
		}

	}
	else {
		animChangeCount_ += delta_time;
	}

	return true;

}