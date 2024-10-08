#include "BattlePlayer.h"
#include "../../manager/InputManager.h"
#include "../../manager/ObjectManager.h"

#include "../Battle/attack/Attack.h"

// コンストラクタ
// 引数：tnl::Vector3 startPos...開始位置, float objSize...オブジェクトの大きさ, std::string fileName...テクスチャのファイル名
// 移動前の座標は開始位置で初期化
BattlePlayer::BattlePlayer(tnl::Vector3 startPos, float objSize, std::string fileName)
	: /*attackSize_(meshSize_ * 2), */BattleCharacterBase(startPos, objSize, fileName){



	// 表示するメッシュの初期設定
	displayObj_ = tnl::Vector2i( 1, textureCutNum_.y - 2);

	// キャラクターの種類の設定
	characterType_ = eCharaType::PLAYER;

	return;
}

// デストラクタ
BattlePlayer::~BattlePlayer() {


	return;
}

// 更新用の関数
void BattlePlayer::update(const float delta_time) {

	seq_.update(delta_time);

	// キャラクターベースの更新
	BattleCharacterBase::update(delta_time);

	return;
}

// 描画用の関数
void BattlePlayer::draw(const std::shared_ptr<dxe::Camera>& camera) {
	// デバッグ用
	// DrawStringEx(100, 100, -1, "playerPos = x : %f, y : %f, z : %f", hitBox_->get_mesh_()->pos_.x, hitBox_->get_mesh_()->pos_.y, hitBox_->get_mesh_()->pos_.z);

	// 
	BattleCharacterBase::draw(camera);

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

		displayObj_.x = 1;

		// 以下を処理しない
		return;
	}

	// 移動前に座標を記録する
	// beforePos_ = hitBox_->get_mesh_()->pos_;
	beforePos_ = transform_.getPos_();

	// 押したキーに応じて座標をずらす
	if (InputManager::GetInstance()->KeyDownUp()) {
		MoveCharacter(delta_time, tnl::Vector3{ 0, 0, 1 });
		frontDir_ = Enum::eDir4::UP;
	}
	if (InputManager::GetInstance()->KeyDownDown()) {
		MoveCharacter(delta_time, tnl::Vector3{ 0, 0, -1 });
		frontDir_ = Enum::eDir4::DOWN;
	}
	if (InputManager::GetInstance()->KeyDownLeft()) {
		MoveCharacter(delta_time, tnl::Vector3{ -1, 0, 0 });
		animFrontDir_ = Enum::eDir4::LEFT;
		frontDir_ = Enum::eDir4::LEFT;
		displayObj_.y = 3;
	}

	if (InputManager::GetInstance()->KeyDownRight()) {
		MoveCharacter(delta_time, tnl::Vector3{ 1, 0, 0 });
		animFrontDir_ = Enum::eDir4::RIGHT;
		frontDir_ = Enum::eDir4::RIGHT;
		displayObj_.y = 2;
	}

	// アニメーション用画像切り替え
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
		displayObj_.y = (animFrontDir_ == Enum::eDir4::LEFT) ? 1 : 0;
		displayObj_.x = 0;

		tnl::Vector3 attackPos;

		if (frontDir_ == Enum::eDir4::UP) {
			attackPos = hitBox_->get_mesh_()->pos_ + tnl::Vector3{ 0, 0, attackSize_ };
		}
		else if (frontDir_ == Enum::eDir4::DOWN) {
			attackPos = hitBox_->get_mesh_()->pos_ + tnl::Vector3{ 0, 0, -attackSize_ };
		}
		else if (frontDir_ == Enum::eDir4::LEFT) {
			attackPos = hitBox_->get_mesh_()->pos_ + tnl::Vector3{ -attackSize_ , 0, 0 };
		}
		else if (frontDir_ == Enum::eDir4::RIGHT) {
			attackPos = hitBox_->get_mesh_()->pos_ + tnl::Vector3{ attackSize_ , 0, 0 };
		}

		// 攻撃のリストに追加
		attackList_.emplace_back(std::shared_ptr<Attack>(new Attack(attackPos, attackSize_, "slashAnim.png", animFrontDir_, eCharaType::PLAYER)));
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
			displayObj_.y = (animFrontDir_ == Enum::eDir4::LEFT) ? 3 : 2;

			seq_.change(&BattlePlayer::seqIdle);
		}

	}
	else {
		animChangeCount_ += delta_time;
	}

	return true;

}